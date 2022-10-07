#include "AbstractTextDumper.h"

#include <cassert>

AbstractTextDumper::AbstractTextDumper(std::ostream& stream)
    : m_stream(stream),
      m_indent(0u)
{
}

void AbstractTextDumper::Indent() const
{
    for (auto i = 0u; i < m_indent; i++)
        m_stream << "  ";
}

void AbstractTextDumper::IncIndent()
{
    ++m_indent;
}

void AbstractTextDumper::DecIndent()
{
    assert(m_indent > 0);
    if (m_indent > 0)
        m_indent--;
}

AbstractTokenTextDumper::AbstractTokenTextDumper(std::ostream& stream)
    : AbstractTextDumper(stream)
{
}

void AbstractTokenTextDumper::WriteEscapedInQuotationMarks(const std::string& value) const
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

void AbstractTokenTextDumper::WriteStringValue(const std::string& keyword, const std::string& value) const
{
    Indent();
    m_stream << keyword << " ";
    WriteEscapedInQuotationMarks(value);
    m_stream << "\n";
}

void AbstractTokenTextDumper::WriteIntegerValue(const std::string& keyword, int value) const
{
    Indent();
    m_stream << keyword << " " << value << "\n";
}

void AbstractTokenTextDumper::WriteKeyword(const std::string& keyword) const
{
    Indent();
    m_stream << keyword << "\n";
}
