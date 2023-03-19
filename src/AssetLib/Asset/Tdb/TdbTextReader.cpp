#include "TdbTextReader.h"

#include <iostream>

#include "Tdb.h"

#pragma warning(push, 0)
#include "Parsing/Common/CommonGrammarHelper.h"
#include "Parsing/Parser/Tdb/TdbLexer.h"
#include "Parsing/Parser/Tdb/TdbParser.h"
#include "Parsing/Parser/Tdb/TdbBaseListener.h"
#pragma warning(pop)

namespace tdb
{
    class TdbCreationException final : public std::exception
    {
    public:
        explicit TdbCreationException(std::string msg)
            : m_msg(std::move(msg))
        {
        }

        [[nodiscard]] char const* what() const noexcept override
        {
            return m_msg.c_str();
        }

    private:
        std::string m_msg;
    };

    class CustomTdbListener final : public TdbBaseListener
    {
    public:
        explicit CustomTdbListener(TdbParser& parser, ITdbEmitter& emitter)
            : m_parser(parser),
              m_emitter(emitter)
        {
        }

        void enterTextures(TdbParser::TexturesContext*) override
        {
            m_emitter.StartTextures();
        }

        void exitTextures(TdbParser::TexturesContext*) override
        {
            m_emitter.EndTextures();
        }

        void exitTextureName(TdbParser::TextureNameContext* context) override
        {
            auto textureName = common_grammar::StringValue(context->StringLiteral());
            m_emitter.StartTexture(std::move(textureName));
        }

        void exitTexture(TdbParser::TextureContext* context) override
        {
            m_emitter.EndTexture();
        }

        void exitColorTextureProperty(TdbParser::ColorTexturePropertyContext* context) override
        {
            assert(context->colorTexturePropertyKeyword()->getStart()->getType() == TdbLexer::ChromaKey);

            uint8_t values[3];
            for (auto i = 0u; i < 3; i++)
            {
                auto* node = context->IntegerConstant(i);
                uint8_t value;
                if (!common_grammar::UInt8Value(node, value))
                    return m_parser.notifyErrorListeners(node->getSymbol(), "Invalid uint8 value", nullptr);

                values[i] = value;
            }

            m_emitter.EmitChromaKey(values[0], values[1], values[2]);
        }

        void exitIntTextureProperty(TdbParser::IntTexturePropertyContext* context) override
        {
            assert(context->intTexturePropertyKeyword()->getStart()->getType() == TdbLexer::Keyword29);

            auto* node = context->IntegerConstant();
            int value;
            if (!common_grammar::IntValue(node, value))
                return m_parser.notifyErrorListeners(node->getSymbol(), "Invalid int value", nullptr);

            m_emitter.EmitKeyword29(value);
        }

        void exitSingleValueKeywords(TdbParser::SingleValueKeywordsContext* context) override
        {
            const auto keywordType = context->getStart()->getType();
            switch (keywordType)
            {
            case TdbLexer::FlipVertical:
                m_emitter.EmitFlipVertical();
                break;
            case TdbLexer::Bmp:
                m_emitter.EmitBmp();
                break;
            case TdbLexer::Tga:
                m_emitter.EmitTga();
                break;
            case TdbLexer::Keyword2D:
                m_emitter.EmitKeyword2D();
                break;
            case TdbLexer::Keyword2E:
                m_emitter.EmitKeyword2E();
                break;
            default:
                assert(false);
                break;
            }
        }

    private:
        TdbParser& m_parser;
        ITdbEmitter& m_emitter;
    };

    class CustomTdbErrorListener final : public antlr4::BaseErrorListener
    {
        void syntaxError(antlr4::Recognizer* recognizer, antlr4::Token* offendingSymbol, const size_t line, const size_t charPositionInLine, const std::string& msg,
                         std::exception_ptr e) override
        {
            std::ostringstream ss;
            ss << "Parsing TDB failed: L" << line << ':' << charPositionInLine << " " << msg;

            throw TdbCreationException(ss.str());
        }
    };

    class TdbTextReaderImpl
    {
    public:
        TdbTextReaderImpl(std::istream& in, ITdbEmitter& emitter)
            : m_stream(in),
              m_emitter(emitter)
        {
        }

        void Read() const
        {
            CustomTdbErrorListener errors;
            antlr4::ANTLRInputStream inputStream(m_stream);

            TdbLexer lexer(&inputStream);
            lexer.addErrorListener(&errors);

            antlr4::CommonTokenStream tokenStream(&lexer);
            TdbParser parser(&tokenStream);
            parser.addErrorListener(&errors);

            auto* parseTree = parser.root();

            CustomTdbListener listener(parser, m_emitter);
            antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, parseTree);
        }

        std::istream& m_stream;
        ITdbEmitter& m_emitter;
    };
}

using namespace tdb;

void TdbTextReader::Read(std::istream& input, ITdbEmitter& emitter)
{
    const TdbTextReaderImpl impl(input, emitter);
    impl.Read();
}
