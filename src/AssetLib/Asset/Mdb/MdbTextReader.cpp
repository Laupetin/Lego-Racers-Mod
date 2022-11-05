#include "MdbTextReader.h"

#include <iostream>

#include "Mdb.h"

#pragma warning(push, 0)
#include "Parsing/Common/CommonGrammarHelper.h"
#include "Parsing/Parser/Gdb/GdbLexer.h"
#include "Parsing/Parser/Mdb/MdbLexer.h"
#include "Parsing/Parser/Mdb/MdbParser.h"
#include "Parsing/Parser/Mdb/MdbBaseListener.h"
#pragma warning(pop)

namespace mdb
{
    class MdbCreationException final : public std::exception
    {
    public:
        explicit MdbCreationException(std::string str)
            : exception(str.c_str()),
              m_message(std::move(str))
        {
        }

    private:
        std::string m_message;
    };

    class CustomMdbListener final : public MdbBaseListener
    {
    public:
        explicit CustomMdbListener(MdbParser& parser, IMdbEmitter& emitter)
            : m_parser(parser),
              m_emitter(emitter)
        {
        }

        void exitMaterialName(MdbParser::MaterialNameContext* context) override
        {
            auto materialName = common_grammar::StringValue(context->StringLiteral());
            m_emitter.StartMaterial(std::move(materialName));
        }

        void exitMaterial(MdbParser::MaterialContext* context) override
        {
            m_emitter.EndMaterial();
        }

        void exitColorMaterialProperty(MdbParser::ColorMaterialPropertyContext* context) override
        {
            const auto keywordType = context->colorMaterialPropertyKeyword()->getStart()->getType();

            const uint8_t values[4]
            {
                GetUInt8(context->IntegerConstant(0)),
                GetUInt8(context->IntegerConstant(1)),
                GetUInt8(context->IntegerConstant(2)),
                GetUInt8(context->IntegerConstant(3))
            };

            if (keywordType == MdbLexer::Color0)
                m_emitter.EmitColor0(values[0], values[1], values[2], values[3]);
            else if (keywordType == MdbLexer::Color1)
                m_emitter.EmitColor1(values[0], values[1], values[2], values[3]);
            else
                assert(false);
        }

        void exitTextMaterialProperty(MdbParser::TextMaterialPropertyContext* context) override
        {
            assert(context->textMaterialPropertyKeyword()->getStart()->getType() == MdbLexer::Texture);
            const auto stringValue = common_grammar::StringValue(context->StringLiteral());

            m_emitter.EmitTexture(stringValue);
        }

        void exitUint8MaterialProperty(MdbParser::Uint8MaterialPropertyContext* context) override
        {
            assert(context->uint8MaterialPropertyKeyword()->getStart()->getType() == MdbLexer::Opacity);

            m_emitter.EmitOpacity(GetUInt8(context->IntegerConstant()));
        }

        void exitIntMaterialProperty(MdbParser::IntMaterialPropertyContext* context) override
        {
            const auto keywordType = context->intMaterialPropertyKeyword()->getStart()->getType();
            switch (keywordType)
            {
            case MdbLexer::Keyword4D:
                m_emitter.EmitKeyword4D(GetInt(context->IntegerConstant()));
                break;
            case MdbLexer::Keyword4E:
                m_emitter.EmitKeyword4E(GetInt(context->IntegerConstant()));
                break;
            case MdbLexer::Keyword4F:
                m_emitter.EmitKeyword4F(GetInt(context->IntegerConstant()));
                break;
            case MdbLexer::Keyword50:
                m_emitter.EmitKeyword50(GetInt(context->IntegerConstant()));
                break;
            default:
                assert(false);
                break;
            }
        }

        void exitSingleValueKeywords(MdbParser::SingleValueKeywordsContext* context) override
        {
            const auto keywordType = context->getStart()->getType();
            switch (keywordType)
            {
            case MdbLexer::Keyword2A:
                m_emitter.EmitKeyword2A();
                break;
            case MdbLexer::Keyword2B:
                m_emitter.EmitKeyword2B();
                break;
            case MdbLexer::Keyword2D:
                m_emitter.EmitKeyword2D();
                break;
            case MdbLexer::Keyword2E:
                m_emitter.EmitKeyword2E();
                break;
            case MdbLexer::Keyword44:
                m_emitter.EmitKeyword44();
                break;
            case MdbLexer::Keyword45:
                m_emitter.EmitKeyword45();
                break;
            case MdbLexer::Keyword47:
                m_emitter.EmitKeyword47();
                break;
            case MdbLexer::Keyword48:
                m_emitter.EmitKeyword48();
                break;
            case MdbLexer::Keyword49:
                m_emitter.EmitKeyword49();
                break;
            case MdbLexer::Keyword4A:
                m_emitter.EmitKeyword4A();
                break;
            case MdbLexer::Keyword4B:
                m_emitter.EmitKeyword4B();
                break;
            case MdbLexer::Keyword4C:
                m_emitter.EmitKeyword4C();
                break;
            default:
                assert(false);
                break;
            }
        }

