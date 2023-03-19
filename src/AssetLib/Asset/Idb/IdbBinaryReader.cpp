#include "IdbBinaryReader.h"

#include "Idb.h"
#include "TokenStream.h"

using namespace idb;

namespace idb
{
    class IdbBinaryReadingException final : public std::exception
    {
    public:
        explicit IdbBinaryReadingException(std::string msg)
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

    class IdbBinaryReaderImpl
    {
    public:
        IdbBinaryReaderImpl(std::istream& in, IIdbEmitter& emitter)
            : m_tokens(ITokenInputStream::Create(in)),
              m_emitter(emitter)
        {
        }

        void Read() const
        {
            m_tokens->ExpectToken(TOKEN_IMAGE_DB);
            m_emitter.StartImages();

            const auto imageCount = ReadImageCount();
            for (auto imageIndex = 0; imageIndex < imageCount; imageIndex++)
            {
                m_tokens->ExpectToken(TOKEN_IMAGE);
                const auto imageName = m_tokens->NextStringValue();
                m_tokens->ExpectToken(TOKEN_LEFT_CURLY);
                m_emitter.StartImage(imageName);

                while (ProcessImageToken())
                {
                    // Next token
                }

                m_emitter.EndImage();
            }

            m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);
            m_emitter.EndImages();
        }

    private:
        [[nodiscard]] int ReadImageCount() const
        {
            m_tokens->ExpectToken(TOKEN_LEFT_BRACKET);
            const auto materialCount = m_tokens->NextIntegerValue();
            m_tokens->ExpectToken(TOKEN_RIGHT_BRACKET);
            m_tokens->ExpectToken(TOKEN_LEFT_CURLY);
            return materialCount;
        }

        [[nodiscard]] bool ProcessImageToken() const
        {
            const auto token = m_tokens->NextValue();
            if (token.m_type == TOKEN_EOF || token.m_type == TOKEN_RIGHT_CURLY)
                return false;

            switch (token.m_type)
            {
            case TOKEN_KEYWORD_FLIP_VERTICAL:
                m_emitter.EmitFlipVertical();
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
            case TOKEN_KEYWORD_TINT:
                {
                    const auto value0 = static_cast<uint8_t>(m_tokens->NextIntegerValue());
                    const auto value1 = static_cast<uint8_t>(m_tokens->NextIntegerValue());
                    const auto value2 = static_cast<uint8_t>(m_tokens->NextIntegerValue());
                    m_emitter.EmitTint(value0, value1, value2);
                    break;
                }
            default:
                throw IdbBinaryReadingException("Unexpected token");
            }

            return true;
        }

        std::unique_ptr<ITokenInputStream> m_tokens;
        IIdbEmitter& m_emitter;
    };
}

void IdbBinaryReader::Read(std::istream& input, IIdbEmitter& emitter)
{
    const IdbBinaryReaderImpl impl(input, emitter);
    impl.Read();
}
