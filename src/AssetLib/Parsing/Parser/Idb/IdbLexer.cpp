
// Generated from ..\..\..\src\AssetLib\Parsing\Parser\Idb\Idb.g4 by ANTLR 4.10.1

#include "IdbLexer.h"

using namespace antlr4;

using namespace idb;

using namespace antlr4;

namespace
{

    struct IdbLexerStaticData final
    {
        IdbLexerStaticData(std::vector<std::string> ruleNames,
                           std::vector<std::string> channelNames,
                           std::vector<std::string> modeNames,
                           std::vector<std::string> literalNames,
                           std::vector<std::string> symbolicNames)
            : ruleNames(std::move(ruleNames)),
              channelNames(std::move(channelNames)),
              modeNames(std::move(modeNames)),
              literalNames(std::move(literalNames)),
              symbolicNames(std::move(symbolicNames)),
              vocabulary(this->literalNames, this->symbolicNames)
        {
        }

        IdbLexerStaticData(const IdbLexerStaticData&) = delete;
        IdbLexerStaticData(IdbLexerStaticData&&) = delete;
        IdbLexerStaticData& operator=(const IdbLexerStaticData&) = delete;
        IdbLexerStaticData& operator=(IdbLexerStaticData&&) = delete;

        std::vector<antlr4::dfa::DFA> decisionToDFA;
        antlr4::atn::PredictionContextCache sharedContextCache;
        const std::vector<std::string> ruleNames;
        const std::vector<std::string> channelNames;
        const std::vector<std::string> modeNames;
        const std::vector<std::string> literalNames;
        const std::vector<std::string> symbolicNames;
        const antlr4::dfa::Vocabulary vocabulary;
        antlr4::atn::SerializedATNView serializedATN;
        std::unique_ptr<antlr4::atn::ATN> atn;
    };

    std::once_flag idblexerLexerOnceFlag;
    IdbLexerStaticData* idblexerLexerStaticData = nullptr;

