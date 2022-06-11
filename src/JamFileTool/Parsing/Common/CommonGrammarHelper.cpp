#include "CommonGrammarHelper.h"

#include <cstdlib>
#include <sstream>

#pragma warning(push, 0)
#include <antlr4-runtime.h>
#pragma warning(pop)

namespace common_grammar
{
    std::string StringValue(antlr4::tree::TerminalNode* node)
    {
        if (!node)
            return std::string();

        const auto text = node->getText();
        if (text.size() <= 2)
            return std::string();

        if (text.find('\\') == std::string::npos)
            return text.substr(1, text.size() - 2);

        std::ostringstream ss;
        const auto strEnd = text.size() - 1u;
        for (auto i = 1u; i < strEnd; i++)
        {
            const auto c = text[i];
            if (c == '\\' && i + 1 < strEnd)
            {
                switch (text[i + 1])
                {
                case 'a':
                    ss << '\a';
                    break;
                case 'b':
                    ss << '\b';
                    break;
                case 'f':
                    ss << '\f';
                    break;
                case 'n':
                    ss << '\n';
                    break;
                case 'r':
                    ss << '\r';
                    break;
                case 't':
                    ss << '\t';
                    break;
                case 'v':
                    ss << '\v';
                    break;
                default:
                    ss << text[i + 1];
                    break;
                }
                i++;
            }
            else
            {
                ss << c;
            }
        }

        return ss.str();
    }

    bool UInt8Value(antlr4::tree::TerminalNode* node, uint8_t& value)
    {
        if (!node)
            return false;

        const auto text = node->getText();
        assert(!text.empty());

        size_t off = 0u;
        if (text[off] == '-')
            return false;

        if (text[off] == '+')
            off++;

        char* endPos;
        const auto readVal = strtoul(&text[off], &endPos, 0);

        if (endPos != &text[text.size()] || readVal > std::numeric_limits<uint8_t>::max())
            return false;

        value = static_cast<uint8_t>(readVal);
        return true;
    }

    bool IntValue(antlr4::tree::TerminalNode* node, int& value)
    {
        if (!node)
            return false;

        const auto text = node->getText();
        assert(!text.empty());

        char* endPos;
        const auto readVal = strtol(text.c_str(), &endPos, 0);

        if (endPos != &text[text.size()])
            return false;

        value = static_cast<int>(readVal);
        return true;
    }
}
