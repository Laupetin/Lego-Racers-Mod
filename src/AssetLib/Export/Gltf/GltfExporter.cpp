#include "glTFExporter.h"

#include <algorithm>
#include <sstream>
#include <cassert>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <unordered_map>

#include "GltfWriter.h"
#include "Export/Obj/Obj.h"
#include "Export/Obj/ObjDeduplicator.h"
#include "Export/Obj/ObjMtlConverter.h"
#include "Asset/Gdb/GdbStructWriter.h"
#include "Asset/Gdb/GdbTextReader.h"
#include "Asset/Mdb/MdbTextReader.h"

namespace fs = std::filesystem;

namespace gltf
{
    bool ReadGdbModelFromFile(std::istream& in, gdb::Model& model)
    {
        try
        {
            const auto writer = gdb::GdbStructWriter::Create(model);
            gdb::GdbTextReader::Read(in, *writer);
            return true;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Failed to load GDB: " << e.what() << "\n";
        }

        return false;
    }

    void AddVerticesWithPosition(const gdb::Model& gdbModel, obj::ObjObject& object, const gdb::VertexSelector& vertexSelector)
    {
        for (auto vertexIndex = 0u; vertexIndex < vertexSelector.m_vertex_count; vertexIndex++)
        {
            const auto& vertex = gdbModel.m_vertices[vertexSelector.m_vertex_offset + vertexIndex];

            object.m_vertices.emplace_back(vertex.m_position.x, vertex.m_position.y, vertex.m_position.z);
        }
    }

    void AddVerticesWithPositionUv(const gdb::Model& gdbModel, obj::ObjObject& object, const gdb::VertexSelector& vertexSelector)
    {
        for (auto vertexIndex = 0u; vertexIndex < vertexSelector.m_vertex_count; vertexIndex++)
        {
            const auto& vertex = gdbModel.m_vertices[vertexSelector.m_vertex_offset + vertexIndex];

            object.m_vertices.emplace_back(vertex.m_position.x, vertex.m_position.y, vertex.m_position.z);
            object.m_uvs.emplace_back(vertex.m_uv.x, vertex.m_uv.y);
        }
    }

    void AddVerticesWithPositionUvColor(const gdb::Model& gdbModel, obj::ObjObject& object, const gdb::VertexSelector& vertexSelector)
    {
        for (auto vertexIndex = 0u; vertexIndex < vertexSelector.m_vertex_count; vertexIndex++)
        {
            const auto& vertex = gdbModel.m_vertices[vertexSelector.m_vertex_offset + vertexIndex];

            object.m_vertices.emplace_back(vertex.m_position.x, vertex.m_position.y, vertex.m_position.z,
                static_cast<float>(vertex.m_color.r) / static_cast<float>(std::numeric_limits<unsigned char>::max()),
                static_cast<float>(vertex.m_color.g) / static_cast<float>(std::numeric_limits<unsigned char>::max()),
                static_cast<float>(vertex.m_color.b) / static_cast<float>(std::numeric_limits<unsigned char>::max()));
            object.m_uvs.emplace_back(vertex.m_uv.x, vertex.m_uv.y);
        }
    }

    void AddVerticesWithPositionUvNormal(const gdb::Model& gdbModel, obj::ObjObject& object, const gdb::VertexSelector& vertexSelector)
    {
        for (auto vertexIndex = 0u; vertexIndex < vertexSelector.m_vertex_count; vertexIndex++)
        {
            const auto& vertex = gdbModel.m_vertices[vertexSelector.m_vertex_offset + vertexIndex];

            object.m_vertices.emplace_back(vertex.m_position.x, vertex.m_position.y, vertex.m_position.z);
            object.m_uvs.emplace_back(vertex.m_uv.x, vertex.m_uv.y);
            object.m_normals.emplace_back(vertex.m_normal.x, vertex.m_normal.y, vertex.m_normal.z);
        }
    }