    void idblexerLexerInitialize()
    {
        assert(idblexerLexerStaticData == nullptr);
        auto staticData = std::make_unique<IdbLexerStaticData>(
            std::vector<std::string>{"T__0",
                                     "T__1",
                                     "Images",
                                     "Image",
                                     "FlipVertical",
                                     "Bmp",
                                     "Tga",
                                     "ChromaKey",
                                     "Tint",
                                     "IntegerConstant",
                                     "DecimalConstant",
                                     "HexadecimalConstant",
                                     "HexadecimalPrefix",
                                     "FloatingConstant",
                                     "DigitSequence",
                                     "NonzeroDigit",
                                     "Digit",
                                     "HexadecimalDigit",
                                     "Zero",
                                     "IntegerSign",
                                     "StringLiteral",
                                     "SCharSequence",
                                     "SChar",
                                     "EscapeSequence",
                                     "Whitespace",
                                     "Newline",
                                     "BlockComment",
                                     "LineComment"},
            std::vector<std::string>{"DEFAULT_TOKEN_CHANNEL", "HIDDEN"},
            std::vector<std::string>{"DEFAULT_MODE"},
            std::vector<std::string>{"", "'{'", "'}'", "'images'", "'image'", "'flipVertical'", "'bmp'", "'tga'", "'chromaKey'", "'tint'"},
            std::vector<std::string>{"",
                                     "",
                                     "",
                                     "Images",
                                     "Image",
                                     "FlipVertical",
                                     "Bmp",
                                     "Tga",
                                     "ChromaKey",
                                     "Tint",
                                     "IntegerConstant",
                                     "FloatingConstant",
                                     "DigitSequence",
                                     "StringLiteral",
                                     "Whitespace",
                                     "Newline",
                                     "BlockComment",
                                     "LineComment"});
        static const int32_t serializedATNSegment[] = {
            4,   0,   17,  233, 6,   -1,  2,   0,   7,   0,   2,   1,   7,   1,   2,   2,   7,   2,   2,   3,  7,   3,   2,   4,   7,   4,   2,   5,   7,   5,
            2,   6,   7,   6,   2,   7,   7,   7,   2,   8,   7,   8,   2,   9,   7,   9,   2,   10,  7,   10, 2,   11,  7,   11,  2,   12,  7,   12,  2,   13,
            7,   13,  2,   14,  7,   14,  2,   15,  7,   15,  2,   16,  7,   16,  2,   17,  7,   17,  2,   18, 7,   18,  2,   19,  7,   19,  2,   20,  7,   20,
            2,   21,  7,   21,  2,   22,  7,   22,  2,   23,  7,   23,  2,   24,  7,   24,  2,   25,  7,   25, 2,   26,  7,   26,  2,   27,  7,   27,  1,   0,
            1,   0,   1,   1,   1,   1,   1,   2,   1,   2,   1,   2,   1,   2,   1,   2,   1,   2,   1,   2,  1,   3,   1,   3,   1,   3,   1,   3,   1,   3,
            1,   3,   1,   4,   1,   4,   1,   4,   1,   4,   1,   4,   1,   4,   1,   4,   1,   4,   1,   4,  1,   4,   1,   4,   1,   4,   1,   4,   1,   5,
            1,   5,   1,   5,   1,   5,   1,   6,   1,   6,   1,   6,   1,   6,   1,   7,   1,   7,   1,   7,  1,   7,   1,   7,   1,   7,   1,   7,   1,   7,
            1,   7,   1,   7,   1,   8,   1,   8,   1,   8,   1,   8,   1,   8,   1,   9,   1,   9,   1,   9,  3,   9,   114, 8,   9,   1,   10,  3,   10,  117,
            8,   10,  1,   10,  4,   10,  120, 8,   10,  11,  10,  12,  10,  121, 1,   11,  3,   11,  125, 8,  11,  1,   11,  1,   11,  4,   11,  129, 8,   11,
            11,  11,  12,  11,  130, 1,   12,  1,   12,  1,   12,  1,   13,  3,   13,  137, 8,   13,  1,   13, 3,   13,  140, 8,   13,  1,   13,  1,   13,  1,
            13,  3,   13,  145, 8,   13,  1,   13,  1,   13,  1,   13,  3,   13,  150, 8,   13,  1,   14,  4,  14,  153, 8,   14,  11,  14,  12,  14,  154, 1,
            15,  1,   15,  1,   16,  1,   16,  1,   17,  1,   17,  1,   18,  3,   18,  164, 8,   18,  1,   18, 1,   18,  1,   19,  1,   19,  1,   20,  1,   20,
            3,   20,  172, 8,   20,  1,   20,  1,   20,  1,   21,  4,   21,  177, 8,   21,  11,  21,  12,  21, 178, 1,   22,  1,   22,  1,   22,  1,   22,  1,
            22,  1,   22,  1,   22,  3,   22,  188, 8,   22,  1,   23,  1,   23,  1,   23,  1,   24,  4,   24, 194, 8,   24,  11,  24,  12,  24,  195, 1,   24,
            1,   24,  1,   25,  1,   25,  3,   25,  202, 8,   25,  1,   25,  3,   25,  205, 8,   25,  1,   25, 1,   25,  1,   26,  1,   26,  1,   26,  1,   26,
            5,   26,  213, 8,   26,  10,  26,  12,  26,  216, 9,   26,  1,   26,  1,   26,  1,   26,  1,   26, 1,   26,  1,   27,  1,   27,  1,   27,  1,   27,
            5,   27,  227, 8,   27,  10,  27,  12,  27,  230, 9,   27,  1,   27,  1,   27,  1,   214, 0,   28, 1,   1,   3,   2,   5,   3,   7,   4,   9,   5,
            11,  6,   13,  7,   15,  8,   17,  9,   19,  10,  21,  0,   23,  0,   25,  0,   27,  11,  29,  12, 31,  0,   33,  0,   35,  0,   37,  0,   39,  0,
            41,  13,  43,  0,   45,  0,   47,  0,   49,  14,  51,  15,  53,  16,  55,  17,  1,   0,   9,   2,  0,   88,  88,  120, 120, 1,   0,   49,  57,  1,
            0,   48,  57,  3,   0,   48,  57,  65,  70,  97,  102, 2,   0,   43,  43,  45,  45,  4,   0,   10, 10,  13,  13,  34,  34,  92,  92,  10,  0,   34,
            34,  39,  39,  63,  63,  92,  92,  97,  98,  102, 102, 110, 110, 114, 114, 116, 116, 118, 118, 2,  0,   9,   9,   32,  32,  2,   0,   10,  10,  13,
            13,  243, 0,   1,   1,   0,   0,   0,   0,   3,   1,   0,   0,   0,   0,   5,   1,   0,   0,   0,  0,   7,   1,   0,   0,   0,   0,   9,   1,   0,
            0,   0,   0,   11,  1,   0,   0,   0,   0,   13,  1,   0,   0,   0,   0,   15,  1,   0,   0,   0,  0,   17,  1,   0,   0,   0,   0,   19,  1,   0,
            0,   0,   0,   27,  1,   0,   0,   0,   0,   29,  1,   0,   0,   0,   0,   41,  1,   0,   0,   0,  0,   49,  1,   0,   0,   0,   0,   51,  1,   0,
            0,   0,   0,   53,  1,   0,   0,   0,   0,   55,  1,   0,   0,   0,   1,   57,  1,   0,   0,   0,  3,   59,  1,   0,   0,   0,   5,   61,  1,   0,
            0,   0,   7,   68,  1,   0,   0,   0,   9,   74,  1,   0,   0,   0,   11,  87,  1,   0,   0,   0,  13,  91,  1,   0,   0,   0,   15,  95,  1,   0,
            0,   0,   17,  105, 1,   0,   0,   0,   19,  113, 1,   0,   0,   0,   21,  116, 1,   0,   0,   0,  23,  124, 1,   0,   0,   0,   25,  132, 1,   0,
            0,   0,   27,  149, 1,   0,   0,   0,   29,  152, 1,   0,   0,   0,   31,  156, 1,   0,   0,   0,  33,  158, 1,   0,   0,   0,   35,  160, 1,   0,
            0,   0,   37,  163, 1,   0,   0,   0,   39,  167, 1,   0,   0,   0,   41,  169, 1,   0,   0,   0,  43,  176, 1,   0,   0,   0,   45,  187, 1,   0,
            0,   0,   47,  189, 1,   0,   0,   0,   49,  193, 1,   0,   0,   0,   51,  204, 1,   0,   0,   0,  53,  208, 1,   0,   0,   0,   55,  222, 1,   0,
            0,   0,   57,  58,  5,   123, 0,   0,   58,  2,   1,   0,   0,   0,   59,  60,  5,   125, 0,   0,  60,  4,   1,   0,   0,   0,   61,  62,  5,   105,
            0,   0,   62,  63,  5,   109, 0,   0,   63,  64,  5,   97,  0,   0,   64,  65,  5,   103, 0,   0,  65,  66,  5,   101, 0,   0,   66,  67,  5,   115,
            0,   0,   67,  6,   1,   0,   0,   0,   68,  69,  5,   105, 0,   0,   69,  70,  5,   109, 0,   0,  70,  71,  5,   97,  0,   0,   71,  72,  5,   103,
            0,   0,   72,  73,  5,   101, 0,   0,   73,  8,   1,   0,   0,   0,   74,  75,  5,   102, 0,   0,  75,  76,  5,   108, 0,   0,   76,  77,  5,   105,
            0,   0,   77,  78,  5,   112, 0,   0,   78,  79,  5,   86,  0,   0,   79,  80,  5,   101, 0,   0,  80,  81,  5,   114, 0,   0,   81,  82,  5,   116,
            0,   0,   82,  83,  5,   105, 0,   0,   83,  84,  5,   99,  0,   0,   84,  85,  5,   97,  0,   0,  85,  86,  5,   108, 0,   0,   86,  10,  1,   0,
            0,   0,   87,  88,  5,   98,  0,   0,   88,  89,  5,   109, 0,   0,   89,  90,  5,   112, 0,   0,  90,  12,  1,   0,   0,   0,   91,  92,  5,   116,
            0,   0,   92,  93,  5,   103, 0,   0,   93,  94,  5,   97,  0,   0,   94,  14,  1,   0,   0,   0,  95,  96,  5,   99,  0,   0,   96,  97,  5,   104,
            0,   0,   97,  98,  5,   114, 0,   0,   98,  99,  5,   111, 0,   0,   99,  100, 5,   109, 0,   0,  100, 101, 5,   97,  0,   0,   101, 102, 5,   75,
            0,   0,   102, 103, 5,   101, 0,   0,   103, 104, 5,   121, 0,   0,   104, 16,  1,   0,   0,   0,  105, 106, 5,   116, 0,   0,   106, 107, 5,   105,
            0,   0,   107, 108, 5,   110, 0,   0,   108, 109, 5,   116, 0,   0,   109, 18,  1,   0,   0,   0,  110, 114, 3,   21,  10,  0,   111, 114, 3,   23,
            11,  0,   112, 114, 3,   37,  18,  0,   113, 110, 1,   0,   0,   0,   113, 111, 1,   0,   0,   0,  113, 112, 1,   0,   0,   0,   114, 20,  1,   0,
            0,   0,   115, 117, 3,   39,  19,  0,   116, 115, 1,   0,   0,   0,   116, 117, 1,   0,   0,   0,  117, 119, 1,   0,   0,   0,   118, 120, 3,   33,
            16,  0,   119, 118, 1,   0,   0,   0,   120, 121, 1,   0,   0,   0,   121, 119, 1,   0,   0,   0,  121, 122, 1,   0,   0,   0,   122, 22,  1,   0,
            0,   0,   123, 125, 3,   39,  19,  0,   124, 123, 1,   0,   0,   0,   124, 125, 1,   0,   0,   0,  125, 126, 1,   0,   0,   0,   126, 128, 3,   25,
            12,  0,   127, 129, 3,   35,  17,  0,   128, 127, 1,   0,   0,   0,   129, 130, 1,   0,   0,   0,  130, 128, 1,   0,   0,   0,   130, 131, 1,   0,
            0,   0,   131, 24,  1,   0,   0,   0,   132, 133, 5,   48,  0,   0,   133, 134, 7,   0,   0,   0,  134, 26,  1,   0,   0,   0,   135, 137, 3,   39,
            19,  0,   136, 135, 1,   0,   0,   0,   136, 137, 1,   0,   0,   0,   137, 138, 1,   0,   0,   0,  138, 140, 3,   29,  14,  0,   139, 136, 1,   0,
            0,   0,   139, 140, 1,   0,   0,   0,   140, 141, 1,   0,   0,   0,   141, 142, 5,   46,  0,   0,  142, 150, 3,   29,  14,  0,   143, 145, 3,   39,
            19,  0,   144, 143, 1,   0,   0,   0,   144, 145, 1,   0,   0,   0,   145, 146, 1,   0,   0,   0,  146, 147, 3,   29,  14,  0,   147, 148, 5,   46,
            0,   0,   148, 150, 1,   0,   0,   0,   149, 139, 1,   0,   0,   0,   149, 144, 1,   0,   0,   0,  150, 28,  1,   0,   0,   0,   151, 153, 3,   33,
            16,  0,   152, 151, 1,   0,   0,   0,   153, 154, 1,   0,   0,   0,   154, 152, 1,   0,   0,   0,  154, 155, 1,   0,   0,   0,   155, 30,  1,   0,
            0,   0,   156, 157, 7,   1,   0,   0,   157, 32,  1,   0,   0,   0,   158, 159, 7,   2,   0,   0,  159, 34,  1,   0,   0,   0,   160, 161, 7,   3,
            0,   0,   161, 36,  1,   0,   0,   0,   162, 164, 3,   39,  19,  0,   163, 162, 1,   0,   0,   0,  163, 164, 1,   0,   0,   0,   164, 165, 1,   0,
            0,   0,   165, 166, 5,   48,  0,   0,   166, 38,  1,   0,   0,   0,   167, 168, 7,   4,   0,   0,  168, 40,  1,   0,   0,   0,   169, 171, 5,   34,
            0,   0,   170, 172, 3,   43,  21,  0,   171, 170, 1,   0,   0,   0,   171, 172, 1,   0,   0,   0,  172, 173, 1,   0,   0,   0,   173, 174, 5,   34,
            0,   0,   174, 42,  1,   0,   0,   0,   175, 177, 3,   45,  22,  0,   176, 175, 1,   0,   0,   0,  177, 178, 1,   0,   0,   0,   178, 176, 1,   0,
            0,   0,   178, 179, 1,   0,   0,   0,   179, 44,  1,   0,   0,   0,   180, 188, 8,   5,   0,   0,  181, 188, 3,   47,  23,  0,   182, 183, 5,   92,
            0,   0,   183, 188, 5,   10,  0,   0,   184, 185, 5,   92,  0,   0,   185, 186, 5,   13,  0,   0,  186, 188, 5,   10,  0,   0,   187, 180, 1,   0,
            0,   0,   187, 181, 1,   0,   0,   0,   187, 182, 1,   0,   0,   0,   187, 184, 1,   0,   0,   0,  188, 46,  1,   0,   0,   0,   189, 190, 5,   92,
            0,   0,   190, 191, 7,   6,   0,   0,   191, 48,  1,   0,   0,   0,   192, 194, 7,   7,   0,   0,  193, 192, 1,   0,   0,   0,   194, 195, 1,   0,
            0,   0,   195, 193, 1,   0,   0,   0,   195, 196, 1,   0,   0,   0,   196, 197, 1,   0,   0,   0,  197, 198, 6,   24,  0,   0,   198, 50,  1,   0,
            0,   0,   199, 201, 5,   13,  0,   0,   200, 202, 5,   10,  0,   0,   201, 200, 1,   0,   0,   0,  201, 202, 1,   0,   0,   0,   202, 205, 1,   0,
            0,   0,   203, 205, 5,   10,  0,   0,   204, 199, 1,   0,   0,   0,   204, 203, 1,   0,   0,   0,  205, 206, 1,   0,   0,   0,   206, 207, 6,   25,
            0,   0,   207, 52,  1,   0,   0,   0,   208, 209, 5,   47,  0,   0,   209, 210, 5,   42,  0,   0,  210, 214, 1,   0,   0,   0,   211, 213, 9,   0,
            0,   0,   212, 211, 1,   0,   0,   0,   213, 216, 1,   0,   0,   0,   214, 215, 1,   0,   0,   0,  214, 212, 1,   0,   0,   0,   215, 217, 1,   0,
            0,   0,   216, 214, 1,   0,   0,   0,   217, 218, 5,   42,  0,   0,   218, 219, 5,   47,  0,   0,  219, 220, 1,   0,   0,   0,   220, 221, 6,   26,
            0,   0,   221, 54,  1,   0,   0,   0,   222, 223, 5,   47,  0,   0,   223, 224, 5,   47,  0,   0,  224, 228, 1,   0,   0,   0,   225, 227, 8,   8,
            0,   0,   226, 225, 1,   0,   0,   0,   227, 230, 1,   0,   0,   0,   228, 226, 1,   0,   0,   0,  228, 229, 1,   0,   0,   0,   229, 231, 1,   0,
            0,   0,   230, 228, 1,   0,   0,   0,   231, 232, 6,   27,  0,   0,   232, 56,  1,   0,   0,   0,  20,  0,   113, 116, 121, 124, 130, 136, 139, 144,
            149, 154, 163, 171, 178, 187, 195, 201, 204, 214, 228, 1,   6,   0,   0};
        staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

        antlr4::atn::ATNDeserializer deserializer;
        staticData->atn = deserializer.deserialize(staticData->serializedATN);

        const size_t count = staticData->atn->getNumberOfDecisions();
        staticData->decisionToDFA.reserve(count);
        for (size_t i = 0; i < count; i++)
        {
            staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
        }
        idblexerLexerStaticData = staticData.release();
    }

} // namespace

IdbLexer::IdbLexer(CharStream* input)
    : Lexer(input)
{
    IdbLexer::initialize();
    _interpreter =
        new atn::LexerATNSimulator(this, *idblexerLexerStaticData->atn, idblexerLexerStaticData->decisionToDFA, idblexerLexerStaticData->sharedContextCache);
}

IdbLexer::~IdbLexer()
{
    delete _interpreter;
}

std::string IdbLexer::getGrammarFileName() const
{
    return "Idb.g4";
}

const std::vector<std::string>& IdbLexer::getRuleNames() const
{
    return idblexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& IdbLexer::getChannelNames() const
{
    return idblexerLexerStaticData->channelNames;
}

const std::vector<std::string>& IdbLexer::getModeNames() const
{
    return idblexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& IdbLexer::getVocabulary() const
{
    return idblexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView IdbLexer::getSerializedATN() const
{
    return idblexerLexerStaticData->serializedATN;
}

const atn::ATN& IdbLexer::getATN() const
{
    return *idblexerLexerStaticData->atn;
}

void IdbLexer::initialize()
{
    std::call_once(idblexerLexerOnceFlag, idblexerLexerInitialize);
}
