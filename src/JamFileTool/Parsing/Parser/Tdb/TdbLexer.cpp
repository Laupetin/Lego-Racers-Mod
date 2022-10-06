
// Generated from ..\..\..\src\JamFileTool\Parsing\Parser\Tdb\Tdb.g4 by ANTLR 4.10.1


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
  	4,0,19,264,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,1,0,1,0,1,1,1,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,
  	3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,
  	1,4,1,4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,6,1,6,1,
  	6,1,6,1,7,1,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,9,1,9,
  	1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,
  	10,1,10,1,10,1,11,1,11,1,11,3,11,149,8,11,1,12,3,12,152,8,12,1,12,1,12,
  	5,12,156,8,12,10,12,12,12,159,9,12,1,13,3,13,162,8,13,1,13,1,13,4,13,
  	166,8,13,11,13,12,13,167,1,14,1,14,1,14,1,15,3,15,174,8,15,1,15,1,15,
  	1,15,1,15,1,15,3,15,181,8,15,1,16,4,16,184,8,16,11,16,12,16,185,1,17,
  	1,17,1,18,1,18,1,19,1,19,1,20,3,20,195,8,20,1,20,1,20,1,21,1,21,1,22,
  	1,22,3,22,203,8,22,1,22,1,22,1,23,4,23,208,8,23,11,23,12,23,209,1,24,
  	1,24,1,24,1,24,1,24,1,24,1,24,3,24,219,8,24,1,25,1,25,1,25,1,26,4,26,
  	225,8,26,11,26,12,26,226,1,26,1,26,1,27,1,27,3,27,233,8,27,1,27,3,27,
  	236,8,27,1,27,1,27,1,28,1,28,1,28,1,28,5,28,244,8,28,10,28,12,28,247,
  	9,28,1,28,1,28,1,28,1,28,1,28,1,29,1,29,1,29,1,29,5,29,258,8,29,10,29,
  	12,29,261,9,29,1,29,1,29,1,245,0,30,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,
  	8,17,9,19,10,21,11,23,12,25,0,27,0,29,0,31,13,33,14,35,0,37,0,39,0,41,
  	0,43,0,45,15,47,0,49,0,51,0,53,16,55,17,57,18,59,19,1,0,9,2,0,88,88,120,
  	120,1,0,49,57,1,0,48,57,3,0,48,57,65,70,97,102,2,0,43,43,45,45,4,0,10,
  	10,13,13,34,34,92,92,10,0,34,34,39,39,63,63,92,92,97,98,102,102,110,110,
  	114,114,116,116,118,118,2,0,9,9,32,32,2,0,10,10,13,13,272,0,1,1,0,0,0,
  	0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,
  	0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,
  	0,31,1,0,0,0,0,33,1,0,0,0,0,45,1,0,0,0,0,53,1,0,0,0,0,55,1,0,0,0,0,57,
  	1,0,0,0,0,59,1,0,0,0,1,61,1,0,0,0,3,63,1,0,0,0,5,65,1,0,0,0,7,74,1,0,
  	0,0,9,82,1,0,0,0,11,97,1,0,0,0,13,107,1,0,0,0,15,111,1,0,0,0,17,115,1,
  	0,0,0,19,125,1,0,0,0,21,135,1,0,0,0,23,148,1,0,0,0,25,151,1,0,0,0,27,
  	161,1,0,0,0,29,169,1,0,0,0,31,180,1,0,0,0,33,183,1,0,0,0,35,187,1,0,0,
  	0,37,189,1,0,0,0,39,191,1,0,0,0,41,194,1,0,0,0,43,198,1,0,0,0,45,200,
  	1,0,0,0,47,207,1,0,0,0,49,218,1,0,0,0,51,220,1,0,0,0,53,224,1,0,0,0,55,
  	235,1,0,0,0,57,239,1,0,0,0,59,253,1,0,0,0,61,62,5,123,0,0,62,2,1,0,0,
  	0,63,64,5,125,0,0,64,4,1,0,0,0,65,66,5,116,0,0,66,67,5,101,0,0,67,68,
  	5,120,0,0,68,69,5,116,0,0,69,70,5,117,0,0,70,71,5,114,0,0,71,72,5,101,
  	0,0,72,73,5,115,0,0,73,6,1,0,0,0,74,75,5,116,0,0,75,76,5,101,0,0,76,77,
  	5,120,0,0,77,78,5,116,0,0,78,79,5,117,0,0,79,80,5,114,0,0,80,81,5,101,
  	0,0,81,8,1,0,0,0,82,83,5,102,0,0,83,84,5,108,0,0,84,85,5,105,0,0,85,86,
  	5,112,0,0,86,87,5,86,0,0,87,88,5,101,0,0,88,89,5,114,0,0,89,90,5,116,
  	0,0,90,91,5,105,0,0,91,92,5,99,0,0,92,93,5,97,0,0,93,94,5,108,0,0,94,
  	95,5,108,0,0,95,96,5,121,0,0,96,10,1,0,0,0,97,98,5,107,0,0,98,99,5,101,
  	0,0,99,100,5,121,0,0,100,101,5,119,0,0,101,102,5,111,0,0,102,103,5,114,
  	0,0,103,104,5,100,0,0,104,105,5,50,0,0,105,106,5,57,0,0,106,12,1,0,0,
  	0,107,108,5,98,0,0,108,109,5,109,0,0,109,110,5,112,0,0,110,14,1,0,0,0,
  	111,112,5,116,0,0,112,113,5,103,0,0,113,114,5,97,0,0,114,16,1,0,0,0,115,
  	116,5,99,0,0,116,117,5,104,0,0,117,118,5,114,0,0,118,119,5,111,0,0,119,
  	120,5,109,0,0,120,121,5,97,0,0,121,122,5,75,0,0,122,123,5,101,0,0,123,
  	124,5,121,0,0,124,18,1,0,0,0,125,126,5,107,0,0,126,127,5,101,0,0,127,
  	128,5,121,0,0,128,129,5,119,0,0,129,130,5,111,0,0,130,131,5,114,0,0,131,
  	132,5,100,0,0,132,133,5,50,0,0,133,134,5,68,0,0,134,20,1,0,0,0,135,136,
  	5,107,0,0,136,137,5,101,0,0,137,138,5,121,0,0,138,139,5,119,0,0,139,140,
  	5,111,0,0,140,141,5,114,0,0,141,142,5,100,0,0,142,143,5,50,0,0,143,144,
  	5,69,0,0,144,22,1,0,0,0,145,149,3,25,12,0,146,149,3,27,13,0,147,149,3,
  	41,20,0,148,145,1,0,0,0,148,146,1,0,0,0,148,147,1,0,0,0,149,24,1,0,0,
  	0,150,152,3,43,21,0,151,150,1,0,0,0,151,152,1,0,0,0,152,153,1,0,0,0,153,
  	157,3,35,17,0,154,156,3,37,18,0,155,154,1,0,0,0,156,159,1,0,0,0,157,155,
  	1,0,0,0,157,158,1,0,0,0,158,26,1,0,0,0,159,157,1,0,0,0,160,162,3,43,21,
  	0,161,160,1,0,0,0,161,162,1,0,0,0,162,163,1,0,0,0,163,165,3,29,14,0,164,
  	166,3,39,19,0,165,164,1,0,0,0,166,167,1,0,0,0,167,165,1,0,0,0,167,168,
  	1,0,0,0,168,28,1,0,0,0,169,170,5,48,0,0,170,171,7,0,0,0,171,30,1,0,0,
  	0,172,174,3,33,16,0,173,172,1,0,0,0,173,174,1,0,0,0,174,175,1,0,0,0,175,
  	176,5,46,0,0,176,181,3,33,16,0,177,178,3,33,16,0,178,179,5,46,0,0,179,
  	181,1,0,0,0,180,173,1,0,0,0,180,177,1,0,0,0,181,32,1,0,0,0,182,184,3,
  	37,18,0,183,182,1,0,0,0,184,185,1,0,0,0,185,183,1,0,0,0,185,186,1,0,0,
  	0,186,34,1,0,0,0,187,188,7,1,0,0,188,36,1,0,0,0,189,190,7,2,0,0,190,38,
  	1,0,0,0,191,192,7,3,0,0,192,40,1,0,0,0,193,195,3,43,21,0,194,193,1,0,
  	0,0,194,195,1,0,0,0,195,196,1,0,0,0,196,197,5,48,0,0,197,42,1,0,0,0,198,
  	199,7,4,0,0,199,44,1,0,0,0,200,202,5,34,0,0,201,203,3,47,23,0,202,201,
  	1,0,0,0,202,203,1,0,0,0,203,204,1,0,0,0,204,205,5,34,0,0,205,46,1,0,0,
  	0,206,208,3,49,24,0,207,206,1,0,0,0,208,209,1,0,0,0,209,207,1,0,0,0,209,
  	210,1,0,0,0,210,48,1,0,0,0,211,219,8,5,0,0,212,219,3,51,25,0,213,214,
  	5,92,0,0,214,219,5,10,0,0,215,216,5,92,0,0,216,217,5,13,0,0,217,219,5,
  	10,0,0,218,211,1,0,0,0,218,212,1,0,0,0,218,213,1,0,0,0,218,215,1,0,0,
  	0,219,50,1,0,0,0,220,221,5,92,0,0,221,222,7,6,0,0,222,52,1,0,0,0,223,
  	225,7,7,0,0,224,223,1,0,0,0,225,226,1,0,0,0,226,224,1,0,0,0,226,227,1,
  	0,0,0,227,228,1,0,0,0,228,229,6,26,0,0,229,54,1,0,0,0,230,232,5,13,0,
  	0,231,233,5,10,0,0,232,231,1,0,0,0,232,233,1,0,0,0,233,236,1,0,0,0,234,
  	236,5,10,0,0,235,230,1,0,0,0,235,234,1,0,0,0,236,237,1,0,0,0,237,238,
  	6,27,0,0,238,56,1,0,0,0,239,240,5,47,0,0,240,241,5,42,0,0,241,245,1,0,
  	0,0,242,244,9,0,0,0,243,242,1,0,0,0,244,247,1,0,0,0,245,246,1,0,0,0,245,
  	243,1,0,0,0,246,248,1,0,0,0,247,245,1,0,0,0,248,249,5,42,0,0,249,250,
  	5,47,0,0,250,251,1,0,0,0,251,252,6,28,0,0,252,58,1,0,0,0,253,254,5,47,
  	0,0,254,255,5,47,0,0,255,259,1,0,0,0,256,258,8,8,0,0,257,256,1,0,0,0,
  	258,261,1,0,0,0,259,257,1,0,0,0,259,260,1,0,0,0,260,262,1,0,0,0,261,259,
  	1,0,0,0,262,263,6,29,0,0,263,60,1,0,0,0,18,0,148,151,157,161,167,173,
  	180,185,194,202,209,218,226,232,235,245,259,1,6,0,0
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
