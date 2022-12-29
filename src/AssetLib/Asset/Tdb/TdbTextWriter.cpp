#include "TdbTextWriter.h"

#include <iomanip>

#include "Utils/AbstractTextDumper.h"

namespace tdb
{
    class TdbTextWriterImpl final : public ITdbEmitter, AbstractTokenTextDumper
    {
    public:
        explicit TdbTextWriterImpl(std::ostream& out)
            : AbstractTokenTextDumper(out),
              m_first_texture_element(true)
        {
            m_stream << std::fixed << std::showpoint;
        }

        void StartTextures() override
        {
            Indent();
            m_stream << "textures\n";

            Indent();
            m_stream << "{\n";
            IncIndent();
        }

        void EndTextures() override
        {
            DecIndent();
            Indent();
            m_stream << "}\n";
        }

        void StartTexture(const std::string name) override
        {
            if (m_first_texture_element)
                m_first_texture_element = false;
            else
                m_stream << "\n";

            Indent();
            m_stream << "texture ";
            WriteEscapedInQuotationMarks(name);
            m_stream << "\n";

            Indent();
            m_stream << "{\n";
            IncIndent();
        }

        void EmitFlipVertically() override
        {
            WriteKeyword("flipVertically");
        }

        void EmitKeyword29(const int value) override
        {
            WriteIntegerValue("keyword29", value);
        }

        void EmitBmp() override
        {
            WriteKeyword("bmp");
        }

        void EmitTga() override
        {
            WriteKeyword("tga");
        }

        void EmitChromaKey(const uint8_t r, const uint8_t g, const uint8_t b) override
        {
            WriteColorValue("chromaKey", r, g, b);
        }

        void EmitKeyword2D() override
        {
            WriteKeyword("keyword2D");
        }

        void EmitKeyword2E() override
        {
            WriteKeyword("keyword2E");
        }

        void EndTexture() override
        {
            DecIndent();
            Indent();
            m_stream << "}\n";
        }

    private:
        void WriteColorValue(const std::string& keyword, const int value0, const int value1, const int value2) const
        {
            Indent();
            m_stream << keyword << " " << value0 << " " << value1 << " " << value2 << "\n";
        }

        bool m_first_texture_element;
    };
}

using namespace tdb;

std::unique_ptr<ITdbEmitter> TdbTextWriter::Create(std::ostream& out)
{
    return std::make_unique<TdbTextWriterImpl>(out);
}
