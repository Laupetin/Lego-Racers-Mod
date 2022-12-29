#include "IdbTextWriter.h"

#include <iomanip>

#include "Utils/AbstractTextDumper.h"

namespace idb
{
    class IdbTextWriterImpl final : public IIdbEmitter, AbstractTokenTextDumper
    {
    public:
        explicit IdbTextWriterImpl(std::ostream& out)
            : AbstractTokenTextDumper(out),
              m_first_image_element(true)
        {
            m_stream << std::fixed << std::showpoint;
        }

        void StartImages() override
        {
            Indent();
            m_stream << "images\n";

            Indent();
            m_stream << "{\n";
            IncIndent();
        }

        void EndImages() override
        {
            DecIndent();
            Indent();
            m_stream << "}\n";
        }

        void StartImage(const std::string name) override
        {
            if (m_first_image_element)
                m_first_image_element = false;
            else
                m_stream << "\n";

            Indent();
            m_stream << "image ";
            WriteEscapedInQuotationMarks(name);
            m_stream << "\n";

            Indent();
            m_stream << "{\n";
            IncIndent();
        }

        void EmitFlipVertical() override
        {
            WriteKeyword("flipVertical");
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

        void EmitTint(const uint8_t r, const uint8_t g, const uint8_t b) override
        {
            WriteColorValue("tint", r, g, b);
        }

        void EndImage() override
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

        bool m_first_image_element;
    };
}

using namespace idb;

std::unique_ptr<IIdbEmitter> IdbTextWriter::Create(std::ostream& out)
{
    return std::make_unique<IdbTextWriterImpl>(out);
}
