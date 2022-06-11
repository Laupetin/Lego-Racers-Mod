#include "MdbCreator.h"

#include <iostream>
#include <sstream>

#include "Mdb.h"
#include "Utils/Endianness.h"
#include "Utils/StringUtils.h"
#include "TokenStream.h"

#pragma warning(push, 0)
#include "Parsing/Common/CommonGrammarHelper.h"
#include "Parsing/Parser/Mdb/MdbLexer.h"
#include "Parsing/Parser/Mdb/MdbParser.h"
#include "Parsing/Parser/Mdb/MdbBaseListener.h"
#pragma warning(pop)

namespace mdb
{
    class MdbCreationException final : public std::exception
    {
    public:
        explicit MdbCreationException(char const* msg)
            : exception(msg)
        {
        }
    };

    class MdbParserState
    {
    public:
        explicit MdbParserState(ITokenOutputStream* out)
            : m_material_count(0u),
            m_out(out)
        {
        }

        void BeginMaterial(const std::string& materialName)
        {
            m_material_count++;
            m_out->WriteCustom(TOKEN_MATERIAL);
            m_out->WriteString(materialName);
            m_out->WriteLeftCurly();
        }

        void EndMaterial() const
        {
            m_out->WriteRightCurly();
        }

        size_t m_material_count;
        ITokenOutputStream* m_out;
    };

    class CustomMdbListener final : public MdbBaseListener
    {
    public:
        explicit CustomMdbListener(MdbParser& parser, MdbParserState& state)
            : m_parser(parser),
            m_state(state)
        {
        }

        void exitMaterialName(MdbParser::MaterialNameContext* context) override
        {
            const auto materialName = common_grammar::StringValue(context->StringLiteral());
            m_state.BeginMaterial(materialName);
        }

        void exitMaterial(MdbParser::MaterialContext* context) override
        {
            m_state.EndMaterial();
        }

        void exitColorMaterialProperty(MdbParser::ColorMaterialPropertyContext* context) override
        {
            const auto keywordType = context->colorMaterialPropertyKeyword()->getStart()->getType();

            if (keywordType == MdbLexer::Color0)
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_COLOR_0);
            else if (keywordType == MdbLexer::Color1)
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_COLOR_1);
            else
                assert(false);

