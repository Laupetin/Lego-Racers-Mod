#include "ObjImporter.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <unordered_map>

#include "Obj.h"
#include "ObjReader.h"
#include "ObjWriter.h"
#include "Asset/Gdb/Gdb.h"
#include "Asset/Gdb/GdbStructReader.h"
#include "Asset/Gdb/GdbTextWriter.h"

using namespace obj;

namespace fs = std::filesystem;

namespace obj
{
    enum class BackReferenceStatus
    {
        NOT_BACK_REFERENCING,
        BEING_BACK_REFERENCED,
        BACK_REFERENCING,

        MAX
    };

    enum class VertexSelectorSortMode
    {
        NONE,
        REFERENCEABLE_AT_FRONT,
        REFERENCEABLE_AT_BACK
    };

    class PendingGdbVertex
    {
    public:
        static PendingGdbVertex NotBackReferencing(const gdb::Vertex& data, const size_t vertexIndex)
        {
            return PendingGdbVertex(data, BackReferenceStatus::NOT_BACK_REFERENCING, vertexIndex);
        }

        static PendingGdbVertex BackReferencing(const gdb::Vertex& data, const size_t backReferenceIndex)
        {
            return PendingGdbVertex(data, BackReferenceStatus::BACK_REFERENCING, backReferenceIndex);
        }

        static PendingGdbVertex BeingBackReferenced(const gdb::Vertex& data, const size_t backReferenceIndex)
        {
            return PendingGdbVertex(data, BackReferenceStatus::BEING_BACK_REFERENCED, backReferenceIndex);
        }

        PendingGdbVertex()
            : m_back_reference_status(BackReferenceStatus::NOT_BACK_REFERENCING),
              m_index(0u)
        {
        }

        PendingGdbVertex(const gdb::Vertex& vertex, const BackReferenceStatus backReferenceStatus, const size_t index)
            : m_vertex(vertex),
              m_back_reference_status(backReferenceStatus),
              m_index(index)
        {
        }

        [[nodiscard]] const gdb::Vertex& Data() const
        {
            return m_vertex;
        }

        [[nodiscard]] BackReferenceStatus GetBackReferenceStatus() const
        {
            return m_back_reference_status;
        }

        [[nodiscard]] size_t GetIndex() const
        {
            return m_index;
        }

    private:
        gdb::Vertex m_vertex;
        BackReferenceStatus m_back_reference_status;
        size_t m_index;
    };

    class PendingGdbFace
    {
    public:
        PendingGdbFace()
            : m_indices{0}
        {
        }

        PendingGdbFace(const size_t index0, const size_t index1, const size_t index2)
            : m_indices{index0, index1, index2}
        {
        }

        [[nodiscard]] size_t GetIndex(const size_t i) const
        {
            assert(i < 3);
            return m_indices[i];
        }

    private:
        size_t m_indices[3];
    };

    class PendingGdbVertexSelector
    {
    public:
        static constexpr auto MAX_VERTEX_COUNT = 64u;

        PendingGdbVertexSelector()
            : m_own_vertex_count(0u),
              m_current_back_reference_index(0u),
              m_previous_sort_mode(VertexSelectorSortMode::NONE),
              m_required_sort_mode(VertexSelectorSortMode::NONE)
        {
            m_vertices.reserve(MAX_VERTEX_COUNT);
            m_used_vertices.reserve(MAX_VERTEX_COUNT);
        }

        bool GetExistingVertex(const gdb::Vertex& vertex, size_t& pendingGdbVertexIndex)
        {
            const auto usedVertex = m_used_vertices.find(vertex);
            if (usedVertex != m_used_vertices.end())
            {
                pendingGdbVertexIndex = usedVertex->second;
                return true;
            }

            return false;
        }