    void AddVerticesToObject(const gdb::Model& gdbModel, obj::ObjObject& object, const gdb::VertexSelector& vertexSelector)
    {
        switch (gdbModel.m_vertex_format)
        {
        case gdb::VertexFormat::POSITION:
            AddVerticesWithPosition(gdbModel, object, vertexSelector);
            break;

        case gdb::VertexFormat::POSITION_UV:
            AddVerticesWithPositionUv(gdbModel, object, vertexSelector);
            break;

        case gdb::VertexFormat::POSITION_UV_COLOR:
            AddVerticesWithPositionUvColor(gdbModel, object, vertexSelector);
            break;

        case gdb::VertexFormat::POSITION_UV_NORMAL:
            AddVerticesWithPositionUvNormal(gdbModel, object, vertexSelector);
            break;

        default:
            assert(false);
            break;
        }
    }

    bool GetAbsoluteFaceVertex(const size_t relativeIndex, size_t& objIndex, const gdb::VertexSelector& vertexSelector, const gdb::VertexSelector& previousVertexSelector,
        const size_t vertexSelectorObjOffset, const size_t previousVertexSelectorObjOffset)
    {
        if (relativeIndex < vertexSelector.m_shift_forward_count)
        {
            // In theory the game could load this (would reference back to selectors even before the previous) but i doubt the game's tools would build such a file
            if (previousVertexSelector.m_shift_forward_count > relativeIndex)
                return false;

            objIndex = previousVertexSelectorObjOffset + (relativeIndex - previousVertexSelector.m_shift_forward_count);
            return true;
        }

        const auto relativeIndexWithLookBack = relativeIndex - vertexSelector.m_shift_forward_count;

        if (relativeIndexWithLookBack >= vertexSelector.m_vertex_count)
        {
            const size_t previousRelativeIndexWithLookBack = static_cast<size_t>(relativeIndex) - previousVertexSelector.m_shift_forward_count;
            if (previousRelativeIndexWithLookBack >= previousVertexSelector.m_vertex_count)
                return false;

            objIndex = previousVertexSelectorObjOffset + previousRelativeIndexWithLookBack;
            return true;
        }

        objIndex = vertexSelectorObjOffset + relativeIndexWithLookBack;
        return true;
    }

    void AddFacesWithPosition(const gdb::Model& gdbModel, obj::ObjObject& object, const gdb::VertexSelector& vertexSelector, const gdb::VertexSelector& previousVertexSelector,
        const gdb::FaceSelector& currentFaceSelector, const int currentGroup)
    {
        const auto vertexSelectorObjOffset = object.m_vertices.size() - vertexSelector.m_vertex_count;
        const auto previousVertexSelectorObjOffset = vertexSelectorObjOffset - previousVertexSelector.m_vertex_count;

        for (auto faceIndex = 0u; faceIndex < currentFaceSelector.m_face_count; faceIndex++)
        {
            const auto& face = gdbModel.m_faces[currentFaceSelector.m_face_offset + faceIndex];
            size_t absoluteVertices[3];

            if (!GetAbsoluteFaceVertex(face.m_indices[0], absoluteVertices[0], vertexSelector, previousVertexSelector, vertexSelectorObjOffset, previousVertexSelectorObjOffset)
                || !GetAbsoluteFaceVertex(face.m_indices[1], absoluteVertices[1], vertexSelector, previousVertexSelector, vertexSelectorObjOffset, previousVertexSelectorObjOffset)
                || !GetAbsoluteFaceVertex(face.m_indices[2], absoluteVertices[2], vertexSelector, previousVertexSelector, vertexSelectorObjOffset, previousVertexSelectorObjOffset))
            {
                assert(false);
                continue;
            }

            object.m_faces.emplace_back(absoluteVertices[0], absoluteVertices[1], absoluteVertices[2], currentGroup);
        }
    }

