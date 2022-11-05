#include "MdbBinaryReader.h"

#include "TokenStream.h"

using namespace mdb;

namespace mdb
{
    class MdbBinaryReadingException final : public std::exception
    {
    public:
        explicit MdbBinaryReadingException(char const* msg)
            : exception(msg)
        {
        }
    };

    class MdbBinaryReaderImpl
    {
    public:
        MdbBinaryReaderImpl(std::istream& in, IMdbEmitter& emitter)
            : m_tokens(ITokenInputStream::Create(in)),
              m_emitter(emitter)
        {
        }

        void Read() const
        {
            m_tokens->ExpectToken(TOKEN_MATERIAL_DB);
            m_emitter.StartMaterials();

            const auto materialCount = ReadMaterialCount();
            for (auto materialIndex = 0; materialIndex < materialCount; materialIndex++)
            {
                m_tokens->ExpectToken(TOKEN_MATERIAL);
                const auto materialName = m_tokens->NextStringValue();
                m_tokens->ExpectToken(TOKEN_LEFT_CURLY);
                m_emitter.StartMaterial(materialName);

                while (ProcessMaterialToken())
                {
                    // Next token
                }

                m_emitter.EndMaterial();
            }

            m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);
            m_emitter.EndMaterials();
        }

    private:
        [[nodiscard]] int ReadMaterialCount() const
        {
            m_tokens->ExpectToken(TOKEN_LEFT_BRACKET);
            const auto materialCount = m_tokens->NextIntegerValue();
            m_tokens->ExpectToken(TOKEN_RIGHT_BRACKET);
            m_tokens->ExpectToken(TOKEN_LEFT_CURLY);
            return materialCount;
        }

        void ProcessKeyword2F() const
        {
            const auto token = m_tokens->NextValue();

            switch (token.m_type)
            {
            case TOKEN_KEYWORD_2F_SUB_30:
            case TOKEN_KEYWORD_2F_SUB_36:
                m_emitter.EmitKeyword2F(static_cast<MaterialToken>(token.m_type), 0);
                break;

            case TOKEN_KEYWORD_2F_SUB_31:
            case TOKEN_KEYWORD_2F_SUB_32:
            case TOKEN_KEYWORD_2F_SUB_33:
            case TOKEN_KEYWORD_2F_SUB_34:
            case TOKEN_KEYWORD_2F_SUB_35:
            case TOKEN_KEYWORD_2F_SUB_37:
                m_emitter.EmitKeyword2F(static_cast<MaterialToken>(token.m_type), m_tokens->NextIntegerValue());
                break;

            default:
                break;
            }
        }

        void ProcessKeyword38() const
        {
            MaterialToken tokens[2];

            for (auto& i : tokens)
            {
                const auto token = m_tokens->NextValue();

                switch (token.m_type)
                {
                case TOKEN_KEYWORD_38_SUB_39:
                case TOKEN_KEYWORD_38_SUB_3A:
                case TOKEN_KEYWORD_38_SUB_3B:
                case TOKEN_KEYWORD_38_SUB_3C:
                case TOKEN_KEYWORD_38_SUB_3D:
                case TOKEN_KEYWORD_38_SUB_3E:
                case TOKEN_KEYWORD_38_SUB_3F:
                case TOKEN_KEYWORD_38_SUB_40:
                case TOKEN_KEYWORD_38_SUB_41:
                case TOKEN_KEYWORD_38_SUB_42:
                case TOKEN_KEYWORD_38_SUB_43:
                    i = static_cast<MaterialToken>(token.m_type);
                    break;

                default:
                    throw MdbBinaryReadingException("Unknown keyword for keyword38");
                }
            }

            m_emitter.EmitKeyword38(tokens[0], tokens[1]);
        }

        [[nodiscard]] bool ProcessMaterialToken() const
        {
            const auto token = m_tokens->NextValue();
            if (token.m_type == TOKEN_EOF || token.m_type == TOKEN_RIGHT_CURLY)
                return false;

            switch (token.m_type)
            {
            case TOKEN_KEYWORD_COLOR_1:
                {
                    const auto value0 = m_tokens->NextIntegerValue();
                    const auto value1 = m_tokens->NextIntegerValue();
                    const auto value2 = m_tokens->NextIntegerValue();
                    const auto value3 = m_tokens->NextIntegerValue();
                    m_emitter.EmitColor1(value0, value1, value2, value3);
                    break;
                }

            case TOKEN_KEYWORD_COLOR_0:
                {
                    const auto value0 = m_tokens->NextIntegerValue();
                    const auto value1 = m_tokens->NextIntegerValue();
                    const auto value2 = m_tokens->NextIntegerValue();
                    const auto value3 = m_tokens->NextIntegerValue();
                    m_emitter.EmitColor0(value0, value1, value2, value3);
                    break;
                }

            case TOKEN_KEYWORD_TEXTURE:
                m_emitter.EmitTexture(m_tokens->NextStringValue());
                break;

            case TOKEN_KEYWORD_OPACITY:
                m_emitter.EmitOpacity(m_tokens->NextIntegerValue());
                break;

            case TOKEN_KEYWORD_4E:
                m_emitter.EmitKeyword4E(m_tokens->NextIntegerValue());
                break;

            case TOKEN_KEYWORD_4F:
                m_emitter.EmitKeyword4F(m_tokens->NextIntegerValue());
                break;

            case TOKEN_KEYWORD_4D:
                m_emitter.EmitKeyword4D(m_tokens->NextIntegerValue());
                break;

            case TOKEN_KEYWORD_50:
                m_emitter.EmitKeyword50(m_tokens->NextIntegerValue());
                break;

            case TOKEN_KEYWORD_2A:
                m_emitter.EmitKeyword2A(); // DISABLE_SMOOTH_SHADING
                break;

            case TOKEN_KEYWORD_2B:
                m_emitter.EmitKeyword2B();
                break;

            case TOKEN_KEYWORD_2D:
                m_emitter.EmitKeyword2D();
                break;

            case TOKEN_KEYWORD_2E:
                m_emitter.EmitKeyword2E();
                break;

            case TOKEN_KEYWORD_44:
                m_emitter.EmitKeyword44();
                break;

            case TOKEN_KEYWORD_45:
                m_emitter.EmitKeyword45();
                break;

            case TOKEN_KEYWORD_47:
                m_emitter.EmitKeyword47();
                break;

            case TOKEN_KEYWORD_48:
                m_emitter.EmitKeyword48();
                break;

            case TOKEN_KEYWORD_49:
                m_emitter.EmitKeyword49();
                break;

            case TOKEN_KEYWORD_4A:
                m_emitter.EmitKeyword4A();
                break;

            case TOKEN_KEYWORD_4B:
                m_emitter.EmitKeyword4B();
                break;

            case TOKEN_KEYWORD_4C:
                m_emitter.EmitKeyword4C();
                break;

            case TOKEN_KEYWORD_2F:
                ProcessKeyword2F();
                break;

            case TOKEN_KEYWORD_38:
                ProcessKeyword38();
                break;

            default:
                throw MdbBinaryReadingException("Unexpected token");
            }

            return true;
        }

        std::unique_ptr<ITokenInputStream> m_tokens;
        IMdbEmitter& m_emitter;
    };
}

void MdbBinaryReader::Read(std::istream& input, IMdbEmitter& emitter)
{
    const MdbBinaryReaderImpl impl(input, emitter);
    impl.Read();
}