        bool GetExistingNonBackReferencingVertex(const gdb::Vertex& vertex, size_t& pendingGdbVertexIndex)
        {
            const auto usedVertex = m_used_vertices.find(vertex);
            if (usedVertex != m_used_vertices.end())
            {
                pendingGdbVertexIndex = usedVertex->second;
                return m_vertices[usedVertex->second].GetBackReferenceStatus() != BackReferenceStatus::BACK_REFERENCING;
            }

            return false;
        }

        size_t AddVertex(const gdb::Vertex& vertex)
        {
            const auto newIndex = m_vertices.size();
            assert(newIndex < MAX_VERTEX_COUNT);

            m_used_vertices.emplace(vertex, newIndex);
            m_vertices.push_back(PendingGdbVertex::NotBackReferencing(vertex, newIndex));
            m_own_vertex_count++;

            return newIndex;
        }

        size_t AddBackReference(gdb::Vertex vertex, const size_t backReferenceIndex)
        {
            const auto newIndex = m_vertices.size();
            assert(newIndex < MAX_VERTEX_COUNT);

            m_used_vertices.emplace(vertex, newIndex);
            m_vertices.push_back(PendingGdbVertex::BackReferencing(vertex, backReferenceIndex));

            return newIndex;
        }

        size_t MakeBackReference(const size_t index)
        {
            assert(index < m_vertices.size());

            auto& pendingVertex = m_vertices[index];
            if (pendingVertex.GetBackReferenceStatus() == BackReferenceStatus::BEING_BACK_REFERENCED)
                return pendingVertex.GetIndex();

            const auto newBackReferenceIndex = m_current_back_reference_index++;
            pendingVertex = PendingGdbVertex::BeingBackReferenced(pendingVertex.Data(), newBackReferenceIndex);

            return newBackReferenceIndex;
        }

        [[nodiscard]] bool HasData() const
        {
            return !m_vertices.empty();
        }

        [[nodiscard]] size_t GetRemainingCapacity() const
        {
            return MAX_VERTEX_COUNT - m_vertices.size();
        }

        void SetPreviousSortMode(const VertexSelectorSortMode sortMode)
        {
            m_previous_sort_mode = sortMode;
        }

        void ReorderVerticesForBackReferencing()
        {
            // Prepare buffers
            const auto vertexCount = m_vertices.size();
            m_vertex_indices_in_new_order.resize(vertexCount);
            m_new_vertex_index_lookup.resize(vertexCount);

            // Initialize indices
            for (auto vertexIndex = 0u; vertexIndex < vertexCount; vertexIndex++)
                m_vertex_indices_in_new_order[vertexIndex] = vertexIndex;

            // Initialize order to reorder vertices to
            size_t orderByStatus[static_cast<size_t>(BackReferenceStatus::MAX)]{};
            if (m_previous_sort_mode == VertexSelectorSortMode::NONE || m_previous_sort_mode == VertexSelectorSortMode::REFERENCEABLE_AT_FRONT)
            {
                m_required_sort_mode = m_current_back_reference_index > 0 ? VertexSelectorSortMode::REFERENCEABLE_AT_BACK : VertexSelectorSortMode::NONE;
                orderByStatus[static_cast<size_t>(BackReferenceStatus::BACK_REFERENCING)] = 0u;
                orderByStatus[static_cast<size_t>(BackReferenceStatus::NOT_BACK_REFERENCING)] = 1u;
                orderByStatus[static_cast<size_t>(BackReferenceStatus::BEING_BACK_REFERENCED)] = 2u;
            }
            else
            {
                m_required_sort_mode = m_current_back_reference_index > 0 ? VertexSelectorSortMode::REFERENCEABLE_AT_FRONT : VertexSelectorSortMode::NONE;
                orderByStatus[static_cast<size_t>(BackReferenceStatus::BEING_BACK_REFERENCED)] = 0u;
                orderByStatus[static_cast<size_t>(BackReferenceStatus::NOT_BACK_REFERENCING)] = 1u;
                orderByStatus[static_cast<size_t>(BackReferenceStatus::BACK_REFERENCING)] = 2u;
            }

            // Reorder indices
            std::sort(m_vertex_indices_in_new_order.begin(), m_vertex_indices_in_new_order.end(), [this, orderByStatus](const size_t& i0, const size_t& i1)
            {
                const auto& v0 = m_vertices[i0];
                const auto& v1 = m_vertices[i1];

                const auto referenceStatus0 = v0.GetBackReferenceStatus();
                const auto referenceStatus1 = v1.GetBackReferenceStatus();
                if (referenceStatus0 != referenceStatus1)
                    return orderByStatus[static_cast<size_t>(referenceStatus0)] < orderByStatus[static_cast<size_t>(referenceStatus1)];

                if (referenceStatus0 == BackReferenceStatus::BEING_BACK_REFERENCED
                    || referenceStatus0 == BackReferenceStatus::BACK_REFERENCING)
                {
                    return v0.GetIndex() < v1.GetIndex();
                }

                return i0 < i1;
            });

            const auto shiftForwardCount = m_previous_sort_mode == VertexSelectorSortMode::REFERENCEABLE_AT_BACK && m_own_vertex_count < m_vertices.size()
                                               ? MAX_VERTEX_COUNT - m_vertices.size()
                                               : 0u;

            // Create lookup table
            for (auto index = 0u; index < vertexCount; index++)
                m_new_vertex_index_lookup[m_vertex_indices_in_new_order[index]] = index + shiftForwardCount;
        }

