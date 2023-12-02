#include "GdbBinaryReader.h"

#include "TokenStream.h"

using namespace gdb;

namespace gdb
{
    class GdbBinaryReadingException final : public std::exception
    {
    public:
        explicit GdbBinaryReadingException(std::string msg)
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

    class GdbBinaryReaderImpl
    {
    public:
        GdbBinaryReaderImpl(std::istream& in, IGdbEmitter& emitter)
            : m_tokens(ITokenInputStream::Create(in)),
              m_emitter(emitter)
        {
        }

        void Read() const
        {
            for (auto nextSectionToken = m_tokens->NextValue(); nextSectionToken.m_type != TOKEN_INVALID && nextSectionToken.m_type != TOKEN_EOF;
                 nextSectionToken = m_tokens->NextValue())
            {
                switch (nextSectionToken.m_type)
                {
                case TOKEN_SECTION_MATERIAL:
                    ReadMaterialList();
                    break;

                case TOKEN_SECTION_VERTEX_WITH_POSITION_UV:
                    ReadVerticesWithPositionAndUv();
                    break;

                case TOKEN_SECTION_VERTEX_WITH_POSITION_UV_NORMAL:
                    ReadVerticesWithPositionAndUvAndNormal();
                    break;

                case TOKEN_SECTION_VERTEX_WITH_POSITION_UV_COLOR:
                    ReadVerticesWithPositionAndUvAndColor();
                    break;

                case TOKEN_SECTION_INDICES:
                    ReadFaces();
                    break;

                case TOKEN_SECTION_VERTEX_META:
                    ReadVertexMeta();
                    break;

                case TOKEN_SCALE:
                    ReadScale();
                    break;

                case TOKEN_SECTION_VERTEX_WITH_POSITION:
                    ReadVerticesWithPosition();
                    break;

                default:
                    throw GdbBinaryReadingException("Unknown keyword for section");
                }
            }
        }

    private:
        void ReadMaterialList() const
        {
            m_emitter.StartMaterials();

            const auto materialCount = ReadCountInCurlyBraces();
            for (auto materialIndex = 0; materialIndex < materialCount; materialIndex++)
            {
                auto materialName = m_tokens->NextStringValue();

                m_emitter.EmitMaterial(std::move(materialName));
            }

            m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);

            m_emitter.EndMaterials();
        }

        void ReadVerticesWithPositionAndUv() const
        {
            m_emitter.StartVertices();

            const auto vertexCount = ReadCountInCurlyBraces();
            for (auto index = 0; index < vertexCount; index++)
            {
                Vec3 position;
                position.x = m_tokens->NextFloatValue();
                position.y = m_tokens->NextFloatValue();
                position.z = m_tokens->NextFloatValue();

                Vec2 uv;
                uv.x = m_tokens->NextFloatValue();
                uv.y = m_tokens->NextFloatValue();

                m_emitter.EmitVertex(position, uv);
            }

            m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);

            m_emitter.EndVertices();
        }

        void ReadVerticesWithPositionAndUvAndNormal() const
        {
            m_emitter.StartVertices();

            const auto vertexCount = ReadCountInCurlyBraces();
            for (auto index = 0; index < vertexCount; index++)
            {
                Vec3 position;
                position.x = m_tokens->NextFloatValue();
                position.y = m_tokens->NextFloatValue();
                position.z = m_tokens->NextFloatValue();

                Vec2 uv;
                uv.x = m_tokens->NextFloatValue();
                uv.y = m_tokens->NextFloatValue();

                Vec3 normal;
                normal.x = m_tokens->NextFloatValue();
                normal.y = m_tokens->NextFloatValue();
                normal.z = m_tokens->NextFloatValue();

                m_emitter.EmitVertex(position, uv, normal);
            }

            m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);

