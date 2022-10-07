#include "IdbCreator.h"

#include <iostream>
#include <sstream>

#include "Idb.h"
#include "Utils/StringUtils.h"
#include "TokenStream.h"

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
        explicit IdbCreationException(char const* msg)
            : exception(msg)
        {
        }
    };

    class IdbParserState
    {
    public:
        explicit IdbParserState(ITokenOutputStream* out)
            : m_image_count(0u),
            m_out(out)
        {
        }

        void BeginImage(const std::string& imageName)
        {
            m_image_count++;
            m_out->WriteCustom(TOKEN_IMAGE);
            m_out->WriteString(imageName);
            m_out->WriteLeftCurly();
        }

        void EndImage() const
        {
            m_out->WriteRightCurly();
        }

        size_t m_image_count;
        ITokenOutputStream* m_out;
    };

    class CustomIdbListener final : public IdbBaseListener
    {
    public:
        explicit CustomIdbListener(IdbParser& parser, IdbParserState& state)
            : m_parser(parser),
            m_state(state)
        {
        }

        void exitImageName(IdbParser::ImageNameContext* context) override
        {
            const auto imageName = common_grammar::StringValue(context->StringLiteral());
            m_state.BeginImage(imageName);
        }

        void exitImage(IdbParser::ImageContext* context) override
        {
            m_state.EndImage();
        }

        void exitColorImageProperty(IdbParser::ColorImagePropertyContext* context) override
        {
            const auto keywordType = context->colorImagePropertyKeyword()->getStart()->getType();

            if (keywordType == IdbLexer::ChromaKey)
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_CHROMA_KEY);
            else if (keywordType == IdbLexer::Tint)
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_TINT);
            else
                assert(false);

            for (auto i = 0u; i < 3; i++)
            {
                auto* node = context->IntegerConstant(i);
                uint8_t value;
                if (!common_grammar::UInt8Value(node, value))
                    return m_parser.notifyErrorListeners(node->getSymbol(), "Invalid uint8 value", nullptr);

                m_state.m_out->WriteUInt8(value);
            }
        }

        void exitSingleValueKeywords(IdbParser::SingleValueKeywordsContext* context) override
        {
            const auto keywordType = context->getStart()->getType();
            switch (keywordType)
            {
            case IdbLexer::FlipVertical:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_FLIP_VERTICAL);
                break;
            case IdbLexer::Bmp:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_BMP);
                break;
            case IdbLexer::Tga:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_TGA);
                break;
            default:
                assert(false);
                break;
            }
        }

    private:
        IdbParser& m_parser;
        IdbParserState& m_state;
    };

    class CustomIdbErrorListener final : public antlr4::BaseErrorListener
    {
        void syntaxError(antlr4::Recognizer* recognizer, antlr4::Token* offendingSymbol, size_t line, size_t charPositionInLine, const std::string& msg, std::exception_ptr e) override
        {
            throw IdbCreationException("Parsing IDB failed");
        }
    };
}

using namespace idb;


bool IdbCreator::SupportFileExtension(const std::string& extension) const
{
    return extension == ".IDB";
}

void IdbCreator::ProcessFile(const std::string& filePath, const void* inputData, const size_t inputDataSize, std::ostream& output) const
{
    std::cout << "Idb creating \"" << filePath << "\"\n";

    CustomIdbErrorListener errors;
    antlr4::ANTLRInputStream inputStream(static_cast<const char*>(inputData), inputDataSize);

    IdbLexer lexer(&inputStream);
    lexer.addErrorListener(&errors);

    antlr4::CommonTokenStream tokenStream(&lexer);
    IdbParser parser(&tokenStream);
    parser.addErrorListener(&errors);
    parser.setErrorHandler(std::make_shared<antlr4::BailErrorStrategy>());

    auto* parseTree = parser.root();

    std::ostringstream imageData;
    const auto imageDataTokens = ITokenOutputStream::Create(imageData);
    IdbParserState parserState(imageDataTokens.get());
    CustomIdbListener listener(parser, parserState);
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, parseTree);

    const auto tokenOut = ITokenOutputStream::Create(output);
    tokenOut->WriteCustom(TOKEN_IMAGE_DB);
    tokenOut->WriteLeftBracket();
    tokenOut->WriteInteger(static_cast<int>(parserState.m_image_count));
    tokenOut->WriteRightBracket();
    tokenOut->WriteLeftCurly();

    output << imageData.str();

    tokenOut->WriteRightCurly();

    std::cout << "Successfully created Idb \"" << filePath << "\" with " << parserState.m_image_count << " images\n";
}
