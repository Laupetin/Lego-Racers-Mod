#include "AbstractTextReader.h"

#include <sstream>

AbstractTextReader::AbstractTextReader(std::istream& stream)
    : m_stream(stream),
      m_has_peeked_value(false),
      m_peeked_value(-1)
{
}

int AbstractTextReader::NextChar()
{
    if (m_has_peeked_value)
    {
        m_has_peeked_value = false;
        return m_peeked_value;
    }

    return m_stream.get();
}

void AbstractTextReader::SetPeeked(const int c)
{
    m_peeked_value = c;
    m_has_peeked_value = true;
}

bool AbstractTextReader::SkipWhitespace()
{
    int c = NextChar();

    while (isspace(c))
    {
        c = m_stream.get();
    }

    SetPeeked(c);
    return c != EOF;
}

bool AbstractTextReader::SkipWhitespaceNoNewline()
{
    int c = NextChar();

    while (c == ' ' || c == '\t' || c == '\r')
    {
        c = m_stream.get();
    }

    SetPeeked(c);

    return c != EOF;
}

bool AbstractTextReader::ReadEscapedInQuotationMarks(std::string& value)
{
    int c = NextChar();
    if (c == EOF)
        return false;

    if (c != '"')
    {
        SetPeeked(c);
        return false;
    }

    std::ostringstream ss;
    c = m_stream.get();
    while (c != EOF && c != '"')
    {
        if (c == '\n')
            return false;

        if (c == '\\')
        {
            c = m_stream.get();

            switch (c)
            {
            case '\n':
            case '\r':
                return false;
            case 'r':
                ss << "\r";
                break;
            case 'n':
                ss << "\n";
                break;
            default:
                ss << c;
                break;
            }
        }
        else
            ss << c;

        c = m_stream.get();
    }

    value = ss.str();
    return c == '"';
}

bool AbstractTextReader::ReadIntegerValue(int& value)
{
    std::ostringstream ss;

    int c = NextChar();
    while (isdigit(c))
    {
        ss << c;
        c = m_stream.get();
    }

    SetPeeked(c);

    char* endPtr;
    const auto strValue = ss.str();
    value = strtol(strValue.c_str(), &endPtr, 0);

    return endPtr == &strValue[strValue.size()];
}

bool AbstractTextReader::ReadFloatingPoint(float& value)
{
    std::string str;
    if (!ReadFloatingPointStr(str))
        return false;

    char* endPtr;
    value = strtof(str.c_str(), &endPtr);

    return endPtr == &str[str.size()];
}

bool AbstractTextReader::ReadFloatingPoint(double& value)
{
    std::string str;
    if (!ReadFloatingPointStr(str))
        return false;

    char* endPtr;
    value = strtod(str.c_str(), &endPtr);

    return endPtr == &str[str.size()];
}

bool AbstractTextReader::ReadFloatingPointStr(std::string& str)
{
    std::ostringstream ss;
    int c = NextChar();

    if (isdigit(c))
    {
        while (isdigit(c))
        {
            ss << c;
            c = m_stream.get();
        }
    }
    else if (c != '.')
        return false;

    if (c == '.')
    {
        ss << c;
        c = m_stream.get();

        if (!isdigit(c))
            return false;

        while (isdigit(c))
        {
            ss << c;
            c = m_stream.get();
        }
    }

    SetPeeked(c);
    return true;
}

bool AbstractTextReader::ReadIdentifier(std::string& value)
{
    std::ostringstream ss;

    int c = NextChar();
    if (!isalpha(c) && c != '_')
    {
        SetPeeked(c);
        return false;
    }

    ss << c;
    c = m_stream.get();
    while (isalnum(c) || c == '_')
    {
        ss << c;
        c = m_stream.get();
    }

    value = ss.str();
    SetPeeked(c);

    return true;
}
