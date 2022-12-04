#include "ObjReader.h"

#include <algorithm>
#include <cassert>
#include <exception>
#include <iostream>
#include <sstream>
#include <unordered_map>

#include "Utils/AbstractTextReader.h"

using namespace obj;

namespace obj
{
    class ObjReadingException final : public std::exception
    {
    public:
        explicit ObjReadingException(std::string msg)
            : m_msg(std::move(msg))
        {
        }

        [[nodiscard]] char const* what() const noexcept override
        {
            return m_msg.c_str();
        }

    private:
        std::string m_msg;
    };

    class ObjReaderImpl final : public ObjReader, AbstractTextReader
    {
    public:
        explicit ObjReaderImpl(std::istream& stream)
            : AbstractTextReader(stream),
              m_line(1u),
              m_object_defined(false),
              m_object_vertex_offset(0u),
              m_object_uv_offset(0u),
              m_object_normal_offset(0u),
              m_has_colors(false)
        {
        }

        std::unique_ptr<ObjModel> ReadModel() override
        {
            try
            {
                m_model = std::make_unique<ObjModel>();

                ReadData();

                AddCurrentObject();

                return std::move(m_model);
            }
            catch (ObjReadingException& e)
            {
                std::cerr << "Obj reading error: " << e.what() << "\n";
            }

            return nullptr;
        }

        [[nodiscard]] bool HasColors() const override
        {
            return m_has_colors;
        }

    private:
        void NextObject(std::string name)
        {
            AddCurrentObject();

            m_current_object = ObjObject(std::move(name), -1);
            m_object_defined = true;
        }

        void AddCurrentObject()
        {
            if (m_object_defined || !m_current_object.m_vertices.empty() || !m_current_object.m_uvs.empty() || !m_current_object.m_normals.empty())
            {
                m_object_vertex_offset += m_current_object.m_vertices.size();
                m_object_uv_offset += m_current_object.m_uvs.size();
                m_object_normal_offset += m_current_object.m_normals.size();

                m_model->m_objects.emplace_back(std::move(m_current_object));
            }
        }