        [[nodiscard]] VertexSelectorSortMode GetRequiredSortMode() const
        {
            return m_required_sort_mode;
        }

        void WriteVerticesToGdb(gdb::Model& gdb) const
        {
            const auto gdbVertexOffset = gdb.m_vertices.size();
            gdb.m_vertices.resize(gdbVertexOffset + m_own_vertex_count);

            const size_t ownVertexStart = m_previous_sort_mode == VertexSelectorSortMode::REFERENCEABLE_AT_FRONT
                                              ? m_vertices.size() - m_own_vertex_count
                                              : 0u;
            for (auto i = 0u; i < m_own_vertex_count; i++)
            {
                const auto vertexIndex = m_vertex_indices_in_new_order[i + ownVertexStart];
                gdb.m_vertices[gdbVertexOffset + i] = m_vertices[vertexIndex].Data();
            }

            if (m_previous_sort_mode == VertexSelectorSortMode::REFERENCEABLE_AT_BACK && m_own_vertex_count < m_vertices.size())
            {
                // Make sure always touches end of vertex buffer
                const auto shiftForwardCount = static_cast<int>(MAX_VERTEX_COUNT - m_vertices.size());
                gdb.m_meta.emplace_back(gdb::ModelToken::TOKEN_META_VERTICES, shiftForwardCount, static_cast<int>(gdbVertexOffset), static_cast<int>(m_own_vertex_count));
            }
            else if (m_previous_sort_mode == VertexSelectorSortMode::NONE || m_previous_sort_mode == VertexSelectorSortMode::REFERENCEABLE_AT_BACK)
            {
                gdb.m_meta.emplace_back(gdb::ModelToken::TOKEN_META_VERTICES, 0, static_cast<int>(gdbVertexOffset), static_cast<int>(m_own_vertex_count));
            }
            else
            {
                assert(m_previous_sort_mode == VertexSelectorSortMode::REFERENCEABLE_AT_FRONT);

                const auto shiftForwardCount = static_cast<int>(m_vertices.size() - m_own_vertex_count);
                gdb.m_meta.emplace_back(gdb::ModelToken::TOKEN_META_VERTICES, shiftForwardCount, static_cast<int>(gdbVertexOffset), static_cast<int>(m_own_vertex_count));
            }
        }

