#include "GdbDumper.h"

#include <cassert>
#include <iostream>
#include <vector>
#include <array>

#include "Gdb.h"
#include "TokenStream.h"
#include "Utils/AbstractTextDumper.h"

namespace gdb
{
    class GdbDumpingException final : public std::exception
    {
    public:
        explicit GdbDumpingException(char const* msg)
            : exception(msg)
        {
        }
    };

    struct Vec2
    {
        float x;
        float y;

        Vec2()
        {
            x = 0.0f;
            y = 0.0f;
        }
    };

    struct Vec3
    {
        float x;
        float y;
        float z;

        Vec3()
        {
            x = 0.0f;
            y = 0.0f;
            z = 0.0f;
        }
    };

    struct ModelFace
    {
        unsigned char indices[4];

        ModelFace()
            : indices{}
        {
        }
    };

    struct Vertex
    {
        Vec3 m_position;
        Vec2 m_uv;
        Vec3 m_color;
        unsigned char m_unknown[4];

        Vertex()
            : m_unknown{}
        {
        }
    };
}

using namespace gdb;

class GdbTextOutputStream final : public AbstractTokenTextDumper
{
public:
    GdbTextOutputStream(std::istream& in, std::ostream& out)
        : AbstractTokenTextDumper(out),
          m_tokens(ITokenInputStream::Create(in)),
          m_scale_value(0.0f)
    {
    }