        void ReadData()
        {
            while (!m_stream.eof())
            {
                SkipWhitespaceNoNewline();

                if (ConsumeIfLineEnd())
                    continue;

                if (SkipComment())
                {
                    if (!ExpectLineEnd())
                        ReportError("Expected newline after comment");
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
                    float r, g, b;
                    if (!SkipWhitespaceNoNewline() || !ReadFloatingPoint(x)
                        || !SkipWhitespaceNoNewline() || !ReadFloatingPoint(y)
                        || !SkipWhitespaceNoNewline() || !ReadFloatingPoint(z))
                    {
                        ReportError("Invalid vertex");
                    }

                    if (SkipWhitespaceNoNewline() && ReadFloatingPoint(r)
                        && SkipWhitespaceNoNewline() && ReadFloatingPoint(g)
                        && SkipWhitespaceNoNewline() && ReadFloatingPoint(b))
                    {
                        m_current_object.m_vertices.emplace_back(x, y, z,
                                                                 std::clamp(r, 0.0f, 1.0f),
                                                                 std::clamp(g, 0.0f, 1.0f),
                                                                 std::clamp(b, 0.0f, 1.0f));
                        m_has_colors = true;
                    }
                    else
                    {
                        m_current_object.m_vertices.emplace_back(x, y, z);
                    }
                }
                else if (identifier[0] == 'v' && identifier[1] == 't' && identifier[2] == '\0')
                {
                    float u, v;
                    if (!SkipWhitespaceNoNewline() || !ReadFloatingPoint(u)
                        || !SkipWhitespaceNoNewline() || !ReadFloatingPoint(v))
                    {
                        ReportError("Invalid uv");
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
                        ReportError("Invalid normal");
                    }

                    m_current_object.m_normals.emplace_back(x, y, z);
                }
                else if (identifier[0] == 'f' && identifier[1] == '\0')
                {
                    ReadFace();
                }
                else if (identifier[0] == 'o' && identifier[1] == '\0')
                {
                    std::string objectName;
                    if (!SkipWhitespaceNoNewline() || !ReadIdentifier(objectName) || !SkipWhitespaceNoNewline() || !ExpectLineEnd())
                        ReportError("Invalid object");

                    NextObject(objectName);
                }
                else if (identifier == "usemtl")
                {
                    std::string materialName;
                    if (!SkipWhitespaceNoNewline() || !ReadIdentifier(materialName) || !SkipWhitespaceNoNewline() || !ExpectLineEnd())
                        ReportError("Invalid material");

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

            SetPeeked(c);
            return true;
        }

        void ReadFace()
        {
            int vertexIndices[3];
            int uvIndices[3];
            int normalIndices[3];

            if (!SkipWhitespaceNoNewline() || !ReadFaceIndices(vertexIndices[0], uvIndices[0], normalIndices[0])
                || !SkipWhitespaceNoNewline() || !ReadFaceIndices(vertexIndices[1], uvIndices[1], normalIndices[1])
                || !SkipWhitespaceNoNewline() || !ReadFaceIndices(vertexIndices[2], uvIndices[2], normalIndices[2]))
            {
                ReportError("Invalid vertex indices");
            }

            if (!SkipWhitespaceNoNewline() || !ExpectLineEnd())
            {
                // Only supports tris
                ReportError("Only tris are supported");
            }

            const auto hasUvs = uvIndices[0] >= 0 && uvIndices[1] >= 0 && uvIndices[2] >= 0;
            const auto hasNormals = normalIndices[0] >= 0 && normalIndices[1] >= 0 && normalIndices[2] >= 0;
            if (hasNormals && !hasUvs)
                ReportError("Does not support faces with normals but without uvs");

            if (static_cast<size_t>(vertexIndices[0]) < m_object_vertex_offset || static_cast<size_t>(vertexIndices[0]) >= m_object_vertex_offset + m_current_object.m_vertices.size()
                || static_cast<size_t>(vertexIndices[1]) < m_object_vertex_offset || static_cast<size_t>(vertexIndices[1]) >= m_object_vertex_offset + m_current_object.m_vertices.size()
                || static_cast<size_t>(vertexIndices[2]) < m_object_vertex_offset || static_cast<size_t>(vertexIndices[2]) >= m_object_vertex_offset + m_current_object.m_vertices.size())
            {
                ReportError("Face vertex out of bounds");
            }

            if (hasUvs)
            {
                if (static_cast<size_t>(uvIndices[0]) < m_object_uv_offset || static_cast<size_t>(uvIndices[0]) >= m_object_uv_offset + m_current_object.m_uvs.size()
                    || static_cast<size_t>(uvIndices[1]) < m_object_uv_offset || static_cast<size_t>(uvIndices[1]) >= m_object_uv_offset + m_current_object.m_uvs.size()
                    || static_cast<size_t>(uvIndices[2]) < m_object_uv_offset || static_cast<size_t>(uvIndices[2]) >= m_object_uv_offset + m_current_object.m_uvs.size())
                {
                    ReportError("Face uv out of bounds");
                }

                if (hasNormals)
                {
                    if (static_cast<size_t>(normalIndices[0]) < m_object_normal_offset || static_cast<size_t>(normalIndices[0]) >= m_object_normal_offset + m_current_object.m_normals.size()
                        || static_cast<size_t>(normalIndices[1]) < m_object_normal_offset || static_cast<size_t>(normalIndices[1]) >= m_object_normal_offset + m_current_object.m_normals.size()
                        || static_cast<size_t>(normalIndices[2]) < m_object_normal_offset || static_cast<size_t>(normalIndices[2]) >= m_object_normal_offset + m_current_object.m_normals.size())
                    {
                        ReportError("Face normal out of bounds");
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
        }

        bool ReadFaceIndices(int& vertexIndex, int& uvIndex, int& normalIndex)
        {
            if (!ReadIntegerValue(vertexIndex) || vertexIndex <= 0)
                return false;
            vertexIndex--;

            auto c = NextChar();
            if (c == '/')
            {
                c = m_stream.get();
                if (c != '/')
                {
                    SetPeeked(c);
                    if (!ReadIntegerValue(uvIndex) || uvIndex <= 0)
                        return false;
                    uvIndex--;
                }

                c = NextChar();
                if (c == '/')
                {
                    if (!ReadIntegerValue(normalIndex) || normalIndex <= 0)
                        return false;
                    normalIndex--;
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

            m_line++;
        }

        bool ConsumeIfLineEnd()
        {
            const auto c = NextChar();
            if (c == EOF || c == '\n')
            {
                m_line++;
                return true;
            }

            SetPeeked(c);
            return false;
        }

        bool ExpectLineEnd()
        {
            const auto c = NextChar();
            if (c == EOF || c == '\n')
            {
                m_line++;
                return true;
            }

            return false;
        }

        [[noreturn]] void ReportError(const char* msg) const
        {
            std::ostringstream ss;
            ss << "L" << m_line << ": " << msg;

            throw ObjReadingException(ss.str());
        }

        size_t m_line;
        std::unique_ptr<ObjModel> m_model;
        std::unordered_map<std::string, size_t> m_used_materials;
        ObjObject m_current_object;
        bool m_object_defined;
        size_t m_object_vertex_offset;
        size_t m_object_uv_offset;
        size_t m_object_normal_offset;
        bool m_has_colors;
    };
}

std::unique_ptr<ObjReader> ObjReader::Create(std::istream& in)
{
    return std::make_unique<ObjReaderImpl>(in);
}
