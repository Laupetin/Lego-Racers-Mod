#include "MdbTextWriter.h"

#include <iomanip>

#include "Utils/AbstractTextDumper.h"

namespace mdb
{
    class MdbTextWriterImpl final : public IMdbEmitter, AbstractTokenTextDumper
    {
    public:
        explicit MdbTextWriterImpl(std::ostream& out)
            : AbstractTokenTextDumper(out),
              m_first_material_element(true)
        {
            m_stream << std::fixed << std::showpoint;
        }

        void StartMaterials() override
        {
            Indent();
            m_stream << "materials\n";

            Indent();
            m_stream << "{\n";
            IncIndent();
        }

        void EndMaterials() override
        {
            DecIndent();
            Indent();
            m_stream << "}\n";
        }

        void StartMaterial(const std::string name) override
        {
            if (m_first_material_element)
                m_first_material_element = false;
            else
                m_stream << "\n";

            Indent();
            m_stream << "material ";
            WriteEscapedInQuotationMarks(name);
            m_stream << "\n";

            Indent();
            m_stream << "{\n";
            IncIndent();
        }

        void EmitColor0(const uint8_t value0, const uint8_t value1, const uint8_t value2, const uint8_t value3) override
        {
            WriteColorValue("color0", value0, value1, value2, value3);
        }

        void EmitColor1(const uint8_t value0, const uint8_t value1, const uint8_t value2, const uint8_t value3) override
        {
            WriteColorValue("color1", value0, value1, value2, value3);
        }

        void EmitTexture(const std::string textureName) override
        {
            WriteStringValue("texture", textureName);
        }

        void EmitOpacity(const uint8_t value) override
        {
            WriteIntegerValue("opacity", value);
        }

        void EmitKeyword4E(const int value) override
        {
            WriteIntegerValue("keyword4E", value);
        }

        void EmitKeyword4F(const int value) override
        {
            WriteIntegerValue("keyword4F", value);
        }

        void EmitKeyword4D(const int value) override
        {
            WriteIntegerValue("keyword4D", value);
        }

        void EmitKeyword50(const int value) override
        {
            WriteIntegerValue("keyword50", value);
        }

        void EmitKeyword2A() override
        {
            WriteKeyword("keyword2A");
        }

        void EmitKeyword2B() override
        {
            WriteKeyword("keyword2B");
        }

        void EmitKeyword2D() override
        {
            WriteKeyword("keyword2D");
        }

        void EmitKeyword2E() override
        {
            WriteKeyword("keyword2E");
        }

        void EmitKeyword44() override
        {
            WriteKeyword("keyword44");
        }

        void EmitKeyword45() override
        {
            WriteKeyword("keyword45");
        }

        void EmitKeyword47() override
        {
            WriteKeyword("keyword47");
        }

        void EmitKeyword48() override
        {
            WriteKeyword("keyword48");
        }

        void EmitKeyword49() override
        {
            WriteKeyword("keyword49");
        }

        void EmitKeyword4A() override
        {
            WriteKeyword("keyword4A");
        }

        void EmitKeyword4B() override
        {
            WriteKeyword("keyword4B");
        }

        void EmitKeyword4C() override
        {
            WriteKeyword("keyword4C");
        }

        void EmitKeyword2F(const MaterialToken subToken, const int subTokenValue) override
        {
            Indent();
            m_stream << "keyword2F";

            switch (subToken)
            {
            case TOKEN_KEYWORD_2F_SUB_30:
                m_stream << " keyword30";
                break;

            case TOKEN_KEYWORD_2F_SUB_31:
                m_stream << " keyword31 " << subTokenValue;
                break;

            case TOKEN_KEYWORD_2F_SUB_32:
                m_stream << " keyword32 " << subTokenValue;
                break;

            case TOKEN_KEYWORD_2F_SUB_33:
                m_stream << " keyword33 " << subTokenValue;
                break;

            case TOKEN_KEYWORD_2F_SUB_34:
                m_stream << " keyword34 " << subTokenValue;
                break;

            case TOKEN_KEYWORD_2F_SUB_35:
                m_stream << " keyword35 " << subTokenValue;
                break;

            case TOKEN_KEYWORD_2F_SUB_36:
                m_stream << " keyword36";
                break;

            case TOKEN_KEYWORD_2F_SUB_37:
                m_stream << " keyword37 " << subTokenValue;
                break;

            default:
                break;
            }

            m_stream << "\n";
        }

        void EmitKeyword38(const MaterialToken subToken0, const MaterialToken subToken1) override
        {
            Indent();
            m_stream << "keyword38";

            for (auto i = 0u; i < 2u; i++)
            {
                const auto token = i == 0 ? subToken0 : subToken1;

                switch (token)
                {
                case TOKEN_KEYWORD_38_SUB_39:
                    m_stream << " keyword39";
                    break;

                case TOKEN_KEYWORD_38_SUB_3A:
                    m_stream << " keyword3A";
                    break;

                case TOKEN_KEYWORD_38_SUB_3B:
                    m_stream << " keyword3B";
                    break;

                case TOKEN_KEYWORD_38_SUB_3C:
                    m_stream << " keyword3C";
                    break;

                case TOKEN_KEYWORD_38_SUB_3D:
                    m_stream << " keyword3D";
                    break;

                case TOKEN_KEYWORD_38_SUB_3E:
                    m_stream << " keyword3E";
                    break;

                case TOKEN_KEYWORD_38_SUB_3F:
                    m_stream << " keyword3F";
                    break;

                case TOKEN_KEYWORD_38_SUB_40:
                    m_stream << " keyword40";
                    break;

                case TOKEN_KEYWORD_38_SUB_41:
                    m_stream << " keyword41";
                    break;

                case TOKEN_KEYWORD_38_SUB_42:
                    m_stream << " keyword42";
                    break;

                case TOKEN_KEYWORD_38_SUB_43:
                    m_stream << " keyword43";
                    break;

                default:
                    break;
                }
            }

            m_stream << "\n";
        }

        void EndMaterial() override
        {
            DecIndent();
            Indent();
            m_stream << "}\n";
        }

    private:
        void WriteColorValue(const std::string& keyword, const int value0, const int value1, const int value2, const int value3) const
        {
            Indent();
            m_stream << keyword << " " << value0 << " " << value1 << " " << value2 << " " << value3 << "\n";
        }

        bool m_first_material_element;
    };
}

using namespace mdb;

std::unique_ptr<IMdbEmitter> MdbTextWriter::Create(std::ostream& out)
{
    return std::make_unique<MdbTextWriterImpl>(out);
}