            for (auto i = 0u; i < 4; i++)
            {
                auto* node = context->IntegerConstant(i);
                uint8_t value;
                if (!common_grammar::UInt8Value(node, value))
                    return m_parser.notifyErrorListeners(node->getSymbol(), "Invalid uint8 value", nullptr);

                m_state.m_out->WriteUInt8(value);
            }
        }

        void exitTextMaterialProperty(MdbParser::TextMaterialPropertyContext* context) override
        {
            assert(context->textMaterialPropertyKeyword()->getStart()->getType() == MdbLexer::Texture);
            m_state.m_out->WriteCustom(TOKEN_KEYWORD_TEXTURE);

            const auto stringValue = common_grammar::StringValue(context->StringLiteral());
            m_state.m_out->WriteString(stringValue);
        }

        void exitUint8MaterialProperty(MdbParser::Uint8MaterialPropertyContext* context) override
        {
            assert(context->uint8MaterialPropertyKeyword()->getStart()->getType() == MdbLexer::Opacity);
            m_state.m_out->WriteCustom(TOKEN_KEYWORD_OPACITY);

            auto* node = context->IntegerConstant();
            uint8_t value;
            if (!common_grammar::UInt8Value(node, value))
                return m_parser.notifyErrorListeners(node->getSymbol(), "Invalid uint8 value", nullptr);

            m_state.m_out->WriteUInt8(value);
        }

        void exitIntMaterialProperty(MdbParser::IntMaterialPropertyContext* context) override
        {
            const auto keywordType = context->intMaterialPropertyKeyword()->getStart()->getType();
            switch (keywordType)
            {
            case MdbLexer::Keyword4D:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_4D);
                break;
            case MdbLexer::Keyword4E:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_4E);
                break;
            case MdbLexer::Keyword4F:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_4F);
                break;
            case MdbLexer::Keyword50:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_50);
                break;
            default:
                assert(false);
                break;
            }

            auto* node = context->IntegerConstant();
            int value;
            if (!common_grammar::IntValue(node, value))
                return m_parser.notifyErrorListeners(node->getSymbol(), "Invalid int value", nullptr);

            m_state.m_out->WriteInteger(value);
        }

        void exitSingleValueKeywords(MdbParser::SingleValueKeywordsContext* context) override
        {
            const auto keywordType = context->getStart()->getType();
            switch (keywordType)
            {
            case MdbLexer::Keyword2A:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_2A);
                break;
            case MdbLexer::Keyword2B:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_2B);
                break;
            case MdbLexer::Keyword2D:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_2D);
                break;
            case MdbLexer::Keyword2E:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_2E);
                break;
            case MdbLexer::Keyword44:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_44);
                break;
            case MdbLexer::Keyword45:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_45);
                break;
            case MdbLexer::Keyword47:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_47);
                break;
            case MdbLexer::Keyword48:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_48);
                break;
            case MdbLexer::Keyword49:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_49);
                break;
            case MdbLexer::Keyword4A:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_4A);
                break;
            case MdbLexer::Keyword4B:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_4B);
                break;
            case MdbLexer::Keyword4C:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_4C);
                break;
            default:
                assert(false);
                break;
            }
        }

        void enterKeyword2F(MdbParser::Keyword2FContext*) override
        {
            m_state.m_out->WriteCustom(TOKEN_KEYWORD_2F);
        }

        void exitKeyword2FSubtoken(MdbParser::Keyword2FSubtokenContext* context) override
        {
            auto hasIntegerValue = false;
            switch (context->getStart()->getType())
            {
            case MdbLexer::Keyword30:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_2F_SUB_30);
                break;
            case MdbLexer::Keyword31:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_2F_SUB_31);
                hasIntegerValue = true;
                break;
            case MdbLexer::Keyword32:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_2F_SUB_32);
                hasIntegerValue = true;
                break;
            case MdbLexer::Keyword33:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_2F_SUB_33);
                hasIntegerValue = true;
                break;
            case MdbLexer::Keyword34:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_2F_SUB_34);
                hasIntegerValue = true;
                break;
            case MdbLexer::Keyword35:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_2F_SUB_35);
                hasIntegerValue = true;
                break;
            case MdbLexer::Keyword36:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_2F_SUB_36);
                break;
            case MdbLexer::Keyword37:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_2F_SUB_37);
                hasIntegerValue = true;
                break;
            default:
                assert(false);
                break;
            }

            if (hasIntegerValue)
            {
                auto* node = context->IntegerConstant();
                int value;
                if (!common_grammar::IntValue(node, value))
                    return m_parser.notifyErrorListeners(node->getSymbol(), "Invalid int value", nullptr);
                m_state.m_out->WriteInteger(value);
            }
        }

        void enterKeyword38(MdbParser::Keyword38Context*) override
        {
            m_state.m_out->WriteCustom(TOKEN_KEYWORD_38);
        }

        void exitKeyword38Subtoken(MdbParser::Keyword38SubtokenContext* context) override
        {
            switch (context->getStart()->getType())
            {
            case MdbLexer::Keyword39:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_38_SUB_39);
                break;
            case MdbLexer::Keyword3A:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_38_SUB_3A);
                break;
            case MdbLexer::Keyword3B:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_38_SUB_3B);
                break;
            case MdbLexer::Keyword3C:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_38_SUB_3C);
                break;
            case MdbLexer::Keyword3D:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_38_SUB_3D);
                break;
            case MdbLexer::Keyword3E:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_38_SUB_3E);
                break;
            case MdbLexer::Keyword3F:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_38_SUB_3F);
                break;
            case MdbLexer::Keyword40:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_38_SUB_40);
                break;
            case MdbLexer::Keyword41:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_38_SUB_41);
                break;
            case MdbLexer::Keyword42:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_38_SUB_42);
                break;
            case MdbLexer::Keyword43:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_38_SUB_43);
                break;
            default:
                assert(false);
                break;
            }
        }

    private:
        MdbParser& m_parser;
        MdbParserState& m_state;
    };

    class CustomMdbErrorListener final : public antlr4::BaseErrorListener
    {
        void syntaxError(antlr4::Recognizer* recognizer, antlr4::Token* offendingSymbol, size_t line, size_t charPositionInLine, const std::string& msg, std::exception_ptr e) override
        {
            throw MdbCreationException("Parsing MDB failed");
        }
    };
}

using namespace mdb;


bool MdbCreator::SupportFileExtension(const std::string& extension) const
{
    return extension == ".MDB";
}

void MdbCreator::ProcessFile(const std::string& filePath, const void* inputData, const size_t inputDataSize, std::ostream& output) const
{
    std::cout << "Mdb creating \"" << filePath << "\"\n";

    CustomMdbErrorListener errors;
    antlr4::ANTLRInputStream inputStream(static_cast<const char*>(inputData), inputDataSize);

    MdbLexer lexer(&inputStream);
    lexer.addErrorListener(&errors);

    antlr4::CommonTokenStream tokenStream(&lexer);
    MdbParser parser(&tokenStream);
    parser.addErrorListener(&errors);
    parser.setErrorHandler(std::make_shared<antlr4::BailErrorStrategy>());

    auto* parseTree = parser.root();

    std::ostringstream materialData;
    const auto materialDataTokens = ITokenOutputStream::Create(materialData);
    MdbParserState parserState(materialDataTokens.get());
    CustomMdbListener listener(parser, parserState);
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, parseTree);

    const auto tokenOut = ITokenOutputStream::Create(output);
    tokenOut->WriteCustom(TOKEN_MATERIAL_DB);
    tokenOut->WriteLeftBracket();
    tokenOut->WriteInteger(static_cast<int>(parserState.m_material_count));
    tokenOut->WriteRightBracket();
    tokenOut->WriteLeftCurly();

    output << materialData.str();

    tokenOut->WriteRightCurly();

    std::cout << "Successfully created Mdb \"" << filePath << "\" with " << parserState.m_material_count << " materials\n";
}
