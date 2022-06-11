#pragma once
#include <string>

#pragma warning(push, 0)
#include <antlr4-common.h>
#pragma warning(pop)

namespace common_grammar
{
    std::string StringValue(antlr4::tree::TerminalNode* node);
    bool UInt8Value(antlr4::tree::TerminalNode* node, uint8_t& value);
    bool IntValue(antlr4::tree::TerminalNode* node, int& value);
}