    void AddFacesWithPositionUv(const gdb::Model& gdbModel, obj::ObjObject& object, const gdb::VertexSelector& vertexSelector, const gdb::VertexSelector& previousVertexSelector,
        const gdb::FaceSelector& currentFaceSelector, const int currentGroup)
    {
        const auto vertexSelectorObjOffset = object.m_vertices.size() - vertexSelector.m_vertex_count;
        const auto previousVertexSelectorObjOffset = vertexSelectorObjOffset - previousVertexSelector.m_vertex_count;

        for (auto faceIndex = 0u; faceIndex < currentFaceSelector.m_face_count; faceIndex++)
        {
            const auto& face = gdbModel.m_faces[currentFaceSelector.m_face_offset + faceIndex];
            size_t absoluteVertices[3];

            if (!GetAbsoluteFaceVertex(face.m_indices[0], absoluteVertices[0], vertexSelector, previousVertexSelector, vertexSelectorObjOffset, previousVertexSelectorObjOffset)
                || !GetAbsoluteFaceVertex(face.m_indices[1], absoluteVertices[1], vertexSelector, previousVertexSelector, vertexSelectorObjOffset, previousVertexSelectorObjOffset)
                || !GetAbsoluteFaceVertex(face.m_indices[2], absoluteVertices[2], vertexSelector, previousVertexSelector, vertexSelectorObjOffset, previousVertexSelectorObjOffset))
            {
                assert(false);
                continue;
            }

            object.m_faces.emplace_back(absoluteVertices[0], absoluteVertices[0],
                absoluteVertices[1], absoluteVertices[1],
                absoluteVertices[2], absoluteVertices[2],
                currentGroup);
        }
    }

    void AddFacesWithPositionUvNormal(const gdb::Model& gdbModel, obj::ObjObject& object, const gdb::VertexSelector& vertexSelector, const gdb::VertexSelector& previousVertexSelector,
        const gdb::FaceSelector& currentFaceSelector, const int currentGroup)
    {
        const auto vertexSelectorObjOffset = object.m_vertices.size() - vertexSelector.m_vertex_count;
        const auto previousVertexSelectorObjOffset = vertexSelectorObjOffset - previousVertexSelector.m_vertex_count;

        for (auto faceIndex = 0u; faceIndex < currentFaceSelector.m_face_count; faceIndex++)
        {
            const auto& face = gdbModel.m_faces[currentFaceSelector.m_face_offset + faceIndex];
            size_t absoluteVertices[3];

            if (!GetAbsoluteFaceVertex(face.m_indices[0], absoluteVertices[0], vertexSelector, previousVertexSelector, vertexSelectorObjOffset, previousVertexSelectorObjOffset)
                || !GetAbsoluteFaceVertex(face.m_indices[1], absoluteVertices[1], vertexSelector, previousVertexSelector, vertexSelectorObjOffset, previousVertexSelectorObjOffset)
                || !GetAbsoluteFaceVertex(face.m_indices[2], absoluteVertices[2], vertexSelector, previousVertexSelector, vertexSelectorObjOffset, previousVertexSelectorObjOffset))
            {
                assert(false);
                continue;
            }

            object.m_faces.emplace_back(absoluteVertices[0], absoluteVertices[0], absoluteVertices[0],
                absoluteVertices[1], absoluteVertices[1], absoluteVertices[1],
                absoluteVertices[2], absoluteVertices[2], absoluteVertices[2],
                currentGroup);
        }
    }

    void AddFacesToObject(const gdb::Model& gdbModel, obj::ObjObject& object, const gdb::VertexSelector& vertexSelector, const gdb::VertexSelector& previousVertexSelector,
        const gdb::FaceSelector& currentFaceSelector, const int currentGroup)
    {
        switch (gdbModel.m_vertex_format)
        {
        case gdb::VertexFormat::POSITION:
            AddFacesWithPosition(gdbModel, object, vertexSelector, previousVertexSelector, currentFaceSelector, currentGroup);
            break;

        case gdb::VertexFormat::POSITION_UV:
        case gdb::VertexFormat::POSITION_UV_COLOR:
            AddFacesWithPositionUv(gdbModel, object, vertexSelector, previousVertexSelector, currentFaceSelector, currentGroup);
            break;

        case gdb::VertexFormat::POSITION_UV_NORMAL:
            AddFacesWithPositionUvNormal(gdbModel, object, vertexSelector, previousVertexSelector, currentFaceSelector, currentGroup);
            break;

        default:
            assert(false);
            break;
        }
    }

