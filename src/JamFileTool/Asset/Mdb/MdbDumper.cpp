#include "MdbDumper.h"

#include <iostream>

#include "Mdb.h"
#include "TokenStream.h"
#include "Utils/AbstractTextDumper.h"

namespace mdb
{
    class MdbDumpingException final : public std::exception
    {
    public:
        explicit MdbDumpingException(char const* msg)
            : exception(msg)
        {
        }
    };
}

using namespace mdb;

class MdbTextOutputStream final : public AbstractTextDumper
{
public:
    explicit MdbTextOutputStream(std::istream& in, std::ostream& out)
        : AbstractTextDumper(out),
          m_tokens(ITokenInputStream::Create(in))
    {
    }

    void Write()
    {
        m_tokens->ExpectToken(TOKEN_MATERIAL_DB);
        BeginMaterials();

        const auto materialCount = ReadMaterialCount();
        for (auto materialIndex = 0; materialIndex < materialCount; materialIndex++)
        {
            m_tokens->ExpectToken(TOKEN_MATERIAL);
            const auto materialName = m_tokens->NextStringValue();
            m_tokens->ExpectToken(TOKEN_LEFT_CURLY);
            BeginMaterial(materialIndex, materialName);

            while (ProcessMaterialToken())
            {
                // Next token
            }

            EndMaterial();
        }

        m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);
        EndMaterials();
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

    void WriteEscapedInQuotationMarks(const std::string& value) const
    {
        m_stream << "\"";
        for (const auto& c : value)
        {
            switch (c)
            {
            case '\r':
                m_stream << "\\r";
                break;
            case '\n':
                m_stream << "\\n";
                break;
            case '\\':
            case '\"':
                m_stream << "\\" << c;
                break;
            default:
                m_stream << c;
            }
        }
        m_stream << "\"";
    }

    void ProcessKeyword2F() const
    {
        Indent();
        m_stream << "keyword2F";

        const auto token = m_tokens->NextValue();

        switch (token.m_type)
        {
        case TOKEN_KEYWORD_2F_SUB_30:
            m_stream << " keyword30";
            break;

        case TOKEN_KEYWORD_2F_SUB_31:
            m_stream << " keyword31 " << m_tokens->NextIntegerValue();
            break;

        case TOKEN_KEYWORD_2F_SUB_32:
            m_stream << " keyword32 " << m_tokens->NextIntegerValue();
            break;

        case TOKEN_KEYWORD_2F_SUB_33:
            m_stream << " keyword33 " << m_tokens->NextIntegerValue();
            break;

        case TOKEN_KEYWORD_2F_SUB_34:
            m_stream << " keyword34 " << m_tokens->NextIntegerValue();
            break;

        case TOKEN_KEYWORD_2F_SUB_35:
            m_stream << " keyword35 " << m_tokens->NextIntegerValue();
            break;

        case TOKEN_KEYWORD_2F_SUB_36:
            m_stream << " keyword36";
            break;

        case TOKEN_KEYWORD_2F_SUB_37:
            m_stream << " keyword37 " << m_tokens->NextIntegerValue();
            break;

        default:
            break;
        }

        m_stream << "\n";
    }

    void ProcessKeyword38() const
    {
        Indent();
        m_stream << "keyword38";

        for (auto i = 0u; i < 2u; i++)
        {
            const auto token = m_tokens->NextValue();

            switch (token.m_type)
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
                throw MdbDumpingException("Unknown keyword for keyword38");
            }
        }