        [[nodiscard]] size_t GetRemappedIndexForVertex(const size_t index) const
        {
            assert(index < m_vertices.size() && !m_new_vertex_index_lookup.empty());
            return m_new_vertex_index_lookup[index];
        }

    private:
        std::unordered_map<gdb::Vertex, size_t> m_used_vertices;
        std::vector<PendingGdbVertex> m_vertices;
        std::vector<size_t> m_vertex_indices_in_new_order;
        std::vector<size_t> m_new_vertex_index_lookup;
        size_t m_own_vertex_count;
        size_t m_current_back_reference_index;
        VertexSelectorSortMode m_previous_sort_mode;
        VertexSelectorSortMode m_required_sort_mode;
    };

    class PendingGdbFaceSelector
    {
    public:
        static constexpr auto MAX_FACE_COUNT = 255u;

        void AddFace(const size_t index0, const size_t index1, const size_t index2)
        {
            m_faces.emplace_back(index0, index1, index2);
        }

        [[nodiscard]] size_t GetRemainingCapacity() const
        {
            return MAX_FACE_COUNT - m_faces.size();
        }

        void WriteFacesToGdb(gdb::Model& gdb, const PendingGdbVertexSelector& vertexSelector) const
        {
            const auto gdbFaceOffset = gdb.m_faces.size();
            gdb.m_faces.reserve(gdbFaceOffset + m_faces.size());

            for (const auto& face : m_faces)
            {
                gdb.m_faces.emplace_back(
                    static_cast<unsigned char>(vertexSelector.GetRemappedIndexForVertex(face.GetIndex(0))),
                    static_cast<unsigned char>(vertexSelector.GetRemappedIndexForVertex(face.GetIndex(1))),
                    static_cast<unsigned char>(vertexSelector.GetRemappedIndexForVertex(face.GetIndex(2)))
                );
            }

            gdb.m_meta.emplace_back(gdb::ModelToken::TOKEN_META_FACES, static_cast<int>(gdbFaceOffset), static_cast<int>(m_faces.size()));
        }

    private:
        std::vector<PendingGdbFace> m_faces;
    };

    class ObjToGdbConverter
    {
    public:
        ObjToGdbConverter(gdb::Model& gdb, const ObjModel& obj, const bool hasColors)
            : m_any_null_materials(false),
              m_has_colors(hasColors),
              m_gdb(gdb),
              m_obj(obj)
        {
        }

        void Convert()
        {
            ConvertMaterials();

            for (const auto& object : m_obj.m_objects)
            {
                ConvertObject(object);
            }

            m_gdb.m_vertex_format = DetermineVertexFormat();
        }

    private:
        [[nodiscard]] gdb::VertexFormat DetermineVertexFormat() const
        {
            if (m_obj.m_objects.empty())
                return gdb::VertexFormat::POSITION;

            const auto& faces = m_obj.m_objects[0].m_faces;

            if (faces.empty())
                return gdb::VertexFormat::POSITION;

            const auto& firstFace = faces[0];

            if (firstFace.HasUv())
            {
                if (m_has_colors)
                    return gdb::VertexFormat::POSITION_UV_COLOR;

                if (firstFace.HasNormals())
                    return gdb::VertexFormat::POSITION_UV_NORMAL;

                return gdb::VertexFormat::POSITION_UV;
            }

            return gdb::VertexFormat::POSITION;
        }

        void ConvertMaterials()
        {
            m_any_null_materials = std::any_of(m_obj.m_objects.begin(), m_obj.m_objects.end(), [](const ObjObject& object)
            {
                return object.m_material_index < 0;
            });

            m_gdb.m_materials.reserve(m_obj.m_materials.size() + (m_any_null_materials ? 1 : 0));

            if (m_any_null_materials)
                m_gdb.m_materials.emplace_back("null");

            for (const auto& objMaterial : m_obj.m_materials)
                m_gdb.m_materials.emplace_back(objMaterial.m_material_name);
        }