            m_emitter.EndVertices();
        }

        void ReadVerticesWithPositionAndUvAndColor() const
        {
            m_emitter.StartVertices();

            const auto vertexCount = ReadCountInCurlyBraces();
            for (auto index = 0; index < vertexCount; index++)
            {
                Vec3 position;
                position.x = m_tokens->NextFloatValue();
                position.y = m_tokens->NextFloatValue();
                position.z = m_tokens->NextFloatValue();

                Vec2 uv;
                uv.x = m_tokens->NextFloatValue();
                uv.y = m_tokens->NextFloatValue();

                Color4 color;
                color.r = static_cast<uint8_t>(m_tokens->NextIntegerValue());
                color.g = static_cast<uint8_t>(m_tokens->NextIntegerValue());
                color.b = static_cast<uint8_t>(m_tokens->NextIntegerValue());
                color.a = static_cast<uint8_t>(m_tokens->NextIntegerValue());

                m_emitter.EmitVertex(position, uv, color);
            }

            m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);

            m_emitter.EndVertices();
        }

        void ReadVerticesWithPosition() const
        {
            m_emitter.StartVertices();

            const auto vertexCount = ReadCountInCurlyBraces();
            for (auto index = 0; index < vertexCount; index++)
            {
                Vec3 position;
                position.x = m_tokens->NextFloatValue();
                position.y = m_tokens->NextFloatValue();
                position.z = m_tokens->NextFloatValue();

                m_emitter.EmitVertex(position);
            }

            m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);

            m_emitter.EndVertices();
        }

        void ReadFaces() const
        {
            m_emitter.StartFaces();

            const auto faceCount = ReadCountInCurlyBraces();
            for (auto index = 0; index < faceCount; index++)
            {
                const auto vertex0 = static_cast<unsigned int>(m_tokens->NextIntegerValue());
                const auto vertex1 = static_cast<unsigned int>(m_tokens->NextIntegerValue());
                const auto vertex2 = static_cast<unsigned int>(m_tokens->NextIntegerValue());

                m_emitter.EmitFace(vertex0, vertex1, vertex2);
            }

            m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);

            m_emitter.EndFaces();
        }

        void ReadVertexMeta() const
        {
            m_emitter.StartMeta();

            const auto metaCount = ReadCountInCurlyBraces();

            for (auto index = 0; index < metaCount; index++)
            {
                switch (m_tokens->NextValue().m_type)
                {
                case TOKEN_META_VERTICES:
                {
                    const auto value0 = m_tokens->NextIntegerValue();
                    const auto value1 = m_tokens->NextIntegerValue();
                    const auto value2 = m_tokens->NextIntegerValue();

                    m_emitter.EmitMetaSelectVertices(value0, value1, value2);
                }
                break;
                case TOKEN_META_FACES:
                {
                    const auto value0 = m_tokens->NextIntegerValue();
                    const auto value1 = m_tokens->NextIntegerValue();

                    m_emitter.EmitMetaAddFaces(value0, value1);
                }
                break;
                case TOKEN_META_2F:
                {
                    const auto value0 = m_tokens->NextIntegerValue();

                    m_emitter.EmitMetaKeyword2F(value0);
                }
                break;
                case TOKEN_META_30:
                {
                    m_emitter.EmitMetaKeyword30();
                }
                break;
                case TOKEN_META_BONE:
                {
                    const auto value0 = m_tokens->NextIntegerValue();

                    m_emitter.EmitMetaBone(value0);
                }
                break;
                case TOKEN_META_NEW_OBJECT:
                {
                    const auto value0 = m_tokens->NextIntegerValue();

                    m_emitter.EmitMetaNewObject(value0);
                }
                break;
                default:
                    throw GdbBinaryReadingException("Unknown keyword for vertex meta");
                }
            }

            m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);

            m_emitter.EndMeta();
        }

        void ReadScale() const
        {
            const auto scaleValue = m_tokens->NextFloatValue();
            m_emitter.EmitScale(scaleValue);
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
        IGdbEmitter& m_emitter;
    };
} // namespace gdb

void GdbBinaryReader::Read(std::istream& input, IGdbEmitter& emitter)
{
    GdbBinaryReaderImpl impl(input, emitter);
    impl.Read();
}
