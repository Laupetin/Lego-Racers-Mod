#include "ObjReader.h"

#include <cassert>
#include <unordered_map>

#include "Utils/AbstractTextReader.h"

using namespace obj;

namespace obj
{
    class ObjReaderImpl final : public ObjReader, AbstractTextReader
    {
    public:
        explicit ObjReaderImpl(std::istream& stream)
            : AbstractTextReader(stream),
              m_object_defined(false),
              m_object_vertex_offset(0u),
              m_object_uv_offset(0u),
              m_object_normal_offset(0u)
        {
        }

        std::unique_ptr<ObjModel> ReadModel() override
        {
            m_model = std::make_unique<ObjModel>();

            if (m_object_defined || !m_current_object.m_vertices.empty() || !m_current_object.m_uvs.empty() || !m_current_object.m_normals.empty())
                m_model->m_objects.emplace_back(std::move(m_current_object));

            if (!ReadNext())
                return nullptr;

            return std::move(m_model);
        }

    private:
        void NextObject(std::string name)
        {
            if (m_object_defined || !m_current_object.m_vertices.empty() || !m_current_object.m_uvs.empty() || !m_current_object.m_normals.empty())
            {
                m_object_vertex_offset += m_current_object.m_vertices.size();
                m_object_uv_offset += m_current_object.m_uvs.size();
                m_object_normal_offset += m_current_object.m_normals.size();

                m_model->m_objects.emplace_back(std::move(m_current_object));
            }

            m_current_object = ObjObject(std::move(name), -1);
            m_object_defined = true;
        }

        bool ReadNext()
        {
            while (!m_stream.eof())
            {
                if (!SkipWhitespaceNoNewline())
                    return false;

                if (ConsumeIfLineEnd())
                    continue;

                if (SkipComment())
                {
                    if (!ExpectLineEnd())
                        return false;
                    continue;
                }

                std::string identifier;
                if (!ReadIdentifier(identifier))
                {
                    SkipUnknownLine();
                    continue;
                }

                if (identifier[0] == 'v' && identifier[1] == '\0')
                {
                    float x, y, z;
                    if (!SkipWhitespaceNoNewline() || !ReadFloatingPoint(x)
                        || !SkipWhitespaceNoNewline() || !ReadFloatingPoint(y)
                        || !SkipWhitespaceNoNewline() || !ReadFloatingPoint(z))
                    {
                        return false;
                    }

                    m_current_object.m_vertices.emplace_back(x, y, z);
                }
                else if (identifier[0] == 'v' && identifier[1] == 't' && identifier[2] == '\0')
                {
                    float u, v;
                    if (!SkipWhitespaceNoNewline() || !ReadFloatingPoint(u)
                        || !SkipWhitespaceNoNewline() || !ReadFloatingPoint(v))
                    {
                        return false;
                    }

                    m_current_object.m_uvs.emplace_back(u, v);
                }
                else if (identifier[0] == 'v' && identifier[1] == 'n' && identifier[2] == '\0')
                {
                    float x, y, z;
                    if (!SkipWhitespaceNoNewline() || !ReadFloatingPoint(x)
                        || !SkipWhitespaceNoNewline() || !ReadFloatingPoint(y)
                        || !SkipWhitespaceNoNewline() || !ReadFloatingPoint(z))
                    {
                        return false;
                    }

                    m_current_object.m_normals.emplace_back(x, y, z);
                }
                else if (identifier[0] == 'f' && identifier[1] == '\0')
                {
                    if (!ReadFace())
                        return false;
                }
                else if (identifier[0] == 'o' && identifier[1] == '\0')
                {
                    std::string objectName;
                    if (!SkipWhitespaceNoNewline() || !ReadIdentifier(objectName) || !SkipWhitespaceNoNewline() || !ExpectLineEnd())
                        return false;
                    NextObject(objectName);
                }
                else if (identifier == "usemtl")
                {
                    std::string materialName;
                    if (!SkipWhitespaceNoNewline() || !ReadIdentifier(materialName) || !SkipWhitespaceNoNewline() || !ExpectLineEnd())
                        return false;

                    const auto existingMaterial = m_used_materials.find(materialName);
                    if (existingMaterial == m_used_materials.end())
                    {
                        const auto newMaterialIndex = m_model->m_materials.size();
                        m_current_object.m_material_index = static_cast<int>(newMaterialIndex);
                        m_model->m_materials.emplace_back(materialName);
                        m_used_materials.emplace(std::move(materialName), newMaterialIndex);
                    }
                    else
                    {
                        m_current_object.m_material_index = static_cast<int>(existingMaterial->second);
                    }
                }
                else
                    SkipUnknownLine();
            }

            return true;
        }

        bool SkipComment()
        {
            auto c = NextChar();
            if (c != '#')
            {
                SetPeeked(c);
                return false;
            }

            c = m_stream.get();
            while (c != '\n' && c != EOF)
            {
                c = m_stream.get();
            }

            return true;
        }

