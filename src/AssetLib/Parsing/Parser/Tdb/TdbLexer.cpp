
// Generated from ..\..\..\src\AssetLib\Parsing\Parser\Tdb\Tdb.g4 by ANTLR 4.10.1


#include "TdbLexer.h"


using namespace antlr4;

using namespace tdb;


using namespace antlr4;

namespace {

struct TdbLexerStaticData final {
  TdbLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  TdbLexerStaticData(const TdbLexerStaticData&) = delete;
  TdbLexerStaticData(TdbLexerStaticData&&) = delete;
  TdbLexerStaticData& operator=(const TdbLexerStaticData&) = delete;
  TdbLexerStaticData& operator=(TdbLexerStaticData&&) = delete;

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

std::once_flag tdblexerLexerOnceFlag;
TdbLexerStaticData *tdblexerLexerStaticData = nullptr;

void tdblexerLexerInitialize() {
  assert(tdblexerLexerStaticData == nullptr);
  auto staticData = std::make_unique<TdbLexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "Textures", "Texture", "FlipVertically", "Keyword29", 
      "Bmp", "Tga", "ChromaKey", "Keyword2D", "Keyword2E", "IntegerConstant", 
      "DecimalConstant", "HexadecimalConstant", "HexadecimalPrefix", "FloatingConstant", 
      "DigitSequence", "NonzeroDigit", "Digit", "HexadecimalDigit", "Zero", 
      "IntegerSign", "StringLiteral", "SCharSequence", "SChar", "EscapeSequence", 
      "Whitespace", "Newline", "BlockComment", "LineComment"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'{'", "'}'", "'textures'", "'texture'", "'flipVertically'", "'keyword29'", 
      "'bmp'", "'tga'", "'chromaKey'", "'keyword2D'", "'keyword2E'"
    },
    std::vector<std::string>{
      "", "", "", "Textures", "Texture", "FlipVertically", "Keyword29", 
      "Bmp", "Tga", "ChromaKey", "Keyword2D", "Keyword2E", "IntegerConstant", 
      "FloatingConstant", "DigitSequence", "StringLiteral", "Whitespace", 
      "Newline", "BlockComment", "LineComment"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,19,268,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,1,0,1,0,1,1,1,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,
  	3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,
  	1,4,1,4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,6,1,6,1,
  	6,1,6,1,7,1,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,9,1,9,
  	1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,
  	10,1,10,1,10,1,11,1,11,1,11,3,11,149,8,11,1,12,3,12,152,8,12,1,12,4,12,
  	155,8,12,11,12,12,12,156,1,13,3,13,160,8,13,1,13,1,13,4,13,164,8,13,11,
  	13,12,13,165,1,14,1,14,1,14,1,15,3,15,172,8,15,1,15,3,15,175,8,15,1,15,
  	1,15,1,15,3,15,180,8,15,1,15,1,15,1,15,3,15,185,8,15,1,16,4,16,188,8,
  	16,11,16,12,16,189,1,17,1,17,1,18,1,18,1,19,1,19,1,20,3,20,199,8,20,1,
  	20,1,20,1,21,1,21,1,22,1,22,3,22,207,8,22,1,22,1,22,1,23,4,23,212,8,23,
  	11,23,12,23,213,1,24,1,24,1,24,1,24,1,24,1,24,1,24,3,24,223,8,24,1,25,
  	1,25,1,25,1,26,4,26,229,8,26,11,26,12,26,230,1,26,1,26,1,27,1,27,3,27,
  	237,8,27,1,27,3,27,240,8,27,1,27,1,27,1,28,1,28,1,28,1,28,5,28,248,8,
  	28,10,28,12,28,251,9,28,1,28,1,28,1,28,1,28,1,28,1,29,1,29,1,29,1,29,
  	5,29,262,8,29,10,29,12,29,265,9,29,1,29,1,29,1,249,0,30,1,1,3,2,5,3,7,
  	4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,0,27,0,29,0,31,13,33,14,
  	35,0,37,0,39,0,41,0,43,0,45,15,47,0,49,0,51,0,53,16,55,17,57,18,59,19,
  	1,0,9,2,0,88,88,120,120,1,0,49,57,1,0,48,57,3,0,48,57,65,70,97,102,2,
  	0,43,43,45,45,4,0,10,10,13,13,34,34,92,92,10,0,34,34,39,39,63,63,92,92,
  	97,98,102,102,110,110,114,114,116,116,118,118,2,0,9,9,32,32,2,0,10,10,
  	13,13,278,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,
  	0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,
  	1,0,0,0,0,23,1,0,0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,45,1,0,0,0,0,53,1,0,
  	0,0,0,55,1,0,0,0,0,57,1,0,0,0,0,59,1,0,0,0,1,61,1,0,0,0,3,63,1,0,0,0,
  	5,65,1,0,0,0,7,74,1,0,0,0,9,82,1,0,0,0,11,97,1,0,0,0,13,107,1,0,0,0,15,
  	111,1,0,0,0,17,115,1,0,0,0,19,125,1,0,0,0,21,135,1,0,0,0,23,148,1,0,0,
  	0,25,151,1,0,0,0,27,159,1,0,0,0,29,167,1,0,0,0,31,184,1,0,0,0,33,187,
  	1,0,0,0,35,191,1,0,0,0,37,193,1,0,0,0,39,195,1,0,0,0,41,198,1,0,0,0,43,
  	202,1,0,0,0,45,204,1,0,0,0,47,211,1,0,0,0,49,222,1,0,0,0,51,224,1,0,0,
  	0,53,228,1,0,0,0,55,239,1,0,0,0,57,243,1,0,0,0,59,257,1,0,0,0,61,62,5,
  	123,0,0,62,2,1,0,0,0,63,64,5,125,0,0,64,4,1,0,0,0,65,66,5,116,0,0,66,
  	67,5,101,0,0,67,68,5,120,0,0,68,69,5,116,0,0,69,70,5,117,0,0,70,71,5,
  	114,0,0,71,72,5,101,0,0,72,73,5,115,0,0,73,6,1,0,0,0,74,75,5,116,0,0,
  	75,76,5,101,0,0,76,77,5,120,0,0,77,78,5,116,0,0,78,79,5,117,0,0,79,80,
  	5,114,0,0,80,81,5,101,0,0,81,8,1,0,0,0,82,83,5,102,0,0,83,84,5,108,0,
  	0,84,85,5,105,0,0,85,86,5,112,0,0,86,87,5,86,0,0,87,88,5,101,0,0,88,89,
  	5,114,0,0,89,90,5,116,0,0,90,91,5,105,0,0,91,92,5,99,0,0,92,93,5,97,0,
  	0,93,94,5,108,0,0,94,95,5,108,0,0,95,96,5,121,0,0,96,10,1,0,0,0,97,98,
  	5,107,0,0,98,99,5,101,0,0,99,100,5,121,0,0,100,101,5,119,0,0,101,102,
  	5,111,0,0,102,103,5,114,0,0,103,104,5,100,0,0,104,105,5,50,0,0,105,106,
  	5,57,0,0,106,12,1,0,0,0,107,108,5,98,0,0,108,109,5,109,0,0,109,110,5,
  	112,0,0,110,14,1,0,0,0,111,112,5,116,0,0,112,113,5,103,0,0,113,114,5,
  	97,0,0,114,16,1,0,0,0,115,116,5,99,0,0,116,117,5,104,0,0,117,118,5,114,
  	0,0,118,119,5,111,0,0,119,120,5,109,0,0,120,121,5,97,0,0,121,122,5,75,
  	0,0,122,123,5,101,0,0,123,124,5,121,0,0,124,18,1,0,0,0,125,126,5,107,
  	0,0,126,127,5,101,0,0,127,128,5,121,0,0,128,129,5,119,0,0,129,130,5,111,
  	0,0,130,131,5,114,0,0,131,132,5,100,0,0,132,133,5,50,0,0,133,134,5,68,
  	0,0,134,20,1,0,0,0,135,136,5,107,0,0,136,137,5,101,0,0,137,138,5,121,
  	0,0,138,139,5,119,0,0,139,140,5,111,0,0,140,141,5,114,0,0,141,142,5,100,
  	0,0,142,143,5,50,0,0,143,144,5,69,0,0,144,22,1,0,0,0,145,149,3,25,12,
  	0,146,149,3,27,13,0,147,149,3,41,20,0,148,145,1,0,0,0,148,146,1,0,0,0,
  	148,147,1,0,0,0,149,24,1,0,0,0,150,152,3,43,21,0,151,150,1,0,0,0,151,
  	152,1,0,0,0,152,154,1,0,0,0,153,155,3,37,18,0,154,153,1,0,0,0,155,156,
  	1,0,0,0,156,154,1,0,0,0,156,157,1,0,0,0,157,26,1,0,0,0,158,160,3,43,21,
  	0,159,158,1,0,0,0,159,160,1,0,0,0,160,161,1,0,0,0,161,163,3,29,14,0,162,
  	164,3,39,19,0,163,162,1,0,0,0,164,165,1,0,0,0,165,163,1,0,0,0,165,166,
  	1,0,0,0,166,28,1,0,0,0,167,168,5,48,0,0,168,169,7,0,0,0,169,30,1,0,0,
  	0,170,172,3,43,21,0,171,170,1,0,0,0,171,172,1,0,0,0,172,173,1,0,0,0,173,
  	175,3,33,16,0,174,171,1,0,0,0,174,175,1,0,0,0,175,176,1,0,0,0,176,177,
  	5,46,0,0,177,185,3,33,16,0,178,180,3,43,21,0,179,178,1,0,0,0,179,180,
  	1,0,0,0,180,181,1,0,0,0,181,182,3,33,16,0,182,183,5,46,0,0,183,185,1,
  	0,0,0,184,174,1,0,0,0,184,179,1,0,0,0,185,32,1,0,0,0,186,188,3,37,18,
  	0,187,186,1,0,0,0,188,189,1,0,0,0,189,187,1,0,0,0,189,190,1,0,0,0,190,
  	34,1,0,0,0,191,192,7,1,0,0,192,36,1,0,0,0,193,194,7,2,0,0,194,38,1,0,
  	0,0,195,196,7,3,0,0,196,40,1,0,0,0,197,199,3,43,21,0,198,197,1,0,0,0,
  	198,199,1,0,0,0,199,200,1,0,0,0,200,201,5,48,0,0,201,42,1,0,0,0,202,203,
  	7,4,0,0,203,44,1,0,0,0,204,206,5,34,0,0,205,207,3,47,23,0,206,205,1,0,
  	0,0,206,207,1,0,0,0,207,208,1,0,0,0,208,209,5,34,0,0,209,46,1,0,0,0,210,
  	212,3,49,24,0,211,210,1,0,0,0,212,213,1,0,0,0,213,211,1,0,0,0,213,214,
  	1,0,0,0,214,48,1,0,0,0,215,223,8,5,0,0,216,223,3,51,25,0,217,218,5,92,
  	0,0,218,223,5,10,0,0,219,220,5,92,0,0,220,221,5,13,0,0,221,223,5,10,0,
  	0,222,215,1,0,0,0,222,216,1,0,0,0,222,217,1,0,0,0,222,219,1,0,0,0,223,
  	50,1,0,0,0,224,225,5,92,0,0,225,226,7,6,0,0,226,52,1,0,0,0,227,229,7,
  	7,0,0,228,227,1,0,0,0,229,230,1,0,0,0,230,228,1,0,0,0,230,231,1,0,0,0,
  	231,232,1,0,0,0,232,233,6,26,0,0,233,54,1,0,0,0,234,236,5,13,0,0,235,
  	237,5,10,0,0,236,235,1,0,0,0,236,237,1,0,0,0,237,240,1,0,0,0,238,240,
  	5,10,0,0,239,234,1,0,0,0,239,238,1,0,0,0,240,241,1,0,0,0,241,242,6,27,
  	0,0,242,56,1,0,0,0,243,244,5,47,0,0,244,245,5,42,0,0,245,249,1,0,0,0,
  	246,248,9,0,0,0,247,246,1,0,0,0,248,251,1,0,0,0,249,250,1,0,0,0,249,247,
  	1,0,0,0,250,252,1,0,0,0,251,249,1,0,0,0,252,253,5,42,0,0,253,254,5,47,
  	0,0,254,255,1,0,0,0,255,256,6,28,0,0,256,58,1,0,0,0,257,258,5,47,0,0,
  	258,259,5,47,0,0,259,263,1,0,0,0,260,262,8,8,0,0,261,260,1,0,0,0,262,
  	265,1,0,0,0,263,261,1,0,0,0,263,264,1,0,0,0,264,266,1,0,0,0,265,263,1,
  	0,0,0,266,267,6,29,0,0,267,60,1,0,0,0,20,0,148,151,156,159,165,171,174,
  	179,184,189,198,206,213,222,230,236,239,249,263,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  tdblexerLexerStaticData = staticData.release();
}

}

TdbLexer::TdbLexer(CharStream *input) : Lexer(input) {
  TdbLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *tdblexerLexerStaticData->atn, tdblexerLexerStaticData->decisionToDFA, tdblexerLexerStaticData->sharedContextCache);
}

TdbLexer::~TdbLexer() {
  delete _interpreter;
}

std::string TdbLexer::getGrammarFileName() const {
  return "Tdb.g4";
}

const std::vector<std::string>& TdbLexer::getRuleNames() const {
  return tdblexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& TdbLexer::getChannelNames() const {
  return tdblexerLexerStaticData->channelNames;
}

const std::vector<std::string>& TdbLexer::getModeNames() const {
  return tdblexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& TdbLexer::getVocabulary() const {
  return tdblexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView TdbLexer::getSerializedATN() const {
  return tdblexerLexerStaticData->serializedATN;
}

const atn::ATN& TdbLexer::getATN() const {
  return *tdblexerLexerStaticData->atn;
}




void TdbLexer::initialize() {
  std::call_once(tdblexerLexerOnceFlag, tdblexerLexerInitialize);
}
