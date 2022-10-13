
// Generated from ..\..\..\src\AssetLib\Parsing\Parser\Idb\Idb.g4 by ANTLR 4.10.1


#include "IdbLexer.h"


using namespace antlr4;

using namespace idb;


using namespace antlr4;

namespace {

struct IdbLexerStaticData final {
  IdbLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

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
IdbLexerStaticData *idblexerLexerStaticData = nullptr;

void idblexerLexerInitialize() {
  assert(idblexerLexerStaticData == nullptr);
  auto staticData = std::make_unique<IdbLexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "Images", "Image", "FlipVertical", "Bmp", "Tga", "ChromaKey", 
      "Tint", "IntegerConstant", "DecimalConstant", "HexadecimalConstant", 
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
      "", "'{'", "'}'", "'images'", "'image'", "'flipVertical'", "'bmp'", 
      "'tga'", "'chromaKey'", "'tint'"
    },
    std::vector<std::string>{
      "", "", "", "Images", "Image", "FlipVertical", "Bmp", "Tga", "ChromaKey", 
      "Tint", "IntegerConstant", "FloatingConstant", "DigitSequence", "StringLiteral", 
      "Whitespace", "Newline", "BlockComment", "LineComment"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,17,235,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,1,0,
  	1,0,1,1,1,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,3,1,3,1,3,1,3,1,3,1,3,1,4,1,
  	4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,6,1,6,
  	1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,
  	9,1,9,1,9,3,9,114,8,9,1,10,3,10,117,8,10,1,10,1,10,5,10,121,8,10,10,10,
  	12,10,124,9,10,1,11,3,11,127,8,11,1,11,1,11,4,11,131,8,11,11,11,12,11,
  	132,1,12,1,12,1,12,1,13,3,13,139,8,13,1,13,3,13,142,8,13,1,13,1,13,1,
  	13,3,13,147,8,13,1,13,1,13,1,13,3,13,152,8,13,1,14,4,14,155,8,14,11,14,
  	12,14,156,1,15,1,15,1,16,1,16,1,17,1,17,1,18,3,18,166,8,18,1,18,1,18,
  	1,19,1,19,1,20,1,20,3,20,174,8,20,1,20,1,20,1,21,4,21,179,8,21,11,21,
  	12,21,180,1,22,1,22,1,22,1,22,1,22,1,22,1,22,3,22,190,8,22,1,23,1,23,
  	1,23,1,24,4,24,196,8,24,11,24,12,24,197,1,24,1,24,1,25,1,25,3,25,204,
  	8,25,1,25,3,25,207,8,25,1,25,1,25,1,26,1,26,1,26,1,26,5,26,215,8,26,10,
  	26,12,26,218,9,26,1,26,1,26,1,26,1,26,1,26,1,27,1,27,1,27,1,27,5,27,229,
  	8,27,10,27,12,27,232,9,27,1,27,1,27,1,216,0,28,1,1,3,2,5,3,7,4,9,5,11,
  	6,13,7,15,8,17,9,19,10,21,0,23,0,25,0,27,11,29,12,31,0,33,0,35,0,37,0,
  	39,0,41,13,43,0,45,0,47,0,49,14,51,15,53,16,55,17,1,0,9,2,0,88,88,120,
  	120,1,0,49,57,1,0,48,57,3,0,48,57,65,70,97,102,2,0,43,43,45,45,4,0,10,
  	10,13,13,34,34,92,92,10,0,34,34,39,39,63,63,92,92,97,98,102,102,110,110,
  	114,114,116,116,118,118,2,0,9,9,32,32,2,0,10,10,13,13,245,0,1,1,0,0,0,
  	0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,
  	0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,
  	0,41,1,0,0,0,0,49,1,0,0,0,0,51,1,0,0,0,0,53,1,0,0,0,0,55,1,0,0,0,1,57,
  	1,0,0,0,3,59,1,0,0,0,5,61,1,0,0,0,7,68,1,0,0,0,9,74,1,0,0,0,11,87,1,0,
  	0,0,13,91,1,0,0,0,15,95,1,0,0,0,17,105,1,0,0,0,19,113,1,0,0,0,21,116,
  	1,0,0,0,23,126,1,0,0,0,25,134,1,0,0,0,27,151,1,0,0,0,29,154,1,0,0,0,31,
  	158,1,0,0,0,33,160,1,0,0,0,35,162,1,0,0,0,37,165,1,0,0,0,39,169,1,0,0,
  	0,41,171,1,0,0,0,43,178,1,0,0,0,45,189,1,0,0,0,47,191,1,0,0,0,49,195,
  	1,0,0,0,51,206,1,0,0,0,53,210,1,0,0,0,55,224,1,0,0,0,57,58,5,123,0,0,
  	58,2,1,0,0,0,59,60,5,125,0,0,60,4,1,0,0,0,61,62,5,105,0,0,62,63,5,109,
  	0,0,63,64,5,97,0,0,64,65,5,103,0,0,65,66,5,101,0,0,66,67,5,115,0,0,67,
  	6,1,0,0,0,68,69,5,105,0,0,69,70,5,109,0,0,70,71,5,97,0,0,71,72,5,103,
  	0,0,72,73,5,101,0,0,73,8,1,0,0,0,74,75,5,102,0,0,75,76,5,108,0,0,76,77,
  	5,105,0,0,77,78,5,112,0,0,78,79,5,86,0,0,79,80,5,101,0,0,80,81,5,114,
  	0,0,81,82,5,116,0,0,82,83,5,105,0,0,83,84,5,99,0,0,84,85,5,97,0,0,85,
  	86,5,108,0,0,86,10,1,0,0,0,87,88,5,98,0,0,88,89,5,109,0,0,89,90,5,112,
  	0,0,90,12,1,0,0,0,91,92,5,116,0,0,92,93,5,103,0,0,93,94,5,97,0,0,94,14,
  	1,0,0,0,95,96,5,99,0,0,96,97,5,104,0,0,97,98,5,114,0,0,98,99,5,111,0,
  	0,99,100,5,109,0,0,100,101,5,97,0,0,101,102,5,75,0,0,102,103,5,101,0,
  	0,103,104,5,121,0,0,104,16,1,0,0,0,105,106,5,116,0,0,106,107,5,105,0,
  	0,107,108,5,110,0,0,108,109,5,116,0,0,109,18,1,0,0,0,110,114,3,21,10,
  	0,111,114,3,23,11,0,112,114,3,37,18,0,113,110,1,0,0,0,113,111,1,0,0,0,
  	113,112,1,0,0,0,114,20,1,0,0,0,115,117,3,39,19,0,116,115,1,0,0,0,116,
  	117,1,0,0,0,117,118,1,0,0,0,118,122,3,31,15,0,119,121,3,33,16,0,120,119,
  	1,0,0,0,121,124,1,0,0,0,122,120,1,0,0,0,122,123,1,0,0,0,123,22,1,0,0,
  	0,124,122,1,0,0,0,125,127,3,39,19,0,126,125,1,0,0,0,126,127,1,0,0,0,127,
  	128,1,0,0,0,128,130,3,25,12,0,129,131,3,35,17,0,130,129,1,0,0,0,131,132,
  	1,0,0,0,132,130,1,0,0,0,132,133,1,0,0,0,133,24,1,0,0,0,134,135,5,48,0,
  	0,135,136,7,0,0,0,136,26,1,0,0,0,137,139,3,39,19,0,138,137,1,0,0,0,138,
  	139,1,0,0,0,139,140,1,0,0,0,140,142,3,29,14,0,141,138,1,0,0,0,141,142,
  	1,0,0,0,142,143,1,0,0,0,143,144,5,46,0,0,144,152,3,29,14,0,145,147,3,
  	39,19,0,146,145,1,0,0,0,146,147,1,0,0,0,147,148,1,0,0,0,148,149,3,29,
  	14,0,149,150,5,46,0,0,150,152,1,0,0,0,151,141,1,0,0,0,151,146,1,0,0,0,
  	152,28,1,0,0,0,153,155,3,33,16,0,154,153,1,0,0,0,155,156,1,0,0,0,156,
  	154,1,0,0,0,156,157,1,0,0,0,157,30,1,0,0,0,158,159,7,1,0,0,159,32,1,0,
  	0,0,160,161,7,2,0,0,161,34,1,0,0,0,162,163,7,3,0,0,163,36,1,0,0,0,164,
  	166,3,39,19,0,165,164,1,0,0,0,165,166,1,0,0,0,166,167,1,0,0,0,167,168,
  	5,48,0,0,168,38,1,0,0,0,169,170,7,4,0,0,170,40,1,0,0,0,171,173,5,34,0,
  	0,172,174,3,43,21,0,173,172,1,0,0,0,173,174,1,0,0,0,174,175,1,0,0,0,175,
  	176,5,34,0,0,176,42,1,0,0,0,177,179,3,45,22,0,178,177,1,0,0,0,179,180,
  	1,0,0,0,180,178,1,0,0,0,180,181,1,0,0,0,181,44,1,0,0,0,182,190,8,5,0,
  	0,183,190,3,47,23,0,184,185,5,92,0,0,185,190,5,10,0,0,186,187,5,92,0,
  	0,187,188,5,13,0,0,188,190,5,10,0,0,189,182,1,0,0,0,189,183,1,0,0,0,189,
  	184,1,0,0,0,189,186,1,0,0,0,190,46,1,0,0,0,191,192,5,92,0,0,192,193,7,
  	6,0,0,193,48,1,0,0,0,194,196,7,7,0,0,195,194,1,0,0,0,196,197,1,0,0,0,
  	197,195,1,0,0,0,197,198,1,0,0,0,198,199,1,0,0,0,199,200,6,24,0,0,200,
  	50,1,0,0,0,201,203,5,13,0,0,202,204,5,10,0,0,203,202,1,0,0,0,203,204,
  	1,0,0,0,204,207,1,0,0,0,205,207,5,10,0,0,206,201,1,0,0,0,206,205,1,0,
  	0,0,207,208,1,0,0,0,208,209,6,25,0,0,209,52,1,0,0,0,210,211,5,47,0,0,
  	211,212,5,42,0,0,212,216,1,0,0,0,213,215,9,0,0,0,214,213,1,0,0,0,215,
  	218,1,0,0,0,216,217,1,0,0,0,216,214,1,0,0,0,217,219,1,0,0,0,218,216,1,
  	0,0,0,219,220,5,42,0,0,220,221,5,47,0,0,221,222,1,0,0,0,222,223,6,26,
  	0,0,223,54,1,0,0,0,224,225,5,47,0,0,225,226,5,47,0,0,226,230,1,0,0,0,
  	227,229,8,8,0,0,228,227,1,0,0,0,229,232,1,0,0,0,230,228,1,0,0,0,230,231,
  	1,0,0,0,231,233,1,0,0,0,232,230,1,0,0,0,233,234,6,27,0,0,234,56,1,0,0,
  	0,20,0,113,116,122,126,132,138,141,146,151,156,165,173,180,189,197,203,
  	206,216,230,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  idblexerLexerStaticData = staticData.release();
}

}

IdbLexer::IdbLexer(CharStream *input) : Lexer(input) {
  IdbLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *idblexerLexerStaticData->atn, idblexerLexerStaticData->decisionToDFA, idblexerLexerStaticData->sharedContextCache);
}

IdbLexer::~IdbLexer() {
  delete _interpreter;
}

std::string IdbLexer::getGrammarFileName() const {
  return "Idb.g4";
}

const std::vector<std::string>& IdbLexer::getRuleNames() const {
  return idblexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& IdbLexer::getChannelNames() const {
  return idblexerLexerStaticData->channelNames;
}

const std::vector<std::string>& IdbLexer::getModeNames() const {
  return idblexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& IdbLexer::getVocabulary() const {
  return idblexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView IdbLexer::getSerializedATN() const {
  return idblexerLexerStaticData->serializedATN;
}

const atn::ATN& IdbLexer::getATN() const {
  return *idblexerLexerStaticData->atn;
}




void IdbLexer::initialize() {
  std::call_once(idblexerLexerOnceFlag, idblexerLexerInitialize);
}