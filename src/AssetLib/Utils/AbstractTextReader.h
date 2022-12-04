#pragma once

#include <istream>

class AbstractTextReader
{
protected:
    explicit AbstractTextReader(std::istream& stream);

    int NextChar();
    void SetPeeked(int c);
    bool SkipWhitespace();
    bool SkipWhitespaceNoNewline();
    bool ReadEscapedInQuotationMarks(std::string& value);
    bool ReadIntegerValue(int& value);
    bool ReadFloatingPoint(float& value);
    bool ReadFloatingPoint(double& value);
    bool ReadIdentifier(std::string& value);

private:
    bool ReadFloatingPointStr(std::string& str);

protected:
    std::istream& m_stream;
    bool m_has_peeked_value;
    int m_peeked_value;
};