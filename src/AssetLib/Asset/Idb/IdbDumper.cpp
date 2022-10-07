#include "IdbDumper.h"

#include <iostream>

#include "Idb.h"
#include "TokenStream.h"
#include "Utils/AbstractTextDumper.h"

namespace idb
{
    class IdbDumpingException final : public std::exception
    {
    public:
        explicit IdbDumpingException(char const* msg)
            : exception(msg)
        {
        }
    };
}

using namespace idb;

class IdbTextOutputStream final : public AbstractTokenTextDumper
{
public:
    explicit IdbTextOutputStream(std::istream& in, std::ostream& out)
        : AbstractTokenTextDumper(out),
        m_tokens(ITokenInputStream::Create(in))
    {
    }

    void Write()
    {
        m_tokens->ExpectToken(TOKEN_IMAGE_DB);
        BeginImages();

        const auto imageCount = ReadImageCount();
        for (auto imageIndex = 0; imageIndex < imageCount; imageIndex++)
        {
            m_tokens->ExpectToken(TOKEN_IMAGE);
            const auto imageName = m_tokens->NextStringValue();
            m_tokens->ExpectToken(TOKEN_LEFT_CURLY);
            BeginImage(imageIndex, imageName);

            while (ProcessImageToken())
            {
                // Next token
            }

            EndImage();
        }

        m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);
        EndImages();
    }

private:
    [[nodiscard]] int ReadImageCount() const
    {
        m_tokens->ExpectToken(TOKEN_LEFT_BRACKET);
        const auto imageCount = m_tokens->NextIntegerValue();
        m_tokens->ExpectToken(TOKEN_RIGHT_BRACKET);
        m_tokens->ExpectToken(TOKEN_LEFT_CURLY);
        return imageCount;
    }

    [[nodiscard]] bool ProcessImageToken() const
    {
        const auto token = m_tokens->NextValue();
        if (token.m_type == TOKEN_EOF || token.m_type == TOKEN_RIGHT_CURLY)
            return false;

        switch (token.m_type)
        {
        case TOKEN_KEYWORD_FLIP_VERTICAL:
            WriteKeyword("flipVertical");
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
        case TOKEN_KEYWORD_TINT:
        {
            const auto value0 = m_tokens->NextIntegerValue();
            const auto value1 = m_tokens->NextIntegerValue();
            const auto value2 = m_tokens->NextIntegerValue();
            WriteTripletValue("tint", value0, value1, value2);
            break;
        }
        default:
            throw IdbDumpingException("Unexpected token");
        }

        return true;
    }

    void WriteTripletValue(const std::string& keyword, const int value0, const int value1, const int value2) const
    {
        Indent();
        m_stream << keyword << " " << value0 << " " << value1 << " " << value2 << "\n";
    }

    void BeginImages()
    {
        Indent();
        m_stream << "images\n";

        Indent();
        m_stream << "{\n";
        IncIndent();
    }

    void EndImages()
    {
        DecIndent();
        Indent();
        m_stream << "}\n";
    }

    void BeginImage(const int imageIndex, const std::string& imageName)
    {
        if (imageIndex > 0)
            m_stream << "\n";

        Indent();
        m_stream << "image ";
        WriteEscapedInQuotationMarks(imageName);
        m_stream << "\n";

        Indent();
        m_stream << "{\n";
        IncIndent();
    }

    void EndImage()
    {
        DecIndent();
        Indent();
        m_stream << "}\n";
    }

    std::unique_ptr<ITokenInputStream> m_tokens;
};

bool IdbDumper::SupportFileExtension(const std::string& extension) const
{
    return extension == ".IDB";
}

void IdbDumper::ProcessFile(const std::string& filePath, std::istream& input, std::ostream& output) const
{
    std::cout << "IDB dumping \"" << filePath << "\"\n";

    IdbTextOutputStream out(input, output);
    out.Write();
}