        bool ReadFace()
        {
            int vertexIndices[3];
            int uvIndices[3];
            int normalIndices[3];

            if (!SkipWhitespaceNoNewline() || !ReadFaceIndices(vertexIndices[0], uvIndices[0], normalIndices[0])
                || !SkipWhitespaceNoNewline() || !ReadFaceIndices(vertexIndices[1], uvIndices[1], normalIndices[1])
                || !SkipWhitespaceNoNewline() || !ReadFaceIndices(vertexIndices[2], uvIndices[2], normalIndices[2]))
            {
                return false;
            }

            if (!SkipWhitespaceNoNewline() || !ExpectLineEnd())
            {
                // Only supports tris
                return false;
            }

            const auto hasUvs = uvIndices[0] >= 0 && uvIndices[1] >= 0 && uvIndices[2] >= 0;
            const auto hasNormals = normalIndices[0] >= 0 && normalIndices[1] >= 0 && normalIndices[2] >= 0;
            if (hasNormals && !hasUvs)
                return false;

            if (static_cast<size_t>(vertexIndices[0]) < m_object_vertex_offset
                || static_cast<size_t>(vertexIndices[1]) < m_object_vertex_offset
                || static_cast<size_t>(vertexIndices[2]) < m_object_vertex_offset)
            {
                return false;
            }

            if (hasUvs)
            {
                if (static_cast<size_t>(uvIndices[0]) < m_object_uv_offset
                    || static_cast<size_t>(uvIndices[1]) < m_object_uv_offset
                    || static_cast<size_t>(uvIndices[2]) < m_object_uv_offset)
                {
                    return false;
                }

                if (hasNormals)
                {
                    if (static_cast<size_t>(normalIndices[0]) < m_object_normal_offset
                        || static_cast<size_t>(normalIndices[1]) < m_object_normal_offset
                        || static_cast<size_t>(normalIndices[2]) < m_object_normal_offset)
                    {
                        return false;
                    }

                    m_current_object.m_faces.emplace_back(vertexIndices[0] - m_object_vertex_offset, uvIndices[0] - m_object_uv_offset, normalIndices[0] - m_object_normal_offset,
                                                          vertexIndices[1] - m_object_vertex_offset, uvIndices[1] - m_object_uv_offset, normalIndices[1] - m_object_normal_offset,
                                                          vertexIndices[2] - m_object_vertex_offset, uvIndices[2] - m_object_uv_offset, normalIndices[2] - m_object_normal_offset);
                }
                else
                {
                    m_current_object.m_faces.emplace_back(vertexIndices[0] - m_object_vertex_offset, uvIndices[0] - m_object_uv_offset,
                                                          vertexIndices[1] - m_object_vertex_offset, uvIndices[1] - m_object_uv_offset,
                                                          vertexIndices[2] - m_object_vertex_offset, uvIndices[2] - m_object_uv_offset);
                }
            }
            else
            {
                m_current_object.m_faces.emplace_back(vertexIndices[0] - m_object_vertex_offset,
                                                      vertexIndices[1] - m_object_vertex_offset,
                                                      vertexIndices[2] - m_object_vertex_offset);
            }

            return true;
        }

        bool ReadFaceIndices(int& vertexIndex, int& uvIndex, int& normalIndex)
        {
            if (!ReadIntegerValue(vertexIndex))
                return false;

            auto c = NextChar();
            if (c == '/')
            {
                c = m_stream.get();
                if (c != '/')
                {
                    SetPeeked(c);
                    if (!ReadIntegerValue(uvIndex))
                        return false;
                }

                c = NextChar();
                if (c == '/')
                {
                    if (!ReadIntegerValue(normalIndex))
                        return false;
                }
                else
                {
                    SetPeeked(c);
                    normalIndex = -1;
                }
            }
            else
            {
                SetPeeked(c);
                uvIndex = -1;
                normalIndex = -1;
            }

            return true;
        }

        void SkipUnknownLine()
        {
            auto c = NextChar();
            while (c != '\n' && c != EOF)
            {
                c = m_stream.get();
            }
        }

        bool ConsumeIfLineEnd()
        {
            const auto c = NextChar();
            if (c == EOF || c == '\n')
                return true;

            SetPeeked(c);
            return false;
        }

        bool ExpectLineEnd()
        {
            const auto c = NextChar();
            return c == EOF || c == '\n';
        }

        std::unique_ptr<ObjModel> m_model;
        std::unordered_map<std::string, size_t> m_used_materials;
        ObjObject m_current_object;
        bool m_object_defined;
        size_t m_object_vertex_offset;
        size_t m_object_uv_offset;
        size_t m_object_normal_offset;
    };
}

std::unique_ptr<ObjReader> ObjReader::Create(std::istream& in)
{
    return std::make_unique<ObjReaderImpl>(in);
}
