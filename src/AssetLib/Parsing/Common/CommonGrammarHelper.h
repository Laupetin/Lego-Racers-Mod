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
    bool UnsignedIntValue(antlr4::tree::TerminalNode* node, unsigned int& value);
    bool FloatingValue(antlr4::tree::TerminalNode* node, float& value);
    bool FloatingOrIntValue(antlr4::ParserRuleContext* ctx, float& value);
}