        void ConvertObject(const ObjObject& object) const
        {
            const auto gdbMaterialIndex = object.m_material_index >= 0 ? (object.m_material_index + (m_any_null_materials ? 1 : 0)) : 0;
            m_gdb.m_meta.emplace_back(gdb::ModelToken::TOKEN_META_NEW_OBJECT, gdbMaterialIndex);

            PendingGdbVertexSelector previousVertexSelector;
            PendingGdbVertexSelector currentVertexSelector;
            PendingGdbFaceSelector previousFaceSelector;
            PendingGdbFaceSelector currentFaceSelector;

            for (const auto& face : object.m_faces)
            {
                if (currentFaceSelector.GetRemainingCapacity() <= 0)
                {
                    AdvanceSelectors(previousVertexSelector, currentVertexSelector, previousFaceSelector, currentFaceSelector);
                }

                const gdb::Vertex gdbVertices[3]
                {
                    CreateGdbVertex(object, face.m_vertex_index[0], face.m_uv_index[0], face.m_normal_index[0]),
                    CreateGdbVertex(object, face.m_vertex_index[1], face.m_uv_index[1], face.m_normal_index[1]),
                    CreateGdbVertex(object, face.m_vertex_index[2], face.m_uv_index[2], face.m_normal_index[2])
                };

                size_t pendingVertexIndex[3];
                bool vertexAlreadyExists[3];
                bool vertexIsFromPreviousSelector[3];

                FindExistingVertex(previousVertexSelector, currentVertexSelector, gdbVertices[0], pendingVertexIndex[0], vertexAlreadyExists[0], vertexIsFromPreviousSelector[0]);
                FindExistingVertex(previousVertexSelector, currentVertexSelector, gdbVertices[1], pendingVertexIndex[1], vertexAlreadyExists[1], vertexIsFromPreviousSelector[1]);
                FindExistingVertex(previousVertexSelector, currentVertexSelector, gdbVertices[2], pendingVertexIndex[2], vertexAlreadyExists[2], vertexIsFromPreviousSelector[2]);

                if (GetRequiredVertexCapacity(vertexAlreadyExists, vertexIsFromPreviousSelector) > currentVertexSelector.GetRemainingCapacity())
                {
                    // Add as many vertices to current selector as possible
                    for (auto i = 0u; currentVertexSelector.GetRemainingCapacity() > 0 && i < 3u; i++)
                    {
                        if (vertexAlreadyExists[i])
                            continue;

                        pendingVertexIndex[i] = currentVertexSelector.AddVertex(gdbVertices[i]);
                        vertexAlreadyExists[i] = true;
                        vertexIsFromPreviousSelector[i] = false;
                    }

                    AdvanceSelectors(previousVertexSelector, currentVertexSelector, previousFaceSelector, currentFaceSelector);
                    AdvanceFoundVertices(vertexAlreadyExists, vertexIsFromPreviousSelector);
                }

                const size_t faceIndices[3]
                {
                    AddVertex(previousVertexSelector, currentVertexSelector, gdbVertices[0], pendingVertexIndex[0], vertexAlreadyExists[0], vertexIsFromPreviousSelector[0]),
                    AddVertex(previousVertexSelector, currentVertexSelector, gdbVertices[1], pendingVertexIndex[1], vertexAlreadyExists[1], vertexIsFromPreviousSelector[1]),
                    AddVertex(previousVertexSelector, currentVertexSelector, gdbVertices[2], pendingVertexIndex[2], vertexAlreadyExists[2], vertexIsFromPreviousSelector[2])
                };

                currentFaceSelector.AddFace(faceIndices[0], faceIndices[1], faceIndices[2]);
            }

            if (previousVertexSelector.HasData())
            {
                FinishSelector(previousVertexSelector, previousFaceSelector);
                currentVertexSelector.SetPreviousSortMode(previousVertexSelector.GetRequiredSortMode());
            }

            if (currentVertexSelector.HasData())
                FinishSelector(currentVertexSelector, currentFaceSelector);
        }

