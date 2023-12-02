#include "TdbBinaryWriter.h"

#include "Tdb.h"
#include "TokenStream.h"

#include <sstream>

namespace tdb
{
    class TdbBinaryWriterImpl final : public ITdbEmitter
    {
    public:
        explicit TdbBinaryWriterImpl(std::ostream& stream)
            : m_stream(stream),
              m_tokens(ITokenOutputStream::Create(m_stream)),
              m_temp_tokens(ITokenOutputStream::Create(m_temp_buffer)),
              m_current_count(0u)
        {
        }

        void StartTextures() override
        {
            PrepareElementsInTempBuffer(TOKEN_TEXTURE_DB);
        }

        void EndTextures() override
        {
            WriteElementsFromTempBuffer();
            m_current_count = 0u;
        }

        void StartTexture(const std::string name) override
        {
            m_current_count++;
            m_temp_tokens->WriteCustom(TOKEN_TEXTURE);
            m_temp_tokens->WriteString(name);
            m_temp_tokens->WriteLeftCurly();
        }

        void EmitFlipVertical() override
        {
            m_temp_tokens->WriteCustom(TOKEN_KEYWORD_FLIP_VERTICAL);
        }

        void EmitKeyword29(const int value) override
        {
            m_temp_tokens->WriteCustom(TOKEN_KEYWORD_29);
            m_temp_tokens->WriteInteger(value);
        }

        void EmitBmp() override
        {
            m_temp_tokens->WriteCustom(TOKEN_KEYWORD_BMP);
        }

        void EmitTga() override
        {
            m_temp_tokens->WriteCustom(TOKEN_KEYWORD_TGA);
        }

        void EmitChromaKey(const uint8_t r, const uint8_t g, const uint8_t b) override
        {
            m_temp_tokens->WriteCustom(TOKEN_KEYWORD_CHROMA_KEY);
            m_temp_tokens->WriteUInt8(r);
            m_temp_tokens->WriteUInt8(g);
            m_temp_tokens->WriteUInt8(b);
        }

        void EmitKeyword2D() override
        {
            m_temp_tokens->WriteCustom(TOKEN_KEYWORD_2D);
        }

        void EmitKeyword2E() override
        {
            m_temp_tokens->WriteCustom(TOKEN_KEYWORD_2E);
        }

        void EndTexture() override
        {
            m_temp_tokens->WriteRightCurly();
        }

    private:
        void PrepareElementsInTempBuffer(const token_type_t startTokenType) const
        {
            m_tokens->WriteCustom(startTokenType);
        }

        void WriteElementsFromTempBuffer()
        {
            m_tokens->WriteLeftBracket();
            m_tokens->WriteInteger(static_cast<int>(m_current_count));
            m_tokens->WriteRightBracket();
            m_tokens->WriteLeftCurly();

            m_stream << m_temp_buffer.str();

            m_tokens->WriteRightCurly();

            m_temp_buffer.str(std::string());
        }

        std::ostream& m_stream;
        std::unique_ptr<ITokenOutputStream> m_tokens;
        std::ostringstream m_temp_buffer;
        std::unique_ptr<ITokenOutputStream> m_temp_tokens;
        size_t m_current_count;
    };
} // namespace tdb

using namespace tdb;

std::unique_ptr<ITdbEmitter> TdbBinaryWriter::Create(std::ostream& stream)
{
    return std::make_unique<TdbBinaryWriterImpl>(stream);
}
