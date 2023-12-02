#include "TdbBinaryReader.h"

#include "Tdb.h"
#include "TokenStream.h"

using namespace tdb;

namespace tdb
{
    class TdbBinaryReadingException final : public std::exception
    {
    public:
        explicit TdbBinaryReadingException(std::string msg)
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

    class TdbBinaryReaderImpl
    {
    public:
        TdbBinaryReaderImpl(std::istream& in, ITdbEmitter& emitter)
            : m_tokens(ITokenInputStream::Create(in)),
              m_emitter(emitter)
        {
        }

        void Read() const
        {
            m_tokens->ExpectToken(TOKEN_TEXTURE_DB);
            m_emitter.StartTextures();

            const auto textureCount = ReadTextureCount();
            for (auto textureIndex = 0; textureIndex < textureCount; textureIndex++)
            {
                m_tokens->ExpectToken(TOKEN_TEXTURE);
                const auto textureName = m_tokens->NextStringValue();
                m_tokens->ExpectToken(TOKEN_LEFT_CURLY);
                m_emitter.StartTexture(textureName);

                while (ProcessTextureToken())
                {
                    // Next token
                }

                m_emitter.EndTexture();
            }

            m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);
            m_emitter.EndTextures();
        }

    private:
        [[nodiscard]] int ReadTextureCount() const
        {
            m_tokens->ExpectToken(TOKEN_LEFT_BRACKET);
            const auto materialCount = m_tokens->NextIntegerValue();
            m_tokens->ExpectToken(TOKEN_RIGHT_BRACKET);
            m_tokens->ExpectToken(TOKEN_LEFT_CURLY);
            return materialCount;
        }

        [[nodiscard]] bool ProcessTextureToken() const
        {
            const auto token = m_tokens->NextValue();
            if (token.m_type == TOKEN_EOF || token.m_type == TOKEN_RIGHT_CURLY)
                return false;

            switch (token.m_type)
            {
            case TOKEN_KEYWORD_FLIP_VERTICAL:
                m_emitter.EmitFlipVertical();
                break;
            case TOKEN_KEYWORD_29:
                m_emitter.EmitKeyword29(m_tokens->NextIntegerValue());
                break;
            case TOKEN_KEYWORD_BMP:
                m_emitter.EmitBmp();
                break;
            case TOKEN_KEYWORD_TGA:
                m_emitter.EmitTga();
                break;
            case TOKEN_KEYWORD_CHROMA_KEY:
            {
                const auto value0 = static_cast<uint8_t>(m_tokens->NextIntegerValue());
                const auto value1 = static_cast<uint8_t>(m_tokens->NextIntegerValue());
                const auto value2 = static_cast<uint8_t>(m_tokens->NextIntegerValue());
                m_emitter.EmitChromaKey(value0, value1, value2);
                break;
            }
            case TOKEN_KEYWORD_2D:
                m_emitter.EmitKeyword2D();
                break;
            case TOKEN_KEYWORD_2E:
                m_emitter.EmitKeyword2E();
                break;
            default:
                throw TdbBinaryReadingException("Unexpected token");
            }

            return true;
        }

        std::unique_ptr<ITokenInputStream> m_tokens;
        ITdbEmitter& m_emitter;
    };
} // namespace tdb

void TdbBinaryReader::Read(std::istream& input, ITdbEmitter& emitter)
{
    const TdbBinaryReaderImpl impl(input, emitter);
    impl.Read();
}