        [[nodiscard]] gdb::Vertex CreateGdbVertex(const ObjObject& object, const int vertexIndex, const int uvIndex, const int normalIndex) const
        {
            assert(vertexIndex >= 0 && static_cast<size_t>(vertexIndex) < object.m_vertices.size());
            assert(uvIndex < 0 || static_cast<size_t>(uvIndex) < object.m_uvs.size());
            assert(normalIndex < 0 || static_cast<size_t>(normalIndex) < object.m_normals.size());

            const auto& objVertex = object.m_vertices[vertexIndex];
            const gdb::Vec3 position(objVertex.m_coordinates[0], objVertex.m_coordinates[1], objVertex.m_coordinates[2]);
            if (uvIndex >= 0)
            {
                const auto& objUv = object.m_uvs[uvIndex];
                const gdb::Vec2 uv(objUv.m_uv[0], objUv.m_uv[1]);

                if (m_has_colors)
                {
                    const gdb::Color4 color(
                        static_cast<unsigned char>(objVertex.m_colors[0] * std::numeric_limits<unsigned char>::max()),
                        static_cast<unsigned char>(objVertex.m_colors[1] * std::numeric_limits<unsigned char>::max()),
                        static_cast<unsigned char>(objVertex.m_colors[2] * std::numeric_limits<unsigned char>::max()),
                        std::numeric_limits<unsigned char>::max()
                    );

                    return gdb::Vertex(position, uv, color);
                }

                if (normalIndex >= 0)
                {
                    const auto& objNormal = object.m_normals[normalIndex];
                    const gdb::Vec3 normal(objNormal.m_normal[0], objNormal.m_normal[1], objNormal.m_normal[2]);

                    return gdb::Vertex(position, uv, normal);
                }

                return gdb::Vertex(position, uv);
            }


            return gdb::Vertex(position);
        }

        static void FindExistingVertex(PendingGdbVertexSelector& previousVertexSelector, PendingGdbVertexSelector& currentVertexSelector, const gdb::Vertex& vertex, size_t& pendingGdbVertexIndex,
                                       bool& vertexAlreadyExists, bool& vertexIsFromPreviousSelector)
        {
            if (currentVertexSelector.GetExistingVertex(vertex, pendingGdbVertexIndex))
            {
                vertexAlreadyExists = true;
                vertexIsFromPreviousSelector = false;
            }
            else if (previousVertexSelector.GetExistingNonBackReferencingVertex(vertex, pendingGdbVertexIndex))
            {
                vertexAlreadyExists = true;
                vertexIsFromPreviousSelector = true;
            }
            else
            {
                vertexAlreadyExists = false;
                vertexIsFromPreviousSelector = false;
            }
        }

        static size_t GetRequiredVertexCapacity(const bool (&vertexAlreadyExists)[3], const bool (&vertexIsFromPreviousSelector)[3])
        {
            return 0u
                + (!vertexAlreadyExists[0] || vertexIsFromPreviousSelector[0] ? 1u : 0u)
                + (!vertexAlreadyExists[1] || vertexIsFromPreviousSelector[1] ? 1u : 0u)
                + (!vertexAlreadyExists[2] || vertexIsFromPreviousSelector[2] ? 1u : 0u);
        }

        void AdvanceSelectors(PendingGdbVertexSelector& previousVertexSelector, PendingGdbVertexSelector& currentVertexSelector, PendingGdbFaceSelector& previousFaceSelector,
                              PendingGdbFaceSelector& currentFaceSelector) const
        {
            FinishSelector(previousVertexSelector, previousFaceSelector);
            currentVertexSelector.SetPreviousSortMode(previousVertexSelector.GetRequiredSortMode());

            previousVertexSelector = std::move(currentVertexSelector);
            previousFaceSelector = std::move(currentFaceSelector);

            currentVertexSelector = PendingGdbVertexSelector();
            currentFaceSelector = PendingGdbFaceSelector();
        }

