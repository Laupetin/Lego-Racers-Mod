#include "IdbBinaryWriter.h"

#include <sstream>

#include "Idb.h"
#include "TokenStream.h"

namespace idb
{
    class IdbBinaryWriterImpl final : public IIdbEmitter
    {
    public:
        explicit IdbBinaryWriterImpl(std::ostream& stream)
            : m_stream(stream),
              m_tokens(ITokenOutputStream::Create(m_stream)),
              m_temp_tokens(ITokenOutputStream::Create(m_temp_buffer)),
              m_current_count(0u)
        {
        }

        void StartImages() override
        {
            PrepareElementsInTempBuffer(TOKEN_IMAGE_DB);
        }

        void EndImages() override
        {
            WriteElementsFromTempBuffer();
            m_current_count = 0u;
        }

        void StartImage(const std::string name) override
        {
            m_current_count++;
            m_temp_tokens->WriteCustom(TOKEN_IMAGE);
            m_temp_tokens->WriteString(name);
            m_temp_tokens->WriteLeftCurly();
        }

        void EmitFlipVertical() override
        {
            m_temp_tokens->WriteCustom(TOKEN_KEYWORD_FLIP_VERTICAL);
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

        void EmitTint(const uint8_t r, const uint8_t g, const uint8_t b) override
        {
            m_temp_tokens->WriteCustom(TOKEN_KEYWORD_TINT);
            m_temp_tokens->WriteUInt8(r);
            m_temp_tokens->WriteUInt8(g);
            m_temp_tokens->WriteUInt8(b);
        }

        void EndImage() override
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
}

using namespace idb;

std::unique_ptr<IIdbEmitter> IdbBinaryWriter::Create(std::ostream& stream)
{
    return std::make_unique<IdbBinaryWriterImpl>(stream);
}