        void exitKeyword2FSubtoken(MdbParser::Keyword2FSubtokenContext* context) override
        {
            switch (context->getStart()->getType())
            {
            case MdbLexer::Keyword30:
                m_emitter.EmitKeyword2F(TOKEN_KEYWORD_2F_SUB_30, 0);
                break;
            case MdbLexer::Keyword31:
                m_emitter.EmitKeyword2F(TOKEN_KEYWORD_2F_SUB_31, GetInt(context->IntegerConstant()));
                break;
            case MdbLexer::Keyword32:
                m_emitter.EmitKeyword2F(TOKEN_KEYWORD_2F_SUB_32, GetInt(context->IntegerConstant()));
                break;
            case MdbLexer::Keyword33:
                m_emitter.EmitKeyword2F(TOKEN_KEYWORD_2F_SUB_33, GetInt(context->IntegerConstant()));
                break;
            case MdbLexer::Keyword34:
                m_emitter.EmitKeyword2F(TOKEN_KEYWORD_2F_SUB_34, GetInt(context->IntegerConstant()));
                break;
            case MdbLexer::Keyword35:
                m_emitter.EmitKeyword2F(TOKEN_KEYWORD_2F_SUB_35, GetInt(context->IntegerConstant()));
                break;
            case MdbLexer::Keyword36:
                m_emitter.EmitKeyword2F(TOKEN_KEYWORD_2F_SUB_36, 0);
                break;
            case MdbLexer::Keyword37:
                m_emitter.EmitKeyword2F(TOKEN_KEYWORD_2F_SUB_37, GetInt(context->IntegerConstant()));
                break;
            default:
                assert(false);
                break;
            }
        }

        void exitKeyword38(MdbParser::Keyword38Context* context) override
        {
            MaterialToken subTokens[2];

            for(auto i = 0u; i < 2u; i++)
            {
                const auto* subToken = context->keyword38Subtoken(i);
                switch (subToken->getStart()->getType())
                {
                case MdbLexer::Keyword39:
                    subTokens[i] = TOKEN_KEYWORD_38_SUB_39;
                    break;
                case MdbLexer::Keyword3A:
                    subTokens[i] = TOKEN_KEYWORD_38_SUB_3A;
                    break;
                case MdbLexer::Keyword3B:
                    subTokens[i] = TOKEN_KEYWORD_38_SUB_3B;
                    break;
                case MdbLexer::Keyword3C:
                    subTokens[i] = TOKEN_KEYWORD_38_SUB_3C;
                    break;
                case MdbLexer::Keyword3D:
                    subTokens[i] = TOKEN_KEYWORD_38_SUB_3D;
                    break;
                case MdbLexer::Keyword3E:
                    subTokens[i] = TOKEN_KEYWORD_38_SUB_3E;
                    break;
                case MdbLexer::Keyword3F:
                    subTokens[i] = TOKEN_KEYWORD_38_SUB_3F;
                    break;
                case MdbLexer::Keyword40:
                    subTokens[i] = TOKEN_KEYWORD_38_SUB_40;
                    break;
                case MdbLexer::Keyword41:
                    subTokens[i] = TOKEN_KEYWORD_38_SUB_41;
                    break;
                case MdbLexer::Keyword42:
                    subTokens[i] = TOKEN_KEYWORD_38_SUB_42;
                    break;
                case MdbLexer::Keyword43:
                    subTokens[i] = TOKEN_KEYWORD_38_SUB_43;
                    break;
                default:
                    assert(false);
                    break;
                }
            }

            m_emitter.EmitKeyword38(subTokens[0], subTokens[1]);
        }

    private:
        uint8_t GetUInt8(antlr4::tree::TerminalNode* node) const
        {
            uint8_t value;
            if (!common_grammar::UInt8Value(node, value))
                m_parser.notifyErrorListeners(node->getSymbol(), "Invalid uint8 value", nullptr);

            return value;
        }

        int GetInt(antlr4::tree::TerminalNode* node) const
        {
            int value;
            if (!common_grammar::IntValue(node, value))
                m_parser.notifyErrorListeners(node->getSymbol(), "Invalid int value", nullptr);

            return value;
        }

        MdbParser& m_parser;
        IMdbEmitter& m_emitter;
    };

    class CustomMdbErrorListener final : public antlr4::BaseErrorListener
    {
        void syntaxError(antlr4::Recognizer* recognizer, antlr4::Token* offendingSymbol, const size_t line, const size_t charPositionInLine, const std::string& msg, std::exception_ptr e) override
        {
            std::ostringstream ss;
            ss << "Parsing MDB failed: L" << line << ':' << charPositionInLine << " " << msg;

            throw MdbCreationException(ss.str());
        }
    };

    class MdbTextReaderImpl
    {
    public:
        MdbTextReaderImpl(std::istream& in, IMdbEmitter& emitter)
            : m_stream(in),
              m_emitter(emitter)
        {
        }

        void Read() const
        {
            CustomMdbErrorListener errors;
            antlr4::ANTLRInputStream inputStream(m_stream);

            gdb::GdbLexer lexer(&inputStream);
            lexer.addErrorListener(&errors);

            antlr4::CommonTokenStream tokenStream(&lexer);
            MdbParser parser(&tokenStream);
            parser.addErrorListener(&errors);

            auto* parseTree = parser.root();

            CustomMdbListener listener(parser, m_emitter);
            antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, parseTree);
        }

        std::istream& m_stream;
        IMdbEmitter& m_emitter;
    };
}

using namespace mdb;

void MdbTextReader::Read(std::istream& input, IMdbEmitter& emitter)
{
    const MdbTextReaderImpl impl(input, emitter);
    impl.Read();
}