    obj::ObjObject CreateNewObject(const obj::ObjModel& model, const int materialIndex)
    {
        obj::ObjObject object;
        object.m_material_index = materialIndex;

        std::ostringstream ss;
        ss << "object" << std::setw(2) << std::setfill('0') << model.m_objects.size();

        object.m_name = ss.str();
        return object;
    }

    int GetGroupForBone(obj::ObjObject& object, const int boneIndex)
    {
        std::ostringstream groupNameStream;
        groupNameStream << "Bone" << boneIndex;
        auto groupName = groupNameStream.str();

        const auto existingGroup = std::find(object.m_groups.begin(), object.m_groups.end(), groupName);
        if (existingGroup != object.m_groups.end())
            return existingGroup - object.m_groups.begin();

        const auto newGroupIndex = object.m_groups.size();
        object.m_groups.emplace_back(std::move(groupName));

        return static_cast<int>(newGroupIndex);
    }

    std::unordered_map<std::string, obj::MtlMaterial> ReadMaterialsFromDirectory(const std::string& directory)
    {
        std::unordered_map<std::string, obj::MtlMaterial> result;
        const fs::directory_iterator iterator(directory, std::filesystem::directory_options::skip_permission_denied);

        for (const auto& file : iterator)
        {
            if (!file.is_regular_file())
                continue;

            if (file.path().extension() != ".MDB")
                continue;

            std::ifstream stream(file.path());
            if (!stream.is_open())
            {
                std::cerr << "Failed to open MDB file for scanning: \"" << file.path() << "\"\n";
                continue;
            }

            try
            {
                const auto mtlConverter = obj::ObjMtlConverter::Create();
                mdb::MdbTextReader::Read(stream, *mtlConverter);

                auto materials = mtlConverter->RetrieveConvertedMaterials();

                for (auto& material : materials)
                    result.emplace(material.m_material_name, std::move(material));
            }
            catch (std::exception& e)
            {
                std::cerr << "Failed to read MDB file: \"" << file.path() << "\": " << e.what() << "\n";
            }
        }

        return result;
    }

