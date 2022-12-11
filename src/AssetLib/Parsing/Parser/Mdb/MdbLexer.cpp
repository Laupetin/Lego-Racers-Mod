
// Generated from ..\..\..\src\AssetLib\Parsing\Parser\Mdb\Mdb.g4 by ANTLR 4.10.1


#include "MdbLexer.h"


using namespace antlr4;

using namespace mdb;


using namespace antlr4;

namespace {

struct MdbLexerStaticData final {
  MdbLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  MdbLexerStaticData(const MdbLexerStaticData&) = delete;
  MdbLexerStaticData(MdbLexerStaticData&&) = delete;
  MdbLexerStaticData& operator=(const MdbLexerStaticData&) = delete;
  MdbLexerStaticData& operator=(MdbLexerStaticData&&) = delete;

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

std::once_flag mdblexerLexerOnceFlag;
MdbLexerStaticData *mdblexerLexerStaticData = nullptr;

void mdblexerLexerInitialize() {
  assert(mdblexerLexerStaticData == nullptr);
  auto staticData = std::make_unique<MdbLexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "Materials", "Material", "Color1", "Color0", "Keyword2A", 
      "Keyword2B", "Texture", "Keyword2D", "Keyword2E", "Keyword2F", "Keyword30", 
      "Keyword31", "Keyword32", "Keyword33", "Keyword34", "Keyword35", "Keyword36", 
      "Keyword37", "Keyword38", "Keyword39", "Keyword3A", "Keyword3B", "Keyword3C", 
      "Keyword3D", "Keyword3E", "Keyword3F", "Keyword40", "Keyword41", "Keyword42", 
      "Keyword43", "Keyword44", "Keyword45", "Opacity", "Keyword47", "Keyword48", 
      "Keyword49", "Keyword4A", "Keyword4B", "Keyword4C", "Keyword4D", "Keyword4E", 
      "Keyword4F", "Keyword50", "IntegerConstant", "DecimalConstant", "HexadecimalConstant", 
      "HexadecimalPrefix", "FloatingConstant", "DigitSequence", "NonzeroDigit", 
      "Digit", "HexadecimalDigit", "Zero", "IntegerSign", "StringLiteral", 
      "SCharSequence", "SChar", "EscapeSequence", "Whitespace", "Newline", 
      "BlockComment", "LineComment"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'{'", "'}'", "'materials'", "'material'", "'color1'", "'color0'", 
      "'keyword2A'", "'keyword2B'", "'texture'", "'keyword2D'", "'keyword2E'", 
      "'keyword2F'", "'keyword30'", "'keyword31'", "'keyword32'", "'keyword33'", 
      "'keyword34'", "'keyword35'", "'keyword36'", "'keyword37'", "'keyword38'", 
      "'keyword39'", "'keyword3A'", "'keyword3B'", "'keyword3C'", "'keyword3D'", 
      "'keyword3E'", "'keyword3F'", "'keyword40'", "'keyword41'", "'keyword42'", 
      "'keyword43'", "'keyword44'", "'keyword45'", "'opacity'", "'keyword47'", 
      "'keyword48'", "'keyword49'", "'keyword4A'", "'keyword4B'", "'keyword4C'", 
      "'keyword4D'", "'keyword4E'", "'keyword4F'", "'keyword50'"
    },
    std::vector<std::string>{
      "", "", "", "Materials", "Material", "Color1", "Color0", "Keyword2A", 
      "Keyword2B", "Texture", "Keyword2D", "Keyword2E", "Keyword2F", "Keyword30", 
      "Keyword31", "Keyword32", "Keyword33", "Keyword34", "Keyword35", "Keyword36", 
      "Keyword37", "Keyword38", "Keyword39", "Keyword3A", "Keyword3B", "Keyword3C", 
      "Keyword3D", "Keyword3E", "Keyword3F", "Keyword40", "Keyword41", "Keyword42", 
      "Keyword43", "Keyword44", "Keyword45", "Opacity", "Keyword47", "Keyword48", 
      "Keyword49", "Keyword4A", "Keyword4B", "Keyword4C", "Keyword4D", "Keyword4E", 
      "Keyword4F", "Keyword50", "IntegerConstant", "FloatingConstant", "DigitSequence", 
      "StringLiteral", "Whitespace", "Newline", "BlockComment", "LineComment"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,53,675,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,
  	7,35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,
  	7,42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,
  	7,49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,
  	7,56,2,57,7,57,2,58,7,58,2,59,7,59,2,60,7,60,2,61,7,61,2,62,7,62,2,63,
  	7,63,1,0,1,0,1,1,1,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,3,1,3,
  	1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,5,1,5,1,5,1,
  	5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,7,1,7,1,7,1,7,
  	1,7,1,7,1,7,1,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,9,1,9,1,9,1,
  	9,1,9,1,9,1,9,1,9,1,9,1,9,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,
  	1,10,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,12,1,12,1,12,
  	1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,13,1,13,1,13,1,13,1,13,1,13,1,13,
  	1,13,1,13,1,13,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,15,
  	1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,16,1,16,1,16,1,16,1,16,
  	1,16,1,16,1,16,1,16,1,16,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,
  	1,17,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,19,1,19,1,19,
  	1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,20,1,20,1,20,1,20,1,20,1,20,1,20,
  	1,20,1,20,1,20,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,22,
  	1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,23,1,23,1,23,1,23,1,23,
  	1,23,1,23,1,23,1,23,1,23,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,
  	1,24,1,25,1,25,1,25,1,25,1,25,1,25,1,25,1,25,1,25,1,25,1,26,1,26,1,26,
  	1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,27,1,27,1,27,1,27,1,27,1,27,1,27,
  	1,27,1,27,1,27,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,29,
  	1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,30,1,30,1,30,1,30,1,30,
  	1,30,1,30,1,30,1,30,1,30,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,
  	1,31,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,33,1,33,1,33,
  	1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,34,1,34,1,34,1,34,1,34,1,34,1,34,
  	1,34,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,36,1,36,1,36,
  	1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,37,1,37,1,37,1,37,1,37,1,37,1,37,
  	1,37,1,37,1,37,1,38,1,38,1,38,1,38,1,38,1,38,1,38,1,38,1,38,1,38,1,39,
  	1,39,1,39,1,39,1,39,1,39,1,39,1,39,1,39,1,39,1,40,1,40,1,40,1,40,1,40,
  	1,40,1,40,1,40,1,40,1,40,1,41,1,41,1,41,1,41,1,41,1,41,1,41,1,41,1,41,
  	1,41,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,43,1,43,1,43,
  	1,43,1,43,1,43,1,43,1,43,1,43,1,43,1,44,1,44,1,44,1,44,1,44,1,44,1,44,
  	1,44,1,44,1,44,1,45,1,45,1,45,3,45,556,8,45,1,46,3,46,559,8,46,1,46,4,
  	46,562,8,46,11,46,12,46,563,1,47,3,47,567,8,47,1,47,1,47,4,47,571,8,47,
  	11,47,12,47,572,1,48,1,48,1,48,1,49,3,49,579,8,49,1,49,3,49,582,8,49,
  	1,49,1,49,1,49,3,49,587,8,49,1,49,1,49,1,49,3,49,592,8,49,1,50,4,50,595,
  	8,50,11,50,12,50,596,1,51,1,51,1,52,1,52,1,53,1,53,1,54,3,54,606,8,54,
  	1,54,1,54,1,55,1,55,1,56,1,56,3,56,614,8,56,1,56,1,56,1,57,4,57,619,8,
  	57,11,57,12,57,620,1,58,1,58,1,58,1,58,1,58,1,58,1,58,3,58,630,8,58,1,
  	59,1,59,1,59,1,60,4,60,636,8,60,11,60,12,60,637,1,60,1,60,1,61,1,61,3,
  	61,644,8,61,1,61,3,61,647,8,61,1,61,1,61,1,62,1,62,1,62,1,62,5,62,655,
  	8,62,10,62,12,62,658,9,62,1,62,1,62,1,62,1,62,1,62,1,63,1,63,1,63,1,63,
  	5,63,669,8,63,10,63,12,63,672,9,63,1,63,1,63,1,656,0,64,1,1,3,2,5,3,7,
  	4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,14,29,15,31,16,33,
  	17,35,18,37,19,39,20,41,21,43,22,45,23,47,24,49,25,51,26,53,27,55,28,
  	57,29,59,30,61,31,63,32,65,33,67,34,69,35,71,36,73,37,75,38,77,39,79,
  	40,81,41,83,42,85,43,87,44,89,45,91,46,93,0,95,0,97,0,99,47,101,48,103,
  	0,105,0,107,0,109,0,111,0,113,49,115,0,117,0,119,0,121,50,123,51,125,
  	52,127,53,1,0,9,2,0,88,88,120,120,1,0,49,57,1,0,48,57,3,0,48,57,65,70,
  	97,102,2,0,43,43,45,45,4,0,10,10,13,13,34,34,92,92,10,0,34,34,39,39,63,
  	63,92,92,97,98,102,102,110,110,114,114,116,116,118,118,2,0,9,9,32,32,
  	2,0,10,10,13,13,685,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,
  	9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,
  	0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,
  	0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,0,0,
  	41,1,0,0,0,0,43,1,0,0,0,0,45,1,0,0,0,0,47,1,0,0,0,0,49,1,0,0,0,0,51,1,
  	0,0,0,0,53,1,0,0,0,0,55,1,0,0,0,0,57,1,0,0,0,0,59,1,0,0,0,0,61,1,0,0,
  	0,0,63,1,0,0,0,0,65,1,0,0,0,0,67,1,0,0,0,0,69,1,0,0,0,0,71,1,0,0,0,0,
  	73,1,0,0,0,0,75,1,0,0,0,0,77,1,0,0,0,0,79,1,0,0,0,0,81,1,0,0,0,0,83,1,
  	0,0,0,0,85,1,0,0,0,0,87,1,0,0,0,0,89,1,0,0,0,0,91,1,0,0,0,0,99,1,0,0,
  	0,0,101,1,0,0,0,0,113,1,0,0,0,0,121,1,0,0,0,0,123,1,0,0,0,0,125,1,0,0,
  	0,0,127,1,0,0,0,1,129,1,0,0,0,3,131,1,0,0,0,5,133,1,0,0,0,7,143,1,0,0,
  	0,9,152,1,0,0,0,11,159,1,0,0,0,13,166,1,0,0,0,15,176,1,0,0,0,17,186,1,
  	0,0,0,19,194,1,0,0,0,21,204,1,0,0,0,23,214,1,0,0,0,25,224,1,0,0,0,27,
  	234,1,0,0,0,29,244,1,0,0,0,31,254,1,0,0,0,33,264,1,0,0,0,35,274,1,0,0,
  	0,37,284,1,0,0,0,39,294,1,0,0,0,41,304,1,0,0,0,43,314,1,0,0,0,45,324,
  	1,0,0,0,47,334,1,0,0,0,49,344,1,0,0,0,51,354,1,0,0,0,53,364,1,0,0,0,55,
  	374,1,0,0,0,57,384,1,0,0,0,59,394,1,0,0,0,61,404,1,0,0,0,63,414,1,0,0,
  	0,65,424,1,0,0,0,67,434,1,0,0,0,69,444,1,0,0,0,71,452,1,0,0,0,73,462,
  	1,0,0,0,75,472,1,0,0,0,77,482,1,0,0,0,79,492,1,0,0,0,81,502,1,0,0,0,83,
  	512,1,0,0,0,85,522,1,0,0,0,87,532,1,0,0,0,89,542,1,0,0,0,91,555,1,0,0,
  	0,93,558,1,0,0,0,95,566,1,0,0,0,97,574,1,0,0,0,99,591,1,0,0,0,101,594,
  	1,0,0,0,103,598,1,0,0,0,105,600,1,0,0,0,107,602,1,0,0,0,109,605,1,0,0,
  	0,111,609,1,0,0,0,113,611,1,0,0,0,115,618,1,0,0,0,117,629,1,0,0,0,119,
  	631,1,0,0,0,121,635,1,0,0,0,123,646,1,0,0,0,125,650,1,0,0,0,127,664,1,
  	0,0,0,129,130,5,123,0,0,130,2,1,0,0,0,131,132,5,125,0,0,132,4,1,0,0,0,
  	133,134,5,109,0,0,134,135,5,97,0,0,135,136,5,116,0,0,136,137,5,101,0,
  	0,137,138,5,114,0,0,138,139,5,105,0,0,139,140,5,97,0,0,140,141,5,108,
  	0,0,141,142,5,115,0,0,142,6,1,0,0,0,143,144,5,109,0,0,144,145,5,97,0,
  	0,145,146,5,116,0,0,146,147,5,101,0,0,147,148,5,114,0,0,148,149,5,105,
  	0,0,149,150,5,97,0,0,150,151,5,108,0,0,151,8,1,0,0,0,152,153,5,99,0,0,
  	153,154,5,111,0,0,154,155,5,108,0,0,155,156,5,111,0,0,156,157,5,114,0,
  	0,157,158,5,49,0,0,158,10,1,0,0,0,159,160,5,99,0,0,160,161,5,111,0,0,
  	161,162,5,108,0,0,162,163,5,111,0,0,163,164,5,114,0,0,164,165,5,48,0,
  	0,165,12,1,0,0,0,166,167,5,107,0,0,167,168,5,101,0,0,168,169,5,121,0,
  	0,169,170,5,119,0,0,170,171,5,111,0,0,171,172,5,114,0,0,172,173,5,100,
  	0,0,173,174,5,50,0,0,174,175,5,65,0,0,175,14,1,0,0,0,176,177,5,107,0,
  	0,177,178,5,101,0,0,178,179,5,121,0,0,179,180,5,119,0,0,180,181,5,111,
  	0,0,181,182,5,114,0,0,182,183,5,100,0,0,183,184,5,50,0,0,184,185,5,66,
  	0,0,185,16,1,0,0,0,186,187,5,116,0,0,187,188,5,101,0,0,188,189,5,120,
  	0,0,189,190,5,116,0,0,190,191,5,117,0,0,191,192,5,114,0,0,192,193,5,101,
  	0,0,193,18,1,0,0,0,194,195,5,107,0,0,195,196,5,101,0,0,196,197,5,121,
  	0,0,197,198,5,119,0,0,198,199,5,111,0,0,199,200,5,114,0,0,200,201,5,100,
  	0,0,201,202,5,50,0,0,202,203,5,68,0,0,203,20,1,0,0,0,204,205,5,107,0,
  	0,205,206,5,101,0,0,206,207,5,121,0,0,207,208,5,119,0,0,208,209,5,111,
  	0,0,209,210,5,114,0,0,210,211,5,100,0,0,211,212,5,50,0,0,212,213,5,69,
  	0,0,213,22,1,0,0,0,214,215,5,107,0,0,215,216,5,101,0,0,216,217,5,121,
  	0,0,217,218,5,119,0,0,218,219,5,111,0,0,219,220,5,114,0,0,220,221,5,100,
  	0,0,221,222,5,50,0,0,222,223,5,70,0,0,223,24,1,0,0,0,224,225,5,107,0,
  	0,225,226,5,101,0,0,226,227,5,121,0,0,227,228,5,119,0,0,228,229,5,111,
  	0,0,229,230,5,114,0,0,230,231,5,100,0,0,231,232,5,51,0,0,232,233,5,48,
  	0,0,233,26,1,0,0,0,234,235,5,107,0,0,235,236,5,101,0,0,236,237,5,121,
  	0,0,237,238,5,119,0,0,238,239,5,111,0,0,239,240,5,114,0,0,240,241,5,100,
  	0,0,241,242,5,51,0,0,242,243,5,49,0,0,243,28,1,0,0,0,244,245,5,107,0,
  	0,245,246,5,101,0,0,246,247,5,121,0,0,247,248,5,119,0,0,248,249,5,111,
  	0,0,249,250,5,114,0,0,250,251,5,100,0,0,251,252,5,51,0,0,252,253,5,50,
  	0,0,253,30,1,0,0,0,254,255,5,107,0,0,255,256,5,101,0,0,256,257,5,121,
  	0,0,257,258,5,119,0,0,258,259,5,111,0,0,259,260,5,114,0,0,260,261,5,100,
  	0,0,261,262,5,51,0,0,262,263,5,51,0,0,263,32,1,0,0,0,264,265,5,107,0,
  	0,265,266,5,101,0,0,266,267,5,121,0,0,267,268,5,119,0,0,268,269,5,111,
  	0,0,269,270,5,114,0,0,270,271,5,100,0,0,271,272,5,51,0,0,272,273,5,52,
  	0,0,273,34,1,0,0,0,274,275,5,107,0,0,275,276,5,101,0,0,276,277,5,121,
  	0,0,277,278,5,119,0,0,278,279,5,111,0,0,279,280,5,114,0,0,280,281,5,100,
  	0,0,281,282,5,51,0,0,282,283,5,53,0,0,283,36,1,0,0,0,284,285,5,107,0,
  	0,285,286,5,101,0,0,286,287,5,121,0,0,287,288,5,119,0,0,288,289,5,111,
  	0,0,289,290,5,114,0,0,290,291,5,100,0,0,291,292,5,51,0,0,292,293,5,54,
  	0,0,293,38,1,0,0,0,294,295,5,107,0,0,295,296,5,101,0,0,296,297,5,121,
  	0,0,297,298,5,119,0,0,298,299,5,111,0,0,299,300,5,114,0,0,300,301,5,100,
  	0,0,301,302,5,51,0,0,302,303,5,55,0,0,303,40,1,0,0,0,304,305,5,107,0,
  	0,305,306,5,101,0,0,306,307,5,121,0,0,307,308,5,119,0,0,308,309,5,111,
  	0,0,309,310,5,114,0,0,310,311,5,100,0,0,311,312,5,51,0,0,312,313,5,56,
  	0,0,313,42,1,0,0,0,314,315,5,107,0,0,315,316,5,101,0,0,316,317,5,121,
  	0,0,317,318,5,119,0,0,318,319,5,111,0,0,319,320,5,114,0,0,320,321,5,100,
  	0,0,321,322,5,51,0,0,322,323,5,57,0,0,323,44,1,0,0,0,324,325,5,107,0,
  	0,325,326,5,101,0,0,326,327,5,121,0,0,327,328,5,119,0,0,328,329,5,111,
  	0,0,329,330,5,114,0,0,330,331,5,100,0,0,331,332,5,51,0,0,332,333,5,65,
  	0,0,333,46,1,0,0,0,334,335,5,107,0,0,335,336,5,101,0,0,336,337,5,121,
  	0,0,337,338,5,119,0,0,338,339,5,111,0,0,339,340,5,114,0,0,340,341,5,100,
  	0,0,341,342,5,51,0,0,342,343,5,66,0,0,343,48,1,0,0,0,344,345,5,107,0,
  	0,345,346,5,101,0,0,346,347,5,121,0,0,347,348,5,119,0,0,348,349,5,111,
  	0,0,349,350,5,114,0,0,350,351,5,100,0,0,351,352,5,51,0,0,352,353,5,67,
  	0,0,353,50,1,0,0,0,354,355,5,107,0,0,355,356,5,101,0,0,356,357,5,121,
  	0,0,357,358,5,119,0,0,358,359,5,111,0,0,359,360,5,114,0,0,360,361,5,100,
  	0,0,361,362,5,51,0,0,362,363,5,68,0,0,363,52,1,0,0,0,364,365,5,107,0,
  	0,365,366,5,101,0,0,366,367,5,121,0,0,367,368,5,119,0,0,368,369,5,111,
  	0,0,369,370,5,114,0,0,370,371,5,100,0,0,371,372,5,51,0,0,372,373,5,69,
  	0,0,373,54,1,0,0,0,374,375,5,107,0,0,375,376,5,101,0,0,376,377,5,121,
  	0,0,377,378,5,119,0,0,378,379,5,111,0,0,379,380,5,114,0,0,380,381,5,100,
  	0,0,381,382,5,51,0,0,382,383,5,70,0,0,383,56,1,0,0,0,384,385,5,107,0,
  	0,385,386,5,101,0,0,386,387,5,121,0,0,387,388,5,119,0,0,388,389,5,111,
  	0,0,389,390,5,114,0,0,390,391,5,100,0,0,391,392,5,52,0,0,392,393,5,48,
  	0,0,393,58,1,0,0,0,394,395,5,107,0,0,395,396,5,101,0,0,396,397,5,121,
  	0,0,397,398,5,119,0,0,398,399,5,111,0,0,399,400,5,114,0,0,400,401,5,100,
  	0,0,401,402,5,52,0,0,402,403,5,49,0,0,403,60,1,0,0,0,404,405,5,107,0,
  	0,405,406,5,101,0,0,406,407,5,121,0,0,407,408,5,119,0,0,408,409,5,111,
  	0,0,409,410,5,114,0,0,410,411,5,100,0,0,411,412,5,52,0,0,412,413,5,50,
  	0,0,413,62,1,0,0,0,414,415,5,107,0,0,415,416,5,101,0,0,416,417,5,121,
  	0,0,417,418,5,119,0,0,418,419,5,111,0,0,419,420,5,114,0,0,420,421,5,100,
  	0,0,421,422,5,52,0,0,422,423,5,51,0,0,423,64,1,0,0,0,424,425,5,107,0,
  	0,425,426,5,101,0,0,426,427,5,121,0,0,427,428,5,119,0,0,428,429,5,111,
  	0,0,429,430,5,114,0,0,430,431,5,100,0,0,431,432,5,52,0,0,432,433,5,52,
  	0,0,433,66,1,0,0,0,434,435,5,107,0,0,435,436,5,101,0,0,436,437,5,121,
  	0,0,437,438,5,119,0,0,438,439,5,111,0,0,439,440,5,114,0,0,440,441,5,100,
  	0,0,441,442,5,52,0,0,442,443,5,53,0,0,443,68,1,0,0,0,444,445,5,111,0,
  	0,445,446,5,112,0,0,446,447,5,97,0,0,447,448,5,99,0,0,448,449,5,105,0,
  	0,449,450,5,116,0,0,450,451,5,121,0,0,451,70,1,0,0,0,452,453,5,107,0,
  	0,453,454,5,101,0,0,454,455,5,121,0,0,455,456,5,119,0,0,456,457,5,111,
  	0,0,457,458,5,114,0,0,458,459,5,100,0,0,459,460,5,52,0,0,460,461,5,55,
  	0,0,461,72,1,0,0,0,462,463,5,107,0,0,463,464,5,101,0,0,464,465,5,121,
  	0,0,465,466,5,119,0,0,466,467,5,111,0,0,467,468,5,114,0,0,468,469,5,100,
  	0,0,469,470,5,52,0,0,470,471,5,56,0,0,471,74,1,0,0,0,472,473,5,107,0,
  	0,473,474,5,101,0,0,474,475,5,121,0,0,475,476,5,119,0,0,476,477,5,111,
  	0,0,477,478,5,114,0,0,478,479,5,100,0,0,479,480,5,52,0,0,480,481,5,57,
  	0,0,481,76,1,0,0,0,482,483,5,107,0,0,483,484,5,101,0,0,484,485,5,121,
  	0,0,485,486,5,119,0,0,486,487,5,111,0,0,487,488,5,114,0,0,488,489,5,100,
  	0,0,489,490,5,52,0,0,490,491,5,65,0,0,491,78,1,0,0,0,492,493,5,107,0,
  	0,493,494,5,101,0,0,494,495,5,121,0,0,495,496,5,119,0,0,496,497,5,111,
  	0,0,497,498,5,114,0,0,498,499,5,100,0,0,499,500,5,52,0,0,500,501,5,66,
  	0,0,501,80,1,0,0,0,502,503,5,107,0,0,503,504,5,101,0,0,504,505,5,121,
  	0,0,505,506,5,119,0,0,506,507,5,111,0,0,507,508,5,114,0,0,508,509,5,100,
  	0,0,509,510,5,52,0,0,510,511,5,67,0,0,511,82,1,0,0,0,512,513,5,107,0,
  	0,513,514,5,101,0,0,514,515,5,121,0,0,515,516,5,119,0,0,516,517,5,111,
  	0,0,517,518,5,114,0,0,518,519,5,100,0,0,519,520,5,52,0,0,520,521,5,68,
  	0,0,521,84,1,0,0,0,522,523,5,107,0,0,523,524,5,101,0,0,524,525,5,121,
  	0,0,525,526,5,119,0,0,526,527,5,111,0,0,527,528,5,114,0,0,528,529,5,100,
  	0,0,529,530,5,52,0,0,530,531,5,69,0,0,531,86,1,0,0,0,532,533,5,107,0,
  	0,533,534,5,101,0,0,534,535,5,121,0,0,535,536,5,119,0,0,536,537,5,111,
  	0,0,537,538,5,114,0,0,538,539,5,100,0,0,539,540,5,52,0,0,540,541,5,70,
  	0,0,541,88,1,0,0,0,542,543,5,107,0,0,543,544,5,101,0,0,544,545,5,121,
  	0,0,545,546,5,119,0,0,546,547,5,111,0,0,547,548,5,114,0,0,548,549,5,100,
  	0,0,549,550,5,53,0,0,550,551,5,48,0,0,551,90,1,0,0,0,552,556,3,93,46,
  	0,553,556,3,95,47,0,554,556,3,109,54,0,555,552,1,0,0,0,555,553,1,0,0,
  	0,555,554,1,0,0,0,556,92,1,0,0,0,557,559,3,111,55,0,558,557,1,0,0,0,558,
  	559,1,0,0,0,559,561,1,0,0,0,560,562,3,105,52,0,561,560,1,0,0,0,562,563,
  	1,0,0,0,563,561,1,0,0,0,563,564,1,0,0,0,564,94,1,0,0,0,565,567,3,111,
  	55,0,566,565,1,0,0,0,566,567,1,0,0,0,567,568,1,0,0,0,568,570,3,97,48,
  	0,569,571,3,107,53,0,570,569,1,0,0,0,571,572,1,0,0,0,572,570,1,0,0,0,
  	572,573,1,0,0,0,573,96,1,0,0,0,574,575,5,48,0,0,575,576,7,0,0,0,576,98,
  	1,0,0,0,577,579,3,111,55,0,578,577,1,0,0,0,578,579,1,0,0,0,579,580,1,
  	0,0,0,580,582,3,101,50,0,581,578,1,0,0,0,581,582,1,0,0,0,582,583,1,0,
  	0,0,583,584,5,46,0,0,584,592,3,101,50,0,585,587,3,111,55,0,586,585,1,
  	0,0,0,586,587,1,0,0,0,587,588,1,0,0,0,588,589,3,101,50,0,589,590,5,46,
  	0,0,590,592,1,0,0,0,591,581,1,0,0,0,591,586,1,0,0,0,592,100,1,0,0,0,593,
  	595,3,105,52,0,594,593,1,0,0,0,595,596,1,0,0,0,596,594,1,0,0,0,596,597,
  	1,0,0,0,597,102,1,0,0,0,598,599,7,1,0,0,599,104,1,0,0,0,600,601,7,2,0,
  	0,601,106,1,0,0,0,602,603,7,3,0,0,603,108,1,0,0,0,604,606,3,111,55,0,
  	605,604,1,0,0,0,605,606,1,0,0,0,606,607,1,0,0,0,607,608,5,48,0,0,608,
  	110,1,0,0,0,609,610,7,4,0,0,610,112,1,0,0,0,611,613,5,34,0,0,612,614,
  	3,115,57,0,613,612,1,0,0,0,613,614,1,0,0,0,614,615,1,0,0,0,615,616,5,
  	34,0,0,616,114,1,0,0,0,617,619,3,117,58,0,618,617,1,0,0,0,619,620,1,0,
  	0,0,620,618,1,0,0,0,620,621,1,0,0,0,621,116,1,0,0,0,622,630,8,5,0,0,623,
  	630,3,119,59,0,624,625,5,92,0,0,625,630,5,10,0,0,626,627,5,92,0,0,627,
  	628,5,13,0,0,628,630,5,10,0,0,629,622,1,0,0,0,629,623,1,0,0,0,629,624,
  	1,0,0,0,629,626,1,0,0,0,630,118,1,0,0,0,631,632,5,92,0,0,632,633,7,6,
  	0,0,633,120,1,0,0,0,634,636,7,7,0,0,635,634,1,0,0,0,636,637,1,0,0,0,637,
  	635,1,0,0,0,637,638,1,0,0,0,638,639,1,0,0,0,639,640,6,60,0,0,640,122,
  	1,0,0,0,641,643,5,13,0,0,642,644,5,10,0,0,643,642,1,0,0,0,643,644,1,0,
  	0,0,644,647,1,0,0,0,645,647,5,10,0,0,646,641,1,0,0,0,646,645,1,0,0,0,
  	647,648,1,0,0,0,648,649,6,61,0,0,649,124,1,0,0,0,650,651,5,47,0,0,651,
  	652,5,42,0,0,652,656,1,0,0,0,653,655,9,0,0,0,654,653,1,0,0,0,655,658,
  	1,0,0,0,656,657,1,0,0,0,656,654,1,0,0,0,657,659,1,0,0,0,658,656,1,0,0,
  	0,659,660,5,42,0,0,660,661,5,47,0,0,661,662,1,0,0,0,662,663,6,62,0,0,
  	663,126,1,0,0,0,664,665,5,47,0,0,665,666,5,47,0,0,666,670,1,0,0,0,667,
  	669,8,8,0,0,668,667,1,0,0,0,669,672,1,0,0,0,670,668,1,0,0,0,670,671,1,
  	0,0,0,671,673,1,0,0,0,672,670,1,0,0,0,673,674,6,63,0,0,674,128,1,0,0,
  	0,20,0,555,558,563,566,572,578,581,586,591,596,605,613,620,629,637,643,
  	646,656,670,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  mdblexerLexerStaticData = staticData.release();
}

}

MdbLexer::MdbLexer(CharStream *input) : Lexer(input) {
  MdbLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *mdblexerLexerStaticData->atn, mdblexerLexerStaticData->decisionToDFA, mdblexerLexerStaticData->sharedContextCache);
}

MdbLexer::~MdbLexer() {
  delete _interpreter;
}

std::string MdbLexer::getGrammarFileName() const {
  return "Mdb.g4";
}

const std::vector<std::string>& MdbLexer::getRuleNames() const {
  return mdblexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& MdbLexer::getChannelNames() const {
  return mdblexerLexerStaticData->channelNames;
}

const std::vector<std::string>& MdbLexer::getModeNames() const {
  return mdblexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& MdbLexer::getVocabulary() const {
  return mdblexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView MdbLexer::getSerializedATN() const {
  return mdblexerLexerStaticData->serializedATN;
}

const atn::ATN& MdbLexer::getATN() const {
  return *mdblexerLexerStaticData->atn;
}




void MdbLexer::initialize() {
  std::call_once(mdblexerLexerOnceFlag, mdblexerLexerInitialize);
}