        m_stream << "\n";
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
                WriteColorValue("color1", value0, value1, value2, value3);
                break;
            }

        case TOKEN_KEYWORD_COLOR_0:
            {
                const auto value0 = m_tokens->NextIntegerValue();
                const auto value1 = m_tokens->NextIntegerValue();
                const auto value2 = m_tokens->NextIntegerValue();
                const auto value3 = m_tokens->NextIntegerValue();
                WriteColorValue("color0", value0, value1, value2, value3);
                break;
            }

        case TOKEN_KEYWORD_TEXTURE:
            WriteStringValue("texture", m_tokens->NextStringValue());
            break;

        case TOKEN_KEYWORD_46:
            WriteIntegerValue("keyword46", m_tokens->NextIntegerValue());
            break;

        case TOKEN_KEYWORD_4E:
            WriteIntegerValue("keyword4E", m_tokens->NextIntegerValue());
            break;

        case TOKEN_KEYWORD_4F:
            WriteIntegerValue("keyword4F", m_tokens->NextIntegerValue());
            break;

        case TOKEN_KEYWORD_4D:
        case TOKEN_KEYWORD_50:
            WriteIntegerValue("keyword4D", m_tokens->NextIntegerValue());
            break;

        case TOKEN_KEYWORD_2A:
            WriteKeyword("keyword2A");
            break;

        case TOKEN_KEYWORD_2B:
            WriteKeyword("keyword2B");
            break;

        case TOKEN_KEYWORD_2D:
            WriteKeyword("keyword2D");
            break;

        case TOKEN_KEYWORD_2E:
            WriteKeyword("keyword2E");
            break;

        case TOKEN_KEYWORD_44:
            WriteKeyword("keyword44");
            break;

        case TOKEN_KEYWORD_45:
            WriteKeyword("keyword45");
            break;

        case TOKEN_KEYWORD_47:
            WriteKeyword("keyword47");
            break;

        case TOKEN_KEYWORD_48:
            WriteKeyword("keyword48");
            break;

        case TOKEN_KEYWORD_49:
            WriteKeyword("keyword49");
            break;

        case TOKEN_KEYWORD_4A:
            WriteKeyword("keyword4A");
            break;

        case TOKEN_KEYWORD_4B:
            WriteKeyword("keyword4B");
            break;

        case TOKEN_KEYWORD_4C:
            WriteKeyword("keyword4C");
            break;

        case TOKEN_KEYWORD_2F:
            ProcessKeyword2F();
            break;

        case TOKEN_KEYWORD_38:
            ProcessKeyword38();
            break;

        default:
            throw MdbDumpingException("Unexpected token");
        }

        return true;
    }

    void WriteColorValue(const std::string& keyword, const int value0, const int value1, const int value2, const int value3) const
    {
        Indent();
        m_stream << keyword << " " << value0 << " " << value1 << " " << value2 << " " << value3 << "\n";
    }

    void WriteStringValue(const std::string& keyword, const std::string& value) const
    {
        Indent();
        m_stream << keyword << " ";
        WriteEscapedInQuotationMarks(value);
        m_stream << "\n";
    }

    void WriteIntegerValue(const std::string& keyword, const int value) const
    {
        Indent();
        m_stream << keyword << " " << value << "\n";
    }

    void WriteKeyword(const std::string& keyword) const
    {
        Indent();
        m_stream << keyword << "\n";
    }

    void BeginMaterials()
    {
        Indent();
        m_stream << "materials\n";

        Indent();
        m_stream << "{\n";
        IncIndent();
    }

    void EndMaterials()
    {
        DecIndent();
        Indent();
        m_stream << "}\n";
    }

    void BeginMaterial(const int materialIndex, const std::string& materialName)
    {
        if (materialIndex > 0)
            m_stream << "\n";

        Indent();
        m_stream << "material ";
        WriteEscapedInQuotationMarks(materialName);
        m_stream << "\n";

        Indent();
        m_stream << "{\n";
        IncIndent();
    }

    void EndMaterial()
    {
        DecIndent();
        Indent();
        m_stream << "}\n";
    }

    std::unique_ptr<ITokenInputStream> m_tokens;
};

bool MdbDumper::SupportFileExtension(const std::string& extension) const
{
    return extension == ".MDB";
}

void MdbDumper::ProcessFile(const std::string& filePath, std::istream& input, std::ostream& output) const
{
    std::cout << "MDB dumping \"" << filePath << "\"\n";

    MdbTextOutputStream out(input, output);
    out.Write();
}
