#include "TdbCreator.h"

#include <iostream>
#include <sstream>

#include "Tdb.h"
#include "Utils/StringUtils.h"
#include "TokenStream.h"

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
        explicit TdbCreationException(char const* msg)
            : exception(msg)
        {
        }
    };

    class TdbParserState
    {
    public:
        explicit TdbParserState(ITokenOutputStream* out)
            : m_texture_count(0u),
            m_out(out)
        {
        }

        void BeginTexture(const std::string& textureName)
        {
            m_texture_count++;
            m_out->WriteCustom(TOKEN_TEXTURE);
            m_out->WriteString(textureName);
            m_out->WriteLeftCurly();
        }

        void EndTexture() const
        {
            m_out->WriteRightCurly();
        }

        size_t m_texture_count;
        ITokenOutputStream* m_out;
    };

    class CustomTdbListener final : public TdbBaseListener
    {
    public:
        explicit CustomTdbListener(TdbParser& parser, TdbParserState& state)
            : m_parser(parser),
            m_state(state)
        {
        }

        void exitTextureName(TdbParser::TextureNameContext* context) override
        {
            const auto textureName = common_grammar::StringValue(context->StringLiteral());
            m_state.BeginTexture(textureName);
        }

        void exitTexture(TdbParser::TextureContext* context) override
        {
            m_state.EndTexture();
        }

        void exitColorTextureProperty(TdbParser::ColorTexturePropertyContext* context) override
        {
            assert(context->colorTexturePropertyKeyword()->getStart()->getType() == TdbLexer::ChromaKey);
            m_state.m_out->WriteCustom(TOKEN_KEYWORD_CHROMA_KEY);

            for (auto i = 0u; i < 3; i++)
            {
                auto* node = context->IntegerConstant(i);
                uint8_t value;
                if (!common_grammar::UInt8Value(node, value))
                    return m_parser.notifyErrorListeners(node->getSymbol(), "Invalid uint8 value", nullptr);

                m_state.m_out->WriteUInt8(value);
            }
        }

        void exitIntTextureProperty(TdbParser::IntTexturePropertyContext* context) override
        {
            assert(context->intTexturePropertyKeyword()->getStart()->getType() == TdbLexer::Keyword29);
            m_state.m_out->WriteCustom(TOKEN_KEYWORD_29);

            auto* node = context->IntegerConstant();
            int value;
            if (!common_grammar::IntValue(node, value))
                return m_parser.notifyErrorListeners(node->getSymbol(), "Invalid int value", nullptr);

            m_state.m_out->WriteInteger(value);
        }

        void exitSingleValueKeywords(TdbParser::SingleValueKeywordsContext* context) override
        {
            const auto keywordType = context->getStart()->getType();
            switch (keywordType)
            {
            case TdbLexer::FlipVertically:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_FLIP_VERTICALLY);
                break;
            case TdbLexer::Bmp:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_BMP);
                break;
            case TdbLexer::Tga:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_TGA);
                break;
            case TdbLexer::Keyword2D:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_2D);
                break;
            case TdbLexer::Keyword2E:
                m_state.m_out->WriteCustom(TOKEN_KEYWORD_2E);
                break;
            default:
                assert(false);
                break;
            }
        }

    private:
        TdbParser& m_parser;
        TdbParserState& m_state;
    };

    class CustomTdbErrorListener final : public antlr4::BaseErrorListener
    {
        void syntaxError(antlr4::Recognizer* recognizer, antlr4::Token* offendingSymbol, size_t line, size_t charPositionInLine, const std::string& msg, std::exception_ptr e) override
        {
            throw TdbCreationException("Parsing TDB failed");
        }
    };
}

using namespace tdb;


bool TdbCreator::SupportFileExtension(const std::string& extension) const
{
    return extension == ".TDB";
}

void TdbCreator::ProcessFile(const std::string& filePath, const void* inputData, const size_t inputDataSize, std::ostream& output) const
{
    std::cout << "Tdb creating \"" << filePath << "\"\n";

    CustomTdbErrorListener errors;
    antlr4::ANTLRInputStream inputStream(static_cast<const char*>(inputData), inputDataSize);

    TdbLexer lexer(&inputStream);
    lexer.addErrorListener(&errors);

    antlr4::CommonTokenStream tokenStream(&lexer);
    TdbParser parser(&tokenStream);
    parser.addErrorListener(&errors);
    parser.setErrorHandler(std::make_shared<antlr4::BailErrorStrategy>());

    auto* parseTree = parser.root();

    std::ostringstream textureData;
    const auto textureDataTokens = ITokenOutputStream::Create(textureData);
    TdbParserState parserState(textureDataTokens.get());
    CustomTdbListener listener(parser, parserState);
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, parseTree);

    const auto tokenOut = ITokenOutputStream::Create(output);
    tokenOut->WriteCustom(TOKEN_TEXTURE_DB);
    tokenOut->WriteLeftBracket();
    tokenOut->WriteInteger(static_cast<int>(parserState.m_texture_count));
    tokenOut->WriteRightBracket();
    tokenOut->WriteLeftCurly();

    output << textureData.str();

    tokenOut->WriteRightCurly();

    std::cout << "Successfully created Tdb \"" << filePath << "\" with " << parserState.m_texture_count << " textures\n";
}