    std::unique_ptr<obj::ObjModel> CreateObjFromGdb(const std::string& directory, const gdb::Model& gdbModel)
    {
        auto objModel = std::make_unique<obj::ObjModel>();

        gdb::VertexSelector currentVertexSelector;
        gdb::VertexSelector previousVertexSelector;
        gdb::FaceSelector currentFaceSelector;

        bool hasObject = false;
        obj::ObjObject currentObject;
        int currentGroup = -1;
        for (const auto& meta : gdbModel.m_meta)
        {
            switch (meta.m_keyword)
            {
            case gdb::TOKEN_META_NEW_OBJECT:
                if (hasObject)
                {
                    hasObject = false;
                    currentVertexSelector = gdb::VertexSelector();
                    previousVertexSelector = gdb::VertexSelector();
                    currentFaceSelector = gdb::FaceSelector();
                    objModel->m_objects.emplace_back(std::move(currentObject));
                    currentObject = obj::ObjObject();
                }

                if (meta.m_value0 >= 0 && static_cast<size_t>(meta.m_value0) <= gdbModel.m_materials.size())
                {
                    currentObject = CreateNewObject(*objModel, meta.m_value0);
                    hasObject = true;
                }
                else
                    assert(false);
                break;

            case gdb::TOKEN_META_BONE:
                currentGroup = GetGroupForBone(currentObject, meta.m_value0);
                break;

            case gdb::TOKEN_META_VERTICES:
                if (meta.m_value1 >= 0 && meta.m_value2 >= 0 && static_cast<size_t>(meta.m_value1) + static_cast<size_t>(meta.m_value2) <= gdbModel.m_vertices.size())
                {
                    previousVertexSelector = currentVertexSelector;
                    currentVertexSelector.m_shift_forward_count = meta.m_value0;
                    currentVertexSelector.m_vertex_offset = meta.m_value1;
                    currentVertexSelector.m_vertex_count = meta.m_value2;
                }
                else
                    assert(false);

                AddVerticesToObject(gdbModel, currentObject, currentVertexSelector);
                break;

            case gdb::TOKEN_META_FACES:
                if (meta.m_value0 >= 0 && meta.m_value1 >= 0 && static_cast<size_t>(meta.m_value0) + static_cast<size_t>(meta.m_value1) <= gdbModel.m_faces.size())
                {
                    currentFaceSelector.m_face_offset = meta.m_value0;
                    currentFaceSelector.m_face_count = meta.m_value1;
                }
                else
                    assert(false);

                AddFacesToObject(gdbModel, currentObject, currentVertexSelector, previousVertexSelector, currentFaceSelector, currentGroup);
                break;

            default:
                break;
            }
        }

        if (hasObject)
            objModel->m_objects.emplace_back(std::move(currentObject));

        const auto mdbMaterials = ReadMaterialsFromDirectory(directory);
        for (const auto& material : gdbModel.m_materials)
        {
            const auto loadedMdbMaterial = mdbMaterials.find(material);

            if (loadedMdbMaterial != mdbMaterials.end())
            {
                objModel->m_materials.emplace_back(loadedMdbMaterial->second);
            }
            else
            {
                objModel->m_materials.emplace_back(material, std::string());
            }
        }

        return objModel;
    }

    bool WriteGltfFile(const GltfWriter& writer, const fs::path& directory, const std::string& fileName)
    {
        fs::path outPath = directory / fileName;
        outPath.replace_extension(".glTF");

        std::ofstream out(outPath, std::ios::out | std::ios::binary);
        if (!out.is_open())
        {
            std::cerr << "Failed to open output file: \"" << outPath << "\"\n";
            return false;
        }

        fs::path fileNameWithoutExtension(fileName);
        fileNameWithoutExtension.replace_extension(".MTL");

        writer.WriteGltf(out, fileNameWithoutExtension.string());
        return true;
    }
}

using namespace gltf;

bool GltfExporter::SupportsExtension(const std::string& extensionName) const
{
    return extensionName == ".GDB";
}

bool GltfExporter::Convert(const std::string& directory, const std::string& filePath)
{
    const fs::path fsPath = fs::path(directory) / filePath;
    if (!fs::is_regular_file(fsPath))
    {
        std::cerr << "Not a valid file: \"" << fsPath << "\"\n";
        return false;
    }

    std::ifstream in(fsPath, std::ios::in | std::ios::binary);
    if (!in.is_open())
    {
        std::cerr << "Failed to open gdb: \"" << fsPath << "\"\n";
        return false;
    }

    gdb::Model model;
    if (!ReadGdbModelFromFile(in, model))
        return false;

    const auto obj = CreateObjFromGdb(directory, model);
    if (!obj)
        return false;

    for (auto& objObject : obj->m_objects)
    {
        obj::Deduplicator deduplicator(objObject);
        objObject = deduplicator.Deduplicate();
    }

    const auto fileName = fsPath.filename().string();
    GltfWriter writer(*obj);
    writer.ExportColors(model.m_vertex_format == gdb::VertexFormat::POSITION_UV_COLOR);
    writer.ExportNormals(model.m_vertex_format == gdb::VertexFormat::POSITION_UV_NORMAL);

    if (!WriteGltfFile(writer, directory, fileName))
        return false;

    return true;
}
