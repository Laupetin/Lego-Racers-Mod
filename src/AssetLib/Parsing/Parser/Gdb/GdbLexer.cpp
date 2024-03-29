
// Generated from ..\..\..\src\AssetLib\Parsing\Parser\Gdb\Gdb.g4 by ANTLR 4.10.1

#include "GdbLexer.h"

using namespace antlr4;

using namespace gdb;

using namespace antlr4;

namespace
{

    struct GdbLexerStaticData final
    {
        GdbLexerStaticData(std::vector<std::string> ruleNames,
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

        GdbLexerStaticData(const GdbLexerStaticData&) = delete;
        GdbLexerStaticData(GdbLexerStaticData&&) = delete;
        GdbLexerStaticData& operator=(const GdbLexerStaticData&) = delete;
        GdbLexerStaticData& operator=(GdbLexerStaticData&&) = delete;

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

    std::once_flag gdblexerLexerOnceFlag;
    GdbLexerStaticData* gdblexerLexerStaticData = nullptr;

    void gdblexerLexerInitialize()
    {
        assert(gdblexerLexerStaticData == nullptr);
        auto staticData = std::make_unique<GdbLexerStaticData>(std::vector<std::string>{"T__0",
                                                                                        "T__1",
                                                                                        "Materials",
                                                                                        "Scale",
                                                                                        "Vertices",
                                                                                        "Faces",
                                                                                        "Meta",
                                                                                        "Object",
                                                                                        "Vertex",
                                                                                        "Uv",
                                                                                        "Color",
                                                                                        "Normal",
                                                                                        "Texture",
                                                                                        "Face",
                                                                                        "Keyword2F",
                                                                                        "Keyword30",
                                                                                        "Bone",
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
                                                               std::vector<std::string>{"",
                                                                                        "'{'",
                                                                                        "'}'",
                                                                                        "'materials'",
                                                                                        "'scale'",
                                                                                        "'vertices'",
                                                                                        "'faces'",
                                                                                        "'meta'",
                                                                                        "'object'",
                                                                                        "'v'",
                                                                                        "'uv'",
                                                                                        "'clr'",
                                                                                        "'vn'",
                                                                                        "'texture'",
                                                                                        "'f'",
                                                                                        "'keyword2F'",
                                                                                        "'keyword30'",
                                                                                        "'bone'"},
                                                               std::vector<std::string>{"",
                                                                                        "",
                                                                                        "",
                                                                                        "Materials",
                                                                                        "Scale",
                                                                                        "Vertices",
                                                                                        "Faces",
                                                                                        "Meta",
                                                                                        "Object",
                                                                                        "Vertex",
                                                                                        "Uv",
                                                                                        "Color",
                                                                                        "Normal",
                                                                                        "Texture",
                                                                                        "Face",
                                                                                        "Keyword2F",
                                                                                        "Keyword30",
                                                                                        "Bone",
                                                                                        "IntegerConstant",
                                                                                        "FloatingConstant",
                                                                                        "DigitSequence",
                                                                                        "StringLiteral",
                                                                                        "Whitespace",
                                                                                        "Newline",
                                                                                        "BlockComment",
                                                                                        "LineComment"});
        static const int32_t serializedATNSegment[] = {
            4,   0,   25,  290, 6,   -1, 2,   0,   7,   0,   2,  1,   7,   1,   2,   2,   7,   2,   2,   3,   7,   3,   2,   4,   7,   4,   2,   5,   7,   5,
            2,   6,   7,   6,   2,   7,  7,   7,   2,   8,   7,  8,   2,   9,   7,   9,   2,   10,  7,   10,  2,   11,  7,   11,  2,   12,  7,   12,  2,   13,
            7,   13,  2,   14,  7,   14, 2,   15,  7,   15,  2,  16,  7,   16,  2,   17,  7,   17,  2,   18,  7,   18,  2,   19,  7,   19,  2,   20,  7,   20,
            2,   21,  7,   21,  2,   22, 7,   22,  2,   23,  7,  23,  2,   24,  7,   24,  2,   25,  7,   25,  2,   26,  7,   26,  2,   27,  7,   27,  2,   28,
            7,   28,  2,   29,  7,   29, 2,   30,  7,   30,  2,  31,  7,   31,  2,   32,  7,   32,  2,   33,  7,   33,  2,   34,  7,   34,  2,   35,  7,   35,
            1,   0,   1,   0,   1,   1,  1,   1,   1,   2,   1,  2,   1,   2,   1,   2,   1,   2,   1,   2,   1,   2,   1,   2,   1,   2,   1,   2,   1,   3,
            1,   3,   1,   3,   1,   3,  1,   3,   1,   3,   1,  4,   1,   4,   1,   4,   1,   4,   1,   4,   1,   4,   1,   4,   1,   4,   1,   4,   1,   5,
            1,   5,   1,   5,   1,   5,  1,   5,   1,   5,   1,  6,   1,   6,   1,   6,   1,   6,   1,   6,   1,   7,   1,   7,   1,   7,   1,   7,   1,   7,
            1,   7,   1,   7,   1,   8,  1,   8,   1,   9,   1,  9,   1,   9,   1,   10,  1,   10,  1,   10,  1,   10,  1,   11,  1,   11,  1,   11,  1,   12,
            1,   12,  1,   12,  1,   12, 1,   12,  1,   12,  1,  12,  1,   12,  1,   13,  1,   13,  1,   14,  1,   14,  1,   14,  1,   14,  1,   14,  1,   14,
            1,   14,  1,   14,  1,   14, 1,   14,  1,   15,  1,  15,  1,   15,  1,   15,  1,   15,  1,   15,  1,   15,  1,   15,  1,   15,  1,   15,  1,   16,
            1,   16,  1,   16,  1,   16, 1,   16,  1,   17,  1,  17,  1,   17,  3,   17,  171, 8,   17,  1,   18,  3,   18,  174, 8,   18,  1,   18,  4,   18,
            177, 8,   18,  11,  18,  12, 18,  178, 1,   19,  3,  19,  182, 8,   19,  1,   19,  1,   19,  4,   19,  186, 8,   19,  11,  19,  12,  19,  187, 1,
            20,  1,   20,  1,   20,  1,  21,  3,   21,  194, 8,  21,  1,   21,  3,   21,  197, 8,   21,  1,   21,  1,   21,  1,   21,  3,   21,  202, 8,   21,
            1,   21,  1,   21,  1,   21, 3,   21,  207, 8,   21, 1,   22,  4,   22,  210, 8,   22,  11,  22,  12,  22,  211, 1,   23,  1,   23,  1,   24,  1,
            24,  1,   25,  1,   25,  1,  26,  3,   26,  221, 8,  26,  1,   26,  1,   26,  1,   27,  1,   27,  1,   28,  1,   28,  3,   28,  229, 8,   28,  1,
            28,  1,   28,  1,   29,  4,  29,  234, 8,   29,  11, 29,  12,  29,  235, 1,   30,  1,   30,  1,   30,  1,   30,  1,   30,  1,   30,  1,   30,  3,
            30,  245, 8,   30,  1,   31, 1,   31,  1,   31,  1,  32,  4,   32,  251, 8,   32,  11,  32,  12,  32,  252, 1,   32,  1,   32,  1,   33,  1,   33,
            3,   33,  259, 8,   33,  1,  33,  3,   33,  262, 8,  33,  1,   33,  1,   33,  1,   34,  1,   34,  1,   34,  1,   34,  5,   34,  270, 8,   34,  10,
            34,  12,  34,  273, 9,   34, 1,   34,  1,   34,  1,  34,  1,   34,  1,   34,  1,   35,  1,   35,  1,   35,  1,   35,  5,   35,  284, 8,   35,  10,
            35,  12,  35,  287, 9,   35, 1,   35,  1,   35,  1,  271, 0,   36,  1,   1,   3,   2,   5,   3,   7,   4,   9,   5,   11,  6,   13,  7,   15,  8,
            17,  9,   19,  10,  21,  11, 23,  12,  25,  13,  27, 14,  29,  15,  31,  16,  33,  17,  35,  18,  37,  0,   39,  0,   41,  0,   43,  19,  45,  20,
            47,  0,   49,  0,   51,  0,  53,  0,   55,  0,   57, 21,  59,  0,   61,  0,   63,  0,   65,  22,  67,  23,  69,  24,  71,  25,  1,   0,   9,   2,
            0,   88,  88,  120, 120, 1,  0,   49,  57,  1,   0,  48,  57,  3,   0,   48,  57,  65,  70,  97,  102, 2,   0,   43,  43,  45,  45,  4,   0,   10,
            10,  13,  13,  34,  34,  92, 92,  10,  0,   34,  34, 39,  39,  63,  63,  92,  92,  97,  98,  102, 102, 110, 110, 114, 114, 116, 116, 118, 118, 2,
            0,   9,   9,   32,  32,  2,  0,   10,  10,  13,  13, 300, 0,   1,   1,   0,   0,   0,   0,   3,   1,   0,   0,   0,   0,   5,   1,   0,   0,   0,
            0,   7,   1,   0,   0,   0,  0,   9,   1,   0,   0,  0,   0,   11,  1,   0,   0,   0,   0,   13,  1,   0,   0,   0,   0,   15,  1,   0,   0,   0,
            0,   17,  1,   0,   0,   0,  0,   19,  1,   0,   0,  0,   0,   21,  1,   0,   0,   0,   0,   23,  1,   0,   0,   0,   0,   25,  1,   0,   0,   0,
            0,   27,  1,   0,   0,   0,  0,   29,  1,   0,   0,  0,   0,   31,  1,   0,   0,   0,   0,   33,  1,   0,   0,   0,   0,   35,  1,   0,   0,   0,
            0,   43,  1,   0,   0,   0,  0,   45,  1,   0,   0,  0,   0,   57,  1,   0,   0,   0,   0,   65,  1,   0,   0,   0,   0,   67,  1,   0,   0,   0,
            0,   69,  1,   0,   0,   0,  0,   71,  1,   0,   0,  0,   1,   73,  1,   0,   0,   0,   3,   75,  1,   0,   0,   0,   5,   77,  1,   0,   0,   0,
            7,   87,  1,   0,   0,   0,  9,   93,  1,   0,   0,  0,   11,  102, 1,   0,   0,   0,   13,  108, 1,   0,   0,   0,   15,  113, 1,   0,   0,   0,
            17,  120, 1,   0,   0,   0,  19,  122, 1,   0,   0,  0,   21,  125, 1,   0,   0,   0,   23,  129, 1,   0,   0,   0,   25,  132, 1,   0,   0,   0,
            27,  140, 1,   0,   0,   0,  29,  142, 1,   0,   0,  0,   31,  152, 1,   0,   0,   0,   33,  162, 1,   0,   0,   0,   35,  170, 1,   0,   0,   0,
            37,  173, 1,   0,   0,   0,  39,  181, 1,   0,   0,  0,   41,  189, 1,   0,   0,   0,   43,  206, 1,   0,   0,   0,   45,  209, 1,   0,   0,   0,
            47,  213, 1,   0,   0,   0,  49,  215, 1,   0,   0,  0,   51,  217, 1,   0,   0,   0,   53,  220, 1,   0,   0,   0,   55,  224, 1,   0,   0,   0,
            57,  226, 1,   0,   0,   0,  59,  233, 1,   0,   0,  0,   61,  244, 1,   0,   0,   0,   63,  246, 1,   0,   0,   0,   65,  250, 1,   0,   0,   0,
            67,  261, 1,   0,   0,   0,  69,  265, 1,   0,   0,  0,   71,  279, 1,   0,   0,   0,   73,  74,  5,   123, 0,   0,   74,  2,   1,   0,   0,   0,
            75,  76,  5,   125, 0,   0,  76,  4,   1,   0,   0,  0,   77,  78,  5,   109, 0,   0,   78,  79,  5,   97,  0,   0,   79,  80,  5,   116, 0,   0,
            80,  81,  5,   101, 0,   0,  81,  82,  5,   114, 0,  0,   82,  83,  5,   105, 0,   0,   83,  84,  5,   97,  0,   0,   84,  85,  5,   108, 0,   0,
            85,  86,  5,   115, 0,   0,  86,  6,   1,   0,   0,  0,   87,  88,  5,   115, 0,   0,   88,  89,  5,   99,  0,   0,   89,  90,  5,   97,  0,   0,
            90,  91,  5,   108, 0,   0,  91,  92,  5,   101, 0,  0,   92,  8,   1,   0,   0,   0,   93,  94,  5,   118, 0,   0,   94,  95,  5,   101, 0,   0,
            95,  96,  5,   114, 0,   0,  96,  97,  5,   116, 0,  0,   97,  98,  5,   105, 0,   0,   98,  99,  5,   99,  0,   0,   99,  100, 5,   101, 0,   0,
            100, 101, 5,   115, 0,   0,  101, 10,  1,   0,   0,  0,   102, 103, 5,   102, 0,   0,   103, 104, 5,   97,  0,   0,   104, 105, 5,   99,  0,   0,
            105, 106, 5,   101, 0,   0,  106, 107, 5,   115, 0,  0,   107, 12,  1,   0,   0,   0,   108, 109, 5,   109, 0,   0,   109, 110, 5,   101, 0,   0,
            110, 111, 5,   116, 0,   0,  111, 112, 5,   97,  0,  0,   112, 14,  1,   0,   0,   0,   113, 114, 5,   111, 0,   0,   114, 115, 5,   98,  0,   0,
            115, 116, 5,   106, 0,   0,  116, 117, 5,   101, 0,  0,   117, 118, 5,   99,  0,   0,   118, 119, 5,   116, 0,   0,   119, 16,  1,   0,   0,   0,
            120, 121, 5,   118, 0,   0,  121, 18,  1,   0,   0,  0,   122, 123, 5,   117, 0,   0,   123, 124, 5,   118, 0,   0,   124, 20,  1,   0,   0,   0,
            125, 126, 5,   99,  0,   0,  126, 127, 5,   108, 0,  0,   127, 128, 5,   114, 0,   0,   128, 22,  1,   0,   0,   0,   129, 130, 5,   118, 0,   0,
            130, 131, 5,   110, 0,   0,  131, 24,  1,   0,   0,  0,   132, 133, 5,   116, 0,   0,   133, 134, 5,   101, 0,   0,   134, 135, 5,   120, 0,   0,
            135, 136, 5,   116, 0,   0,  136, 137, 5,   117, 0,  0,   137, 138, 5,   114, 0,   0,   138, 139, 5,   101, 0,   0,   139, 26,  1,   0,   0,   0,
            140, 141, 5,   102, 0,   0,  141, 28,  1,   0,   0,  0,   142, 143, 5,   107, 0,   0,   143, 144, 5,   101, 0,   0,   144, 145, 5,   121, 0,   0,
            145, 146, 5,   119, 0,   0,  146, 147, 5,   111, 0,  0,   147, 148, 5,   114, 0,   0,   148, 149, 5,   100, 0,   0,   149, 150, 5,   50,  0,   0,
            150, 151, 5,   70,  0,   0,  151, 30,  1,   0,   0,  0,   152, 153, 5,   107, 0,   0,   153, 154, 5,   101, 0,   0,   154, 155, 5,   121, 0,   0,
            155, 156, 5,   119, 0,   0,  156, 157, 5,   111, 0,  0,   157, 158, 5,   114, 0,   0,   158, 159, 5,   100, 0,   0,   159, 160, 5,   51,  0,   0,
            160, 161, 5,   48,  0,   0,  161, 32,  1,   0,   0,  0,   162, 163, 5,   98,  0,   0,   163, 164, 5,   111, 0,   0,   164, 165, 5,   110, 0,   0,
            165, 166, 5,   101, 0,   0,  166, 34,  1,   0,   0,  0,   167, 171, 3,   37,  18,  0,   168, 171, 3,   39,  19,  0,   169, 171, 3,   53,  26,  0,
            170, 167, 1,   0,   0,   0,  170, 168, 1,   0,   0,  0,   170, 169, 1,   0,   0,   0,   171, 36,  1,   0,   0,   0,   172, 174, 3,   55,  27,  0,
            173, 172, 1,   0,   0,   0,  173, 174, 1,   0,   0,  0,   174, 176, 1,   0,   0,   0,   175, 177, 3,   49,  24,  0,   176, 175, 1,   0,   0,   0,
            177, 178, 1,   0,   0,   0,  178, 176, 1,   0,   0,  0,   178, 179, 1,   0,   0,   0,   179, 38,  1,   0,   0,   0,   180, 182, 3,   55,  27,  0,
            181, 180, 1,   0,   0,   0,  181, 182, 1,   0,   0,  0,   182, 183, 1,   0,   0,   0,   183, 185, 3,   41,  20,  0,   184, 186, 3,   51,  25,  0,
            185, 184, 1,   0,   0,   0,  186, 187, 1,   0,   0,  0,   187, 185, 1,   0,   0,   0,   187, 188, 1,   0,   0,   0,   188, 40,  1,   0,   0,   0,
            189, 190, 5,   48,  0,   0,  190, 191, 7,   0,   0,  0,   191, 42,  1,   0,   0,   0,   192, 194, 3,   55,  27,  0,   193, 192, 1,   0,   0,   0,
            193, 194, 1,   0,   0,   0,  194, 195, 1,   0,   0,  0,   195, 197, 3,   45,  22,  0,   196, 193, 1,   0,   0,   0,   196, 197, 1,   0,   0,   0,
            197, 198, 1,   0,   0,   0,  198, 199, 5,   46,  0,  0,   199, 207, 3,   45,  22,  0,   200, 202, 3,   55,  27,  0,   201, 200, 1,   0,   0,   0,
            201, 202, 1,   0,   0,   0,  202, 203, 1,   0,   0,  0,   203, 204, 3,   45,  22,  0,   204, 205, 5,   46,  0,   0,   205, 207, 1,   0,   0,   0,
            206, 196, 1,   0,   0,   0,  206, 201, 1,   0,   0,  0,   207, 44,  1,   0,   0,   0,   208, 210, 3,   49,  24,  0,   209, 208, 1,   0,   0,   0,
            210, 211, 1,   0,   0,   0,  211, 209, 1,   0,   0,  0,   211, 212, 1,   0,   0,   0,   212, 46,  1,   0,   0,   0,   213, 214, 7,   1,   0,   0,
            214, 48,  1,   0,   0,   0,  215, 216, 7,   2,   0,  0,   216, 50,  1,   0,   0,   0,   217, 218, 7,   3,   0,   0,   218, 52,  1,   0,   0,   0,
            219, 221, 3,   55,  27,  0,  220, 219, 1,   0,   0,  0,   220, 221, 1,   0,   0,   0,   221, 222, 1,   0,   0,   0,   222, 223, 5,   48,  0,   0,
            223, 54,  1,   0,   0,   0,  224, 225, 7,   4,   0,  0,   225, 56,  1,   0,   0,   0,   226, 228, 5,   34,  0,   0,   227, 229, 3,   59,  29,  0,
            228, 227, 1,   0,   0,   0,  228, 229, 1,   0,   0,  0,   229, 230, 1,   0,   0,   0,   230, 231, 5,   34,  0,   0,   231, 58,  1,   0,   0,   0,
            232, 234, 3,   61,  30,  0,  233, 232, 1,   0,   0,  0,   234, 235, 1,   0,   0,   0,   235, 233, 1,   0,   0,   0,   235, 236, 1,   0,   0,   0,
            236, 60,  1,   0,   0,   0,  237, 245, 8,   5,   0,  0,   238, 245, 3,   63,  31,  0,   239, 240, 5,   92,  0,   0,   240, 245, 5,   10,  0,   0,
            241, 242, 5,   92,  0,   0,  242, 243, 5,   13,  0,  0,   243, 245, 5,   10,  0,   0,   244, 237, 1,   0,   0,   0,   244, 238, 1,   0,   0,   0,
            244, 239, 1,   0,   0,   0,  244, 241, 1,   0,   0,  0,   245, 62,  1,   0,   0,   0,   246, 247, 5,   92,  0,   0,   247, 248, 7,   6,   0,   0,
            248, 64,  1,   0,   0,   0,  249, 251, 7,   7,   0,  0,   250, 249, 1,   0,   0,   0,   251, 252, 1,   0,   0,   0,   252, 250, 1,   0,   0,   0,
            252, 253, 1,   0,   0,   0,  253, 254, 1,   0,   0,  0,   254, 255, 6,   32,  0,   0,   255, 66,  1,   0,   0,   0,   256, 258, 5,   13,  0,   0,
            257, 259, 5,   10,  0,   0,  258, 257, 1,   0,   0,  0,   258, 259, 1,   0,   0,   0,   259, 262, 1,   0,   0,   0,   260, 262, 5,   10,  0,   0,
            261, 256, 1,   0,   0,   0,  261, 260, 1,   0,   0,  0,   262, 263, 1,   0,   0,   0,   263, 264, 6,   33,  0,   0,   264, 68,  1,   0,   0,   0,
            265, 266, 5,   47,  0,   0,  266, 267, 5,   42,  0,  0,   267, 271, 1,   0,   0,   0,   268, 270, 9,   0,   0,   0,   269, 268, 1,   0,   0,   0,
            270, 273, 1,   0,   0,   0,  271, 272, 1,   0,   0,  0,   271, 269, 1,   0,   0,   0,   272, 274, 1,   0,   0,   0,   273, 271, 1,   0,   0,   0,
            274, 275, 5,   42,  0,   0,  275, 276, 5,   47,  0,  0,   276, 277, 1,   0,   0,   0,   277, 278, 6,   34,  0,   0,   278, 70,  1,   0,   0,   0,
            279, 280, 5,   47,  0,   0,  280, 281, 5,   47,  0,  0,   281, 285, 1,   0,   0,   0,   282, 284, 8,   8,   0,   0,   283, 282, 1,   0,   0,   0,
            284, 287, 1,   0,   0,   0,  285, 283, 1,   0,   0,  0,   285, 286, 1,   0,   0,   0,   286, 288, 1,   0,   0,   0,   287, 285, 1,   0,   0,   0,
            288, 289, 6,   35,  0,   0,  289, 72,  1,   0,   0,  0,   20,  0,   170, 173, 178, 181, 187, 193, 196, 201, 206, 211, 220, 228, 235, 244, 252, 258,
            261, 271, 285, 1,   6,   0,  0};
        staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

        antlr4::atn::ATNDeserializer deserializer;
        staticData->atn = deserializer.deserialize(staticData->serializedATN);

        const size_t count = staticData->atn->getNumberOfDecisions();
        staticData->decisionToDFA.reserve(count);
        for (size_t i = 0; i < count; i++)
        {
            staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
        }
        gdblexerLexerStaticData = staticData.release();
    }

} // namespace

GdbLexer::GdbLexer(CharStream* input)
    : Lexer(input)
{
    GdbLexer::initialize();
    _interpreter =
        new atn::LexerATNSimulator(this, *gdblexerLexerStaticData->atn, gdblexerLexerStaticData->decisionToDFA, gdblexerLexerStaticData->sharedContextCache);
}

GdbLexer::~GdbLexer()
{
    delete _interpreter;
}

std::string GdbLexer::getGrammarFileName() const
{
    return "Gdb.g4";
}

const std::vector<std::string>& GdbLexer::getRuleNames() const
{
    return gdblexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& GdbLexer::getChannelNames() const
{
    return gdblexerLexerStaticData->channelNames;
}

const std::vector<std::string>& GdbLexer::getModeNames() const
{
    return gdblexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& GdbLexer::getVocabulary() const
{
    return gdblexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView GdbLexer::getSerializedATN() const
{
    return gdblexerLexerStaticData->serializedATN;
}

const atn::ATN& GdbLexer::getATN() const
{
    return *gdblexerLexerStaticData->atn;
}

void GdbLexer::initialize()
{
    std::call_once(gdblexerLexerOnceFlag, gdblexerLexerInitialize);
}
