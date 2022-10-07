#pragma once

#include <ostream>

class AbstractTextDumper
{
protected:
    std::ostream& m_stream;
    size_t m_indent;

    void Indent() const;
    void IncIndent();
    void DecIndent();

    explicit AbstractTextDumper(std::ostream& stream);
};

class AbstractTokenTextDumper : public AbstractTextDumper
{
protected:
    void WriteEscapedInQuotationMarks(const std::string& value) const;
    void WriteStringValue(const std::string& keyword, const std::string& value) const;
    void WriteIntegerValue(const std::string& keyword, int value) const;
    void WriteKeyword(const std::string& keyword) const;

    explicit AbstractTokenTextDumper(std::ostream& stream);
};