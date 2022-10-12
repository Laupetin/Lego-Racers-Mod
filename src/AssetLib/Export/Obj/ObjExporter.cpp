#include "ObjExporter.h"

#include <sstream>
#include <cassert>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <unordered_map>

#include "Obj.h"
#include "ObjWriter.h"
#include "Asset/Gdb/GdbStructWriter.h"
#include "Asset/Gdb/GdbTextReader.h"

namespace fs = std::filesystem;

namespace obj
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

    void AddVerticesWithPosition(const gdb::Model& gdbModel, ObjObject& object, const size_t vertexStart, const size_t vertexCount)
    {
        for (auto vertexIndex = 0u; vertexIndex < vertexCount; vertexIndex++)
        {
            const auto& vertex = gdbModel.m_vertices[vertexStart + vertexIndex];

            object.m_vertices.emplace_back(vertex.m_position.x, vertex.m_position.y, vertex.m_position.z);
        }

        //for (auto faceIndex = 0u; faceIndex < faceCount; faceIndex++)
        //{
        //    const auto& face = gdbModel.m_faces[faceStart + faceIndex];
        //    size_t absoluteVertices[3];

        //    if (!GetAbsoluteFaceVertices(face, absoluteVertices, vertexStart, vertexCount, lastVertexCountWasMax))
        //    {
        //        assert(false);
        //        continue;
        //    }

        //    object.m_faces.emplace_back(absoluteVertices[0], absoluteVertices[1], absoluteVertices[2]);
        //}
    }

    void AddVerticesWithPositionUv(const gdb::Model& gdbModel, ObjObject& object, const size_t vertexStart, const size_t vertexCount)
    {
        std::unordered_map<ObjUv, size_t> uvs;
        std::vector<size_t> uvPerVertex(vertexCount);

        for (auto vertexIndex = 0u; vertexIndex < vertexCount; vertexIndex++)
        {
            const auto& vertex = gdbModel.m_vertices[vertexStart + vertexIndex];

            object.m_vertices.emplace_back(vertex.m_position.x, vertex.m_position.y, vertex.m_position.z);
            object.m_uvs.emplace_back(vertex.m_uv.x, vertex.m_uv.y);
        }

        //for (auto faceIndex = 0u; faceIndex < faceCount; faceIndex++)
        //{
        //    const auto& face = gdbModel.m_faces[faceStart + faceIndex];

        //    if (face.m_indices[0] < vertexStart || face.m_indices[0] >= vertexStart + vertexCount
        //        || face.m_indices[1] < vertexStart || face.m_indices[1] >= vertexStart + vertexCount
        //        || face.m_indices[2] < vertexStart || face.m_indices[2] >= vertexStart + vertexCount)
        //    {
        //        assert(false);
        //        continue;
        //    }

        //    object.m_faces.emplace_back(face.m_indices[0], uvPerVertex[face.m_indices[0]],
        //                                face.m_indices[1], uvPerVertex[face.m_indices[1]],
        //                                face.m_indices[2], uvPerVertex[face.m_indices[2]]);
        //}
    }

    void AddVerticesWithPositionUvNormal(const gdb::Model& gdbModel, ObjObject& object, const size_t vertexStart, const size_t vertexCount)
    {
        std::unordered_map<ObjUv, size_t> uvs;
        std::vector<size_t> uvPerVertex(vertexCount);
        std::unordered_map<ObjNormal, size_t> normals;
        std::vector<size_t> normalPerVertex(vertexCount);

        for (auto vertexIndex = 0u; vertexIndex < vertexCount; vertexIndex++)
        {
            const auto& vertex = gdbModel.m_vertices[vertexStart + vertexIndex];

            object.m_vertices.emplace_back(vertex.m_position.x, vertex.m_position.y, vertex.m_position.z);
            object.m_uvs.emplace_back(vertex.m_uv.x, vertex.m_uv.y);
            object.m_normals.emplace_back(vertex.m_normal.x, vertex.m_normal.y, vertex.m_normal.z);
        }

        //bool shouldBackReferToPreviousVertices = lastVertexCountWasMax;
        //for (auto faceIndex = 0u; faceIndex < faceCount; faceIndex++)
        //{
        //    const auto& face = gdbModel.m_faces[faceStart + faceIndex];

        //    auto vertex0 = shouldBackReferToPreviousVertices && face.m_indices[0];
        //    auto vertex1 = face.m_indices[1];
        //    auto vertex2 = face.m_indices[2];

        //    shouldBackReferToPreviousVertices = shouldBackReferToPreviousVertices
        //        && (face.m_indices[0] > BACK_REFER_CUTOFF || face.m_indices[1] > BACK_REFER_CUTOFF || face.m_indices[2] > BACK_REFER_CUTOFF);

        //    if (face.m_indices[0] < vertexStart || face.m_indices[0] >= vertexStart + vertexCount
        //        || face.m_indices[1] < vertexStart || face.m_indices[1] >= vertexStart + vertexCount
        //        || face.m_indices[2] < vertexStart || face.m_indices[2] >= vertexStart + vertexCount)
        //    {
        //        assert(false);
        //        continue;
        //    }

        //    object.m_faces.emplace_back(face.m_indices[0], uvPerVertex[face.m_indices[0]], normalPerVertex[face.m_indices[0]],
        //                                face.m_indices[1], uvPerVertex[face.m_indices[1]], normalPerVertex[face.m_indices[1]],
        //                                face.m_indices[2], uvPerVertex[face.m_indices[2]], normalPerVertex[face.m_indices[2]]);
        //}
    }

    void AddVerticesToObject(const gdb::Model& gdbModel, ObjObject& object, const size_t vertexStart, const size_t vertexCount)
    {
        switch (gdbModel.m_vertex_format)
        {
        case gdb::VertexFormat::POSITION:
            AddVerticesWithPosition(gdbModel, object, vertexStart, vertexCount);
            break;

        case gdb::VertexFormat::POSITION_UV:
        case gdb::VertexFormat::POSITION_UV_COLOR:
            AddVerticesWithPositionUv(gdbModel, object, vertexStart, vertexCount);
            break;

        case gdb::VertexFormat::POSITION_UV_NORMAL:
            AddVerticesWithPositionUvNormal(gdbModel, object, vertexStart, vertexCount);
            break;

        default:
            assert(false);
            break;
        }
    }

    bool GetAbsoluteFaceVertices(const gdb::ModelFace& face, size_t (&absoluteVertices)[3], const size_t vertexStart, const size_t vertexCount, const bool lastVertexCountWasMax)
    {
        const auto maxValue = lastVertexCountWasMax ? 64u : vertexCount;
        if (face.m_indices[0] >= maxValue || face.m_indices[1] >= maxValue || face.m_indices[2] >= maxValue)
            return false;

        absoluteVertices[0] = face.m_indices[0] >= vertexCount ? vertexStart - (64u - face.m_indices[0]) : vertexStart + face.m_indices[0];
        absoluteVertices[1] = face.m_indices[1] >= vertexCount ? vertexStart - (64u - face.m_indices[1]) : vertexStart + face.m_indices[1];
        absoluteVertices[2] = face.m_indices[2] >= vertexCount ? vertexStart - (64u - face.m_indices[2]) : vertexStart + face.m_indices[2];
        return true;
    }

    void AddFacesWithPosition(const gdb::Model& gdbModel, ObjObject& object, const size_t vertexStart, const size_t vertexCount, const bool lastVertexCountWasMax, const size_t faceStart,
                              const size_t faceCount)
    {
        const auto objVertexStart = object.m_vertices.size() - vertexCount;

        for (auto faceIndex = 0u; faceIndex < faceCount; faceIndex++)
        {
            const auto& face = gdbModel.m_faces[faceStart + faceIndex];
            size_t absoluteVertices[3];

            if (!GetAbsoluteFaceVertices(face, absoluteVertices, objVertexStart, vertexCount, lastVertexCountWasMax))
            {
                assert(false);
                continue;
            }

            object.m_faces.emplace_back(absoluteVertices[0], absoluteVertices[1], absoluteVertices[2]);
        }
    }

    void AddFacesWithPositionUv(const gdb::Model& gdbModel, ObjObject& object, const size_t vertexStart, const size_t vertexCount, const bool lastVertexCountWasMax, const size_t faceStart,
                                const size_t faceCount)
    {
        const auto objVertexStart = object.m_vertices.size() - vertexCount;

        for (auto faceIndex = 0u; faceIndex < faceCount; faceIndex++)
        {
            const auto& face = gdbModel.m_faces[faceStart + faceIndex];
            size_t absoluteVertices[3];

            if (!GetAbsoluteFaceVertices(face, absoluteVertices, objVertexStart, vertexCount, lastVertexCountWasMax))
            {
                assert(false);
                continue;
            }

            object.m_faces.emplace_back(absoluteVertices[0], absoluteVertices[0],
                                        absoluteVertices[1], absoluteVertices[1],
                                        absoluteVertices[2], absoluteVertices[2]);
        }
    }

    void AddFacesWithPositionUvNormal(const gdb::Model& gdbModel, ObjObject& object, const size_t vertexStart, const size_t vertexCount, const bool lastVertexCountWasMax, const size_t faceStart,
                                      const size_t faceCount)
    {
        const auto objVertexStart = object.m_vertices.size() - vertexCount;

        for (auto faceIndex = 0u; faceIndex < faceCount; faceIndex++)
        {
            const auto& face = gdbModel.m_faces[faceStart + faceIndex];
            size_t absoluteVertices[3];

            if (!GetAbsoluteFaceVertices(face, absoluteVertices, objVertexStart, vertexCount, lastVertexCountWasMax))
            {
                assert(false);
                continue;
            }

            object.m_faces.emplace_back(absoluteVertices[0], absoluteVertices[0], absoluteVertices[0],
                                        absoluteVertices[1], absoluteVertices[1], absoluteVertices[1],
                                        absoluteVertices[2], absoluteVertices[2], absoluteVertices[2]);
        }
    }

    void AddFacesToObject(const gdb::Model& gdbModel, ObjObject& object, const size_t vertexStart, const size_t vertexCount, const bool lastVertexCountWasMax, const size_t faceStart,
                          const size_t faceCount)
    {
        switch (gdbModel.m_vertex_format)
        {
        case gdb::VertexFormat::POSITION:
            AddFacesWithPosition(gdbModel, object, vertexStart, vertexCount, lastVertexCountWasMax, faceStart, faceCount);
            break;

        case gdb::VertexFormat::POSITION_UV:
        case gdb::VertexFormat::POSITION_UV_COLOR:
            AddFacesWithPositionUv(gdbModel, object, vertexStart, vertexCount, lastVertexCountWasMax, faceStart, faceCount);
            break;

        case gdb::VertexFormat::POSITION_UV_NORMAL:
            AddFacesWithPositionUvNormal(gdbModel, object, vertexStart, vertexCount, lastVertexCountWasMax, faceStart, faceCount);
            break;

        default:
            assert(false);
            break;
        }
    }

    ObjObject CreateNewObject(const ObjModel& model, const int materialIndex)
    {
        ObjObject object;
        object.m_material_index = materialIndex;

        std::ostringstream ss;
        ss << "object" << std::setw(2) << std::setfill('0') << model.m_objects.size();

        object.m_name = ss.str();
        return object;
    }

    std::unique_ptr<ObjModel> CreateObjFromGdb(const gdb::Model& gdbModel)
    {
        auto objModel = std::make_unique<ObjModel>();

        int currentVertexStart = -1;
        int currentVertexCount = -1;
        bool lastVertexCountWasMax = false;
        int currentFaceStart = -1;
        int currentFaceCount = -1;

        bool hasObject = false;
        ObjObject currentObject;
        for (const auto& meta : gdbModel.m_meta)
        {
            switch (meta.m_keyword)
            {
            case gdb::TOKEN_META_NEW_OBJECT:
                if (hasObject)
                {
                    hasObject = false;
                    currentVertexStart = -1;
                    currentVertexCount = -1;
                    lastVertexCountWasMax = false;
                    currentFaceStart = -1;
                    currentFaceCount = -1;
                    objModel->m_objects.emplace_back(std::move(currentObject));
                }

                if (meta.m_value0 >= 0 && static_cast<size_t>(meta.m_value0) <= gdbModel.m_materials.size())
                {
                    currentObject = CreateNewObject(*objModel, meta.m_value0);
                    hasObject = true;
                }
                else
                    assert(false);
                break;

            case gdb::TOKEN_META_ADD_VERTICES:
                if (meta.m_value1 >= 0 && meta.m_value2 >= 0 && static_cast<size_t>(meta.m_value1) + static_cast<size_t>(meta.m_value2) <= gdbModel.m_vertices.size())
                {
                    lastVertexCountWasMax = currentVertexCount == 64;
                    currentVertexStart = meta.m_value1;
                    currentVertexCount = meta.m_value2;
                }
                else
                    assert(false);

                AddVerticesToObject(gdbModel, currentObject, currentVertexStart, currentVertexCount);
                break;

            case gdb::TOKEN_META_FACES:
                if (meta.m_value0 >= 0 && meta.m_value1 >= 0 && static_cast<size_t>(meta.m_value0) + static_cast<size_t>(meta.m_value1) <= gdbModel.m_faces.size())
                {
                    currentFaceStart = meta.m_value0;
                    currentFaceCount = meta.m_value1;
                }
                else
                    assert(false);

                AddFacesToObject(gdbModel, currentObject, currentVertexStart, currentVertexCount, lastVertexCountWasMax, currentFaceStart, currentFaceCount);
                break;

            default:
                break;
            }
        }

        if (hasObject)
            objModel->m_objects.emplace_back(std::move(currentObject));

        for (const auto& material : gdbModel.m_materials)
        {
            // TODO: Assume color map name is image name
            objModel->m_materials.emplace_back(material, material);
        }

        return objModel;
    }

    bool WriteObjFile(const ObjWriter& writer, const fs::path& directory, const std::string& fileName)
    {
        fs::path outPath = directory / fileName;
        outPath.replace_extension(".OBJ");

        std::ofstream out(outPath, std::ios::out | std::ios::binary);
        if (!out.is_open())
        {
            std::cerr << "Failed to open output file: \"" << outPath << "\"\n";
            return false;
        }

        fs::path fileNameWithoutExtension(fileName);
        fileNameWithoutExtension.replace_extension(".MTL");

        writer.WriteObj(out, fileNameWithoutExtension.string());
        return true;
    }

    bool WriteMatFile(const ObjWriter& writer, const fs::path& directory, const std::string& fileName)
    {
        fs::path outPath = directory / fileName;
        outPath.replace_extension(".MTL");

        std::ofstream out(outPath, std::ios::out | std::ios::binary);
        if (!out.is_open())
        {
            std::cerr << "Failed to open output file: \"" << outPath << "\"\n";
            return false;
        }

        writer.WriteMat(out);
        return true;
    }
}

using namespace obj;

bool ObjExporter::SupportsExtension(const std::string& extensionName) const
{
    return extensionName == ".GDB";
}

bool ObjExporter::Convert(const std::string& directory, const std::string& filePath)
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

    const auto obj = CreateObjFromGdb(model);
    if (!obj)
        return false;

    const auto fileName = fsPath.filename().string();
    ObjWriter writer(*obj);
    if (!WriteObjFile(writer, directory, fileName) || !WriteMatFile(writer, directory, fileName))
        return false;

    return true;
}
