#include "IdbTextReader.h"

#include <iostream>

#pragma warning(push, 0)
#include "Parsing/Common/CommonGrammarHelper.h"
#include "Parsing/Parser/Idb/IdbLexer.h"
#include "Parsing/Parser/Idb/IdbParser.h"
#include "Parsing/Parser/Idb/IdbBaseListener.h"
#pragma warning(pop)

namespace idb
{
    class IdbCreationException final : public std::exception
    {
    public:
        explicit IdbCreationException(std::string msg)
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

    class CustomIdbListener final : public IdbBaseListener
    {
    public:
        explicit CustomIdbListener(IdbParser& parser, IIdbEmitter& emitter)
            : m_parser(parser),
              m_emitter(emitter)
        {
        }

        void enterImages(IdbParser::ImagesContext*) override
        {
            m_emitter.StartImages();
        }

        void exitImages(IdbParser::ImagesContext*) override
        {
            m_emitter.EndImages();
        }

        void exitImageName(IdbParser::ImageNameContext* context) override
        {
            auto imageName = common_grammar::StringValue(context->StringLiteral());
            m_emitter.StartImage(std::move(imageName));
        }

        void exitImage(IdbParser::ImageContext* context) override
        {
            m_emitter.EndImage();
        }

        void exitColorImageProperty(IdbParser::ColorImagePropertyContext* context) override
        {
            uint8_t values[3];
            for (auto i = 0u; i < 3; i++)
            {
                auto* node = context->IntegerConstant(i);
                uint8_t value;
                if (!common_grammar::UInt8Value(node, value))
                    return m_parser.notifyErrorListeners(node->getSymbol(), "Invalid uint8 value", nullptr);

                values[i] = value;
            }

            const auto type = context->colorImagePropertyKeyword()->getStart()->getType();
            if (type == IdbLexer::ChromaKey)
            {
                m_emitter.EmitChromaKey(values[0], values[1], values[2]);
            }
            else
            {
                assert(type == IdbLexer::Tint);

                m_emitter.EmitTint(values[0], values[1], values[2]);
            }
        }

        void exitSingleValueKeywords(IdbParser::SingleValueKeywordsContext* context) override
        {
            const auto keywordType = context->getStart()->getType();
            switch (keywordType)
            {
            case IdbLexer::FlipVertical:
                m_emitter.EmitFlipVertical();
                break;
            case IdbLexer::Bmp:
                m_emitter.EmitBmp();
                break;
            case IdbLexer::Tga:
                m_emitter.EmitTga();
                break;
            default:
                assert(false);
                break;
            }
        }

    private:
        IdbParser& m_parser;
        IIdbEmitter& m_emitter;
    };

    class CustomTdbErrorListener final : public antlr4::BaseErrorListener
    {
        void syntaxError(antlr4::Recognizer* recognizer, antlr4::Token* offendingSymbol, const size_t line, const size_t charPositionInLine, const std::string& msg,
                         std::exception_ptr e) override
        {
            std::ostringstream ss;
            ss << "Parsing IDB failed: L" << line << ':' << charPositionInLine << " " << msg;

            throw IdbCreationException(ss.str());
        }
    };

    class IdbTextReaderImpl
    {
    public:
        IdbTextReaderImpl(std::istream& in, IIdbEmitter& emitter)
            : m_stream(in),
              m_emitter(emitter)
        {
        }

        void Read() const
        {
            CustomTdbErrorListener errors;
            antlr4::ANTLRInputStream inputStream(m_stream);

            IdbLexer lexer(&inputStream);
            lexer.addErrorListener(&errors);

            antlr4::CommonTokenStream tokenStream(&lexer);
            IdbParser parser(&tokenStream);
            parser.addErrorListener(&errors);

            auto* parseTree = parser.root();

            CustomIdbListener listener(parser, m_emitter);
            antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, parseTree);
        }

        std::istream& m_stream;
        IIdbEmitter& m_emitter;
    };
}

using namespace idb;

void IdbTextReader::Read(std::istream& input, IIdbEmitter& emitter)
{
    const IdbTextReaderImpl impl(input, emitter);
    impl.Read();
}
