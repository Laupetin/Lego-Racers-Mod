
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
      "DecimalConstant", "HexadecimalConstant", "HexadecimalPrefix", "NonzeroDigit", 
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
      "", "'{'", "'}'", "'textures'", "'texture'", "'flipVertically'", "'keyword29'", 
      "'bmp'", "'tga'", "'chromaKey'", "'keyword2D'", "'keyword2E'"
    },
    std::vector<std::string>{
      "", "", "", "Textures", "Texture", "FlipVertically", "Keyword29", 
      "Bmp", "Tga", "ChromaKey", "Keyword2D", "Keyword2E", "IntegerConstant", 
      "StringLiteral", "Whitespace", "Newline", "BlockComment", "LineComment"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,17,245,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,1,0,
  	1,0,1,1,1,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,3,1,3,1,3,1,3,1,3,1,
  	3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,
  	1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,7,1,7,1,7,1,
  	7,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,9,1,9,1,9,1,9,1,9,1,9,1,9,
  	1,9,1,9,1,9,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,11,1,
  	11,1,11,3,11,145,8,11,1,12,3,12,148,8,12,1,12,1,12,5,12,152,8,12,10,12,
  	12,12,155,9,12,1,13,3,13,158,8,13,1,13,1,13,4,13,162,8,13,11,13,12,13,
  	163,1,14,1,14,1,14,1,15,1,15,1,16,1,16,1,17,1,17,1,18,3,18,176,8,18,1,
  	18,1,18,1,19,1,19,1,20,1,20,3,20,184,8,20,1,20,1,20,1,21,4,21,189,8,21,
  	11,21,12,21,190,1,22,1,22,1,22,1,22,1,22,1,22,1,22,3,22,200,8,22,1,23,
  	1,23,1,23,1,24,4,24,206,8,24,11,24,12,24,207,1,24,1,24,1,25,1,25,3,25,
  	214,8,25,1,25,3,25,217,8,25,1,25,1,25,1,26,1,26,1,26,1,26,5,26,225,8,
  	26,10,26,12,26,228,9,26,1,26,1,26,1,26,1,26,1,26,1,27,1,27,1,27,1,27,
  	5,27,239,8,27,10,27,12,27,242,9,27,1,27,1,27,1,226,0,28,1,1,3,2,5,3,7,
  	4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,0,27,0,29,0,31,0,33,0,
  	35,0,37,0,39,0,41,13,43,0,45,0,47,0,49,14,51,15,53,16,55,17,1,0,9,2,0,
  	88,88,120,120,1,0,49,57,1,0,48,57,3,0,48,57,65,70,97,102,2,0,43,43,45,
  	45,4,0,10,10,13,13,34,34,92,92,10,0,34,34,39,39,63,63,92,92,97,98,102,
  	102,110,110,114,114,116,116,118,118,2,0,9,9,32,32,2,0,10,10,13,13,250,
  	0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,
  	0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,
  	0,23,1,0,0,0,0,41,1,0,0,0,0,49,1,0,0,0,0,51,1,0,0,0,0,53,1,0,0,0,0,55,
  	1,0,0,0,1,57,1,0,0,0,3,59,1,0,0,0,5,61,1,0,0,0,7,70,1,0,0,0,9,78,1,0,
  	0,0,11,93,1,0,0,0,13,103,1,0,0,0,15,107,1,0,0,0,17,111,1,0,0,0,19,121,
  	1,0,0,0,21,131,1,0,0,0,23,144,1,0,0,0,25,147,1,0,0,0,27,157,1,0,0,0,29,
  	165,1,0,0,0,31,168,1,0,0,0,33,170,1,0,0,0,35,172,1,0,0,0,37,175,1,0,0,
  	0,39,179,1,0,0,0,41,181,1,0,0,0,43,188,1,0,0,0,45,199,1,0,0,0,47,201,
  	1,0,0,0,49,205,1,0,0,0,51,216,1,0,0,0,53,220,1,0,0,0,55,234,1,0,0,0,57,
  	58,5,123,0,0,58,2,1,0,0,0,59,60,5,125,0,0,60,4,1,0,0,0,61,62,5,116,0,
  	0,62,63,5,101,0,0,63,64,5,120,0,0,64,65,5,116,0,0,65,66,5,117,0,0,66,
  	67,5,114,0,0,67,68,5,101,0,0,68,69,5,115,0,0,69,6,1,0,0,0,70,71,5,116,
  	0,0,71,72,5,101,0,0,72,73,5,120,0,0,73,74,5,116,0,0,74,75,5,117,0,0,75,
  	76,5,114,0,0,76,77,5,101,0,0,77,8,1,0,0,0,78,79,5,102,0,0,79,80,5,108,
  	0,0,80,81,5,105,0,0,81,82,5,112,0,0,82,83,5,86,0,0,83,84,5,101,0,0,84,
  	85,5,114,0,0,85,86,5,116,0,0,86,87,5,105,0,0,87,88,5,99,0,0,88,89,5,97,
  	0,0,89,90,5,108,0,0,90,91,5,108,0,0,91,92,5,121,0,0,92,10,1,0,0,0,93,
  	94,5,107,0,0,94,95,5,101,0,0,95,96,5,121,0,0,96,97,5,119,0,0,97,98,5,
  	111,0,0,98,99,5,114,0,0,99,100,5,100,0,0,100,101,5,50,0,0,101,102,5,57,
  	0,0,102,12,1,0,0,0,103,104,5,98,0,0,104,105,5,109,0,0,105,106,5,112,0,
  	0,106,14,1,0,0,0,107,108,5,116,0,0,108,109,5,103,0,0,109,110,5,97,0,0,
  	110,16,1,0,0,0,111,112,5,99,0,0,112,113,5,104,0,0,113,114,5,114,0,0,114,
  	115,5,111,0,0,115,116,5,109,0,0,116,117,5,97,0,0,117,118,5,75,0,0,118,
  	119,5,101,0,0,119,120,5,121,0,0,120,18,1,0,0,0,121,122,5,107,0,0,122,
  	123,5,101,0,0,123,124,5,121,0,0,124,125,5,119,0,0,125,126,5,111,0,0,126,
  	127,5,114,0,0,127,128,5,100,0,0,128,129,5,50,0,0,129,130,5,68,0,0,130,
  	20,1,0,0,0,131,132,5,107,0,0,132,133,5,101,0,0,133,134,5,121,0,0,134,
  	135,5,119,0,0,135,136,5,111,0,0,136,137,5,114,0,0,137,138,5,100,0,0,138,
  	139,5,50,0,0,139,140,5,69,0,0,140,22,1,0,0,0,141,145,3,25,12,0,142,145,
  	3,27,13,0,143,145,3,37,18,0,144,141,1,0,0,0,144,142,1,0,0,0,144,143,1,
  	0,0,0,145,24,1,0,0,0,146,148,3,39,19,0,147,146,1,0,0,0,147,148,1,0,0,
  	0,148,149,1,0,0,0,149,153,3,31,15,0,150,152,3,33,16,0,151,150,1,0,0,0,
  	152,155,1,0,0,0,153,151,1,0,0,0,153,154,1,0,0,0,154,26,1,0,0,0,155,153,
  	1,0,0,0,156,158,3,39,19,0,157,156,1,0,0,0,157,158,1,0,0,0,158,159,1,0,
  	0,0,159,161,3,29,14,0,160,162,3,35,17,0,161,160,1,0,0,0,162,163,1,0,0,
  	0,163,161,1,0,0,0,163,164,1,0,0,0,164,28,1,0,0,0,165,166,5,48,0,0,166,
  	167,7,0,0,0,167,30,1,0,0,0,168,169,7,1,0,0,169,32,1,0,0,0,170,171,7,2,
  	0,0,171,34,1,0,0,0,172,173,7,3,0,0,173,36,1,0,0,0,174,176,3,39,19,0,175,
  	174,1,0,0,0,175,176,1,0,0,0,176,177,1,0,0,0,177,178,5,48,0,0,178,38,1,
  	0,0,0,179,180,7,4,0,0,180,40,1,0,0,0,181,183,5,34,0,0,182,184,3,43,21,
  	0,183,182,1,0,0,0,183,184,1,0,0,0,184,185,1,0,0,0,185,186,5,34,0,0,186,
  	42,1,0,0,0,187,189,3,45,22,0,188,187,1,0,0,0,189,190,1,0,0,0,190,188,
  	1,0,0,0,190,191,1,0,0,0,191,44,1,0,0,0,192,200,8,5,0,0,193,200,3,47,23,
  	0,194,195,5,92,0,0,195,200,5,10,0,0,196,197,5,92,0,0,197,198,5,13,0,0,
  	198,200,5,10,0,0,199,192,1,0,0,0,199,193,1,0,0,0,199,194,1,0,0,0,199,
  	196,1,0,0,0,200,46,1,0,0,0,201,202,5,92,0,0,202,203,7,6,0,0,203,48,1,
  	0,0,0,204,206,7,7,0,0,205,204,1,0,0,0,206,207,1,0,0,0,207,205,1,0,0,0,
  	207,208,1,0,0,0,208,209,1,0,0,0,209,210,6,24,0,0,210,50,1,0,0,0,211,213,
  	5,13,0,0,212,214,5,10,0,0,213,212,1,0,0,0,213,214,1,0,0,0,214,217,1,0,
  	0,0,215,217,5,10,0,0,216,211,1,0,0,0,216,215,1,0,0,0,217,218,1,0,0,0,
  	218,219,6,25,0,0,219,52,1,0,0,0,220,221,5,47,0,0,221,222,5,42,0,0,222,
  	226,1,0,0,0,223,225,9,0,0,0,224,223,1,0,0,0,225,228,1,0,0,0,226,227,1,
  	0,0,0,226,224,1,0,0,0,227,229,1,0,0,0,228,226,1,0,0,0,229,230,5,42,0,
  	0,230,231,5,47,0,0,231,232,1,0,0,0,232,233,6,26,0,0,233,54,1,0,0,0,234,
  	235,5,47,0,0,235,236,5,47,0,0,236,240,1,0,0,0,237,239,8,8,0,0,238,237,
  	1,0,0,0,239,242,1,0,0,0,240,238,1,0,0,0,240,241,1,0,0,0,241,243,1,0,0,
  	0,242,240,1,0,0,0,243,244,6,27,0,0,244,56,1,0,0,0,15,0,144,147,153,157,
  	163,175,183,190,199,207,213,216,226,240,1,6,0,0
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