        void FinishSelector(PendingGdbVertexSelector& vertexSelector, const PendingGdbFaceSelector& faceSelector) const
        {
            if (!vertexSelector.HasData())
                return;

            vertexSelector.ReorderVerticesForBackReferencing();
            vertexSelector.WriteVerticesToGdb(m_gdb);
            faceSelector.WriteFacesToGdb(m_gdb, vertexSelector);
        }

        static void AdvanceFoundVertices(bool (&vertexAlreadyExists)[3], bool (&vertexIsFromPreviousSelector)[3])
        {
            for (auto i = 0u; i < 3u; i++)
            {
                if (!vertexAlreadyExists[i])
                    continue;

                if (vertexIsFromPreviousSelector)
                {
                    vertexAlreadyExists[i] = false;
                    vertexIsFromPreviousSelector[i] = false;
                }
                else
                {
                    vertexIsFromPreviousSelector[i] = true;
                }
            }
        }

        static size_t AddVertex(PendingGdbVertexSelector& previousVertexSelector, PendingGdbVertexSelector& currentVertexSelector, const gdb::Vertex& vertex, const size_t pendingGdbVertexIndex,
                                const bool vertexAlreadyExists, const bool vertexIsFromPreviousSelector)
        {
            if (vertexAlreadyExists)
            {
                if (vertexIsFromPreviousSelector)
                {
                    const auto backReferencingIndex = previousVertexSelector.MakeBackReference(pendingGdbVertexIndex);
                    return currentVertexSelector.AddBackReference(vertex, backReferencingIndex);
                }

                return pendingGdbVertexIndex;
            }

            return currentVertexSelector.AddVertex(vertex);
        }

        bool m_any_null_materials;
        bool m_has_colors;
        gdb::Model& m_gdb;
        const ObjModel& m_obj;
    };

    std::unique_ptr<gdb::Model> CreateGdbFromObj(const ObjModel& obj, const bool hasColors)
    {
        auto gdb = std::make_unique<gdb::Model>();

        ObjToGdbConverter converter(*gdb, obj, hasColors);
        converter.Convert();

        return gdb;
    }

    bool WriteGdbFile(const gdb::Model& model, const std::string& directory, const std::string& fileName)
    {
        const fs::path path = (fs::path(directory) / fileName).replace_extension(".GDB");

        std::ofstream outStream(path, std::ios::out | std::ios::binary);
        if (!outStream.is_open())
            return false;

        const auto fileWriter = gdb::GdbTextWriter::Create(outStream);
        gdb::GdbStructReader::Read(model, *fileWriter);

        return true;
    }
}

bool ObjImporter::SupportsExtension(const std::string& extensionName) const
{
    return extensionName == ".OBJ";
}

bool ObjImporter::Convert(const std::string& directory, const std::string& filePath)
{
    const fs::path fsPath = fs::path(directory) / filePath;
    if (!fs::is_regular_file(fsPath))
    {
        std::cerr << "Not a valid file: \"" << fsPath.string() << "\"\n";
        return false;
    }

    std::ifstream in(fsPath, std::ios::in | std::ios::binary);
    if (!in.is_open())
    {
        std::cerr << "Failed to open obj: \"" << fsPath.string() << "\"\n";
        return false;
    }

    const auto reader = ObjReader::Create(in);
    const auto model = reader->ReadModel();
    if (!model)
    {
        std::cerr << "Error while reading obj: \"" << fsPath.string() << "\"\n";
        return false;
    }

    const auto gdb = CreateGdbFromObj(*model, reader->HasColors());
    if (!gdb)
        return false;

    const auto fileName = fsPath.filename().string();
    if (!WriteGdbFile(*gdb, directory, fileName))
        return false;

    return true;
}