    void Write()
    {
        for (auto nextSectionToken = m_tokens->NextValue(); nextSectionToken.m_type != TOKEN_INVALID && nextSectionToken.m_type != TOKEN_EOF; nextSectionToken = m_tokens->NextValue())
        {
            switch (nextSectionToken.m_type)
            {
            case TOKEN_MATERIAL:
                HandleMaterialList();
                break;

            case TOKEN_SECTION28:
                LoadVerticesWithPositionAndUv();
                break;

            case TOKEN_SECTION29:
                LoadVerticesWithPositionAndUvAndColor();
                break;

            case TOKEN_SECTION2A:
                LoadVerticesWithPositionAndUvAndUnknown();
                break;

            case TOKEN_INDICES:
                LoadIndices();
                break;

            case TOKEN_SECTION2E:
                LoadVertexMeta();
                break;

            case TOKEN_SECTION33:
                LoadScale();
                break;

            case TOKEN_SECTION34:
                LoadVerticesWithPosition();
                break;

            default:
                throw GdbDumpingException("Unknown keyword for section");
            }
        }
    }

private:
    void HandleMaterialList()
    {
        const auto materialCount = ReadCountInCurlyBraces();
        for (auto materialIndex = 0; materialIndex < materialCount; materialIndex++)
        {
            auto materialName = m_tokens->NextStringValue();
            std::cout << "Material in model: \"" << materialName << "\"\n";
            m_materials.emplace_back(std::move(materialName));
        }

        m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);
    }

    void LoadVerticesWithPositionAndUv()
    {
        assert(m_vertices.empty());
        const auto vertexCount = ReadCountInCurlyBraces();

        m_vertices.resize(vertexCount);
        for (auto index = 0; index < vertexCount; index++)
        {
            Vertex& v = m_vertices[index];
            v.m_position.x = m_tokens->NextFloatValue();
            v.m_position.y = m_tokens->NextFloatValue();
            v.m_position.z = m_tokens->NextFloatValue();

            v.m_uv.x = m_tokens->NextFloatValue();
            v.m_uv.y = m_tokens->NextFloatValue();
        }

        m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);
    }

    void LoadVerticesWithPositionAndUvAndColor()
    {
        assert(m_vertices.empty());
        const auto vertexCount = ReadCountInCurlyBraces();

        m_vertices.resize(vertexCount);
        for (auto index = 0; index < vertexCount; index++)
        {
            Vertex& v = m_vertices[index];
            v.m_position.x = m_tokens->NextFloatValue();
            v.m_position.y = m_tokens->NextFloatValue();
            v.m_position.z = m_tokens->NextFloatValue();

            v.m_uv.x = m_tokens->NextFloatValue();
            v.m_uv.y = m_tokens->NextFloatValue();

            v.m_color.x = m_tokens->NextFloatValue();
            v.m_color.y = m_tokens->NextFloatValue();
            v.m_color.z = m_tokens->NextFloatValue();
        }

        m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);
    }

    void LoadVerticesWithPositionAndUvAndUnknown()
    {
        assert(m_vertices.empty());
        const auto vertexCount = ReadCountInCurlyBraces();

        m_vertices.resize(vertexCount);
        for (auto index = 0; index < vertexCount; index++)
        {
            Vertex& v = m_vertices[index];
            v.m_position.x = m_tokens->NextFloatValue();
            v.m_position.y = m_tokens->NextFloatValue();
            v.m_position.z = m_tokens->NextFloatValue();

            v.m_uv.x = m_tokens->NextFloatValue();
            v.m_uv.y = m_tokens->NextFloatValue();

            v.m_unknown[0] = m_tokens->NextIntegerValue();
            v.m_unknown[1] = m_tokens->NextIntegerValue();
            v.m_unknown[2] = m_tokens->NextIntegerValue();
            v.m_unknown[3] = m_tokens->NextIntegerValue();
        }

        m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);
    }

    void LoadVerticesWithPosition()
    {
        const auto vertexCount = ReadCountInCurlyBraces();

        m_vertices.resize(vertexCount);
        for (auto index = 0; index < vertexCount; index++)
        {
            Vertex& v = m_vertices[index];
            v.m_position.x = m_tokens->NextFloatValue();
            v.m_position.y = m_tokens->NextFloatValue();
            v.m_position.z = m_tokens->NextFloatValue();
        }

        m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);
    }

    void LoadIndices()
    {
        const auto indexCount = ReadCountInCurlyBraces();
        m_faces.resize(indexCount);

        for (auto index = 0; index < indexCount; index++)
        {
            m_faces[index].indices[0] = static_cast<unsigned char>(m_tokens->NextIntegerValue());
            m_faces[index].indices[1] = static_cast<unsigned char>(m_tokens->NextIntegerValue());
            m_faces[index].indices[2] = static_cast<unsigned char>(m_tokens->NextIntegerValue());
            m_faces[index].indices[3] = 0;
        }

        m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);
    }

    void LoadVertexMeta()
    {
        // Vertex defs?
        const auto metaCount = ReadCountInCurlyBraces();

        for (auto index = 0; index < metaCount; index++)
        {
            switch (m_tokens->NextValue().m_type)
            {
            case TOKEN_31:
                {
                    const auto value0 = m_tokens->NextIntegerValue();
                    const auto value1 = m_tokens->NextIntegerValue();
                    const auto value2 = m_tokens->NextIntegerValue();
                    std::cout << "Token31: " << value0 << " " << value1 << " " << value2 << "\n";
                }
                break;
            case TOKEN_INDICES:
                {
                    const auto value0 = m_tokens->NextIntegerValue();
                    const auto value1 = m_tokens->NextIntegerValue();
                    std::cout << "Token2D: " << value0 << " " << value1 << "\n";
                }
                break;
            case TOKEN_2F:
                {
                    const auto value0 = m_tokens->NextIntegerValue();
                    std::cout << "Token2F: " << value0 << "\n";
                }
                break;
            case TOKEN_30:
                {
                    std::cout << "Token30: " << "\n";
                }
                break;
            case TOKEN_32:
                {
                    const auto value0 = m_tokens->NextIntegerValue();
                    std::cout << "Token32: " << value0 << "\n";
                }
                break;
            case TOKEN_MATERIAL:
                {
                    const auto value0 = m_tokens->NextIntegerValue();
                    assert(value0 >= 0 && value0 < m_materials.size());
                    std::cout << "TokenMaterial: " << value0 << "\n";
                }
                break;
            default:
                throw GdbDumpingException("Unknown keyword for vertex");
            }
        }

        m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);
    }

    void LoadScale()
    {
        m_scale_value = m_tokens->NextFloatValue();
    }

    [[nodiscard]] int ReadCountInCurlyBraces() const
    {
        m_tokens->ExpectToken(TOKEN_LEFT_BRACKET);
        const auto materialCount = m_tokens->NextIntegerValue();
        m_tokens->ExpectToken(TOKEN_RIGHT_BRACKET);
        m_tokens->ExpectToken(TOKEN_LEFT_CURLY);
        return materialCount;
    }

    std::unique_ptr<ITokenInputStream> m_tokens;
    std::vector<std::string> m_materials;
    std::vector<ModelFace> m_faces;
    std::vector<Vertex> m_vertices;
    float m_scale_value;
};

bool GdbDumper::SupportFileExtension(const std::string& extension) const
{
    return extension == ".GDB";
}

void GdbDumper::ProcessFile(const std::string& filePath, std::istream& input, std::ostream& output) const
{
    std::cout << "GDB dumping \"" << filePath << "\"\n";

    GdbTextOutputStream out(input, output);
    out.Write();
}
