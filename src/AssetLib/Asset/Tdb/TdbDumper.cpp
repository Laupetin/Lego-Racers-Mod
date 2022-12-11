#include "TdbDumper.h"

#include <iostream>

#include "Tdb.h"
#include "TokenStream.h"
#include "Utils/AbstractTextDumper.h"

namespace tdb
{
    class TdbDumpingException final : public std::exception
    {
    public:
        explicit TdbDumpingException(std::string msg)
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
}

using namespace tdb;

class TdbTextOutputStream final : public AbstractTokenTextDumper
{
public:
    explicit TdbTextOutputStream(std::istream& in, std::ostream& out)
        : AbstractTokenTextDumper(out),
          m_tokens(ITokenInputStream::Create(in))
    {
    }

    void Write()
    {
        m_tokens->ExpectToken(TOKEN_TEXTURE_DB);
        BeginTextures();

        const auto textureCount = ReadTextureCount();
        for (auto textureIndex = 0; textureIndex < textureCount; textureIndex++)
        {
            m_tokens->ExpectToken(TOKEN_TEXTURE);
            const auto textureName = m_tokens->NextStringValue();
            m_tokens->ExpectToken(TOKEN_LEFT_CURLY);
            BeginTexture(textureIndex, textureName);

            while (ProcessTextureToken())
            {
                // Next token
            }

            EndTexture();
        }

        m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);
        EndTextures();
    }

private:
    [[nodiscard]] int ReadTextureCount() const
    {
        m_tokens->ExpectToken(TOKEN_LEFT_BRACKET);
        const auto textureCount = m_tokens->NextIntegerValue();
        m_tokens->ExpectToken(TOKEN_RIGHT_BRACKET);
        m_tokens->ExpectToken(TOKEN_LEFT_CURLY);
        return textureCount;
    }

    [[nodiscard]] bool ProcessTextureToken() const
    {
        const auto token = m_tokens->NextValue();
        if (token.m_type == TOKEN_EOF || token.m_type == TOKEN_RIGHT_CURLY)
            return false;

        switch (token.m_type)
        {
        case TOKEN_KEYWORD_FLIP_VERTICALLY:
            WriteKeyword("flipVertically");
            break;
        case TOKEN_KEYWORD_29:
            WriteIntegerValue("keyword29", m_tokens->NextIntegerValue());
            break;
        case TOKEN_KEYWORD_BMP:
            WriteKeyword("bmp");
            break;
        case TOKEN_KEYWORD_TGA:
            WriteKeyword("tga");
            break;
        case TOKEN_KEYWORD_CHROMA_KEY:
            {
                const auto value0 = m_tokens->NextIntegerValue();
                const auto value1 = m_tokens->NextIntegerValue();
                const auto value2 = m_tokens->NextIntegerValue();
                WriteTripletValue("chromaKey", value0, value1, value2);
                break;
            }
        case TOKEN_KEYWORD_2D:
            WriteKeyword("keyword2D");
            break;
        case TOKEN_KEYWORD_2E:
            WriteKeyword("keyword2E");
            break;
        default:
            throw TdbDumpingException("Unexpected token");
        }

        return true;
    }

    void WriteTripletValue(const std::string& keyword, const int value0, const int value1, const int value2) const
    {
        Indent();
        m_stream << keyword << " " << value0 << " " << value1 << " " << value2 << "\n";
    }

    void BeginTextures()
    {
        Indent();
        m_stream << "textures\n";

        Indent();
        m_stream << "{\n";
        IncIndent();
    }

    void EndTextures()
    {
        DecIndent();
        Indent();
        m_stream << "}\n";
    }

    void BeginTexture(const int textureIndex, const std::string& textureName)
    {
        if (textureIndex > 0)
            m_stream << "\n";

        Indent();
        m_stream << "texture ";
        WriteEscapedInQuotationMarks(textureName);
        m_stream << "\n";

        Indent();
        m_stream << "{\n";
        IncIndent();
    }

    void EndTexture()
    {
        DecIndent();
        Indent();
        m_stream << "}\n";
    }

    std::unique_ptr<ITokenInputStream> m_tokens;
};

bool TdbDumper::SupportFileExtension(const std::string& extension) const
{
    return extension == ".TDB";
}

void TdbDumper::ProcessFile(const std::string& filePath, std::istream& input, std::ostream& output) const
{
    std::cout << "TDB dumping \"" << filePath << "\"\n";

    TdbTextOutputStream out(input, output);
    out.Write();
}
