
// Generated from ..\..\..\src\JamFileTool\Parsing\Parser\Idb\Idb.g4 by ANTLR 4.10.1


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
      "HexadecimalPrefix", "NonzeroDigit", "Digit", "HexadecimalDigit", 
      "Zero", "IntegerSign", "StringLiteral", "SCharSequence", "SChar", 
      "EscapeSequence", "Whitespace", "Newline", "BlockComment", "LineComment"
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
      "Tint", "IntegerConstant", "StringLiteral", "Whitespace", "Newline", 
      "BlockComment", "LineComment"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,15,210,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,1,0,1,0,1,1,1,1,1,2,1,2,
  	1,2,1,2,1,2,1,2,1,2,1,3,1,3,1,3,1,3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,1,4,1,
  	4,1,4,1,4,1,4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,7,1,7,1,7,
  	1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,9,1,9,1,9,3,9,110,8,
  	9,1,10,3,10,113,8,10,1,10,1,10,5,10,117,8,10,10,10,12,10,120,9,10,1,11,
  	3,11,123,8,11,1,11,1,11,4,11,127,8,11,11,11,12,11,128,1,12,1,12,1,12,
  	1,13,1,13,1,14,1,14,1,15,1,15,1,16,3,16,141,8,16,1,16,1,16,1,17,1,17,
  	1,18,1,18,3,18,149,8,18,1,18,1,18,1,19,4,19,154,8,19,11,19,12,19,155,
  	1,20,1,20,1,20,1,20,1,20,1,20,1,20,3,20,165,8,20,1,21,1,21,1,21,1,22,
  	4,22,171,8,22,11,22,12,22,172,1,22,1,22,1,23,1,23,3,23,179,8,23,1,23,
  	3,23,182,8,23,1,23,1,23,1,24,1,24,1,24,1,24,5,24,190,8,24,10,24,12,24,
  	193,9,24,1,24,1,24,1,24,1,24,1,24,1,25,1,25,1,25,1,25,5,25,204,8,25,10,
  	25,12,25,207,9,25,1,25,1,25,1,191,0,26,1,1,3,2,5,3,7,4,9,5,11,6,13,7,
  	15,8,17,9,19,10,21,0,23,0,25,0,27,0,29,0,31,0,33,0,35,0,37,11,39,0,41,
  	0,43,0,45,12,47,13,49,14,51,15,1,0,9,2,0,88,88,120,120,1,0,49,57,1,0,
  	48,57,3,0,48,57,65,70,97,102,2,0,43,43,45,45,4,0,10,10,13,13,34,34,92,
  	92,10,0,34,34,39,39,63,63,92,92,97,98,102,102,110,110,114,114,116,116,
  	118,118,2,0,9,9,32,32,2,0,10,10,13,13,215,0,1,1,0,0,0,0,3,1,0,0,0,0,5,
  	1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,
  	0,0,17,1,0,0,0,0,19,1,0,0,0,0,37,1,0,0,0,0,45,1,0,0,0,0,47,1,0,0,0,0,
  	49,1,0,0,0,0,51,1,0,0,0,1,53,1,0,0,0,3,55,1,0,0,0,5,57,1,0,0,0,7,64,1,
  	0,0,0,9,70,1,0,0,0,11,83,1,0,0,0,13,87,1,0,0,0,15,91,1,0,0,0,17,101,1,
  	0,0,0,19,109,1,0,0,0,21,112,1,0,0,0,23,122,1,0,0,0,25,130,1,0,0,0,27,
  	133,1,0,0,0,29,135,1,0,0,0,31,137,1,0,0,0,33,140,1,0,0,0,35,144,1,0,0,
  	0,37,146,1,0,0,0,39,153,1,0,0,0,41,164,1,0,0,0,43,166,1,0,0,0,45,170,
  	1,0,0,0,47,181,1,0,0,0,49,185,1,0,0,0,51,199,1,0,0,0,53,54,5,123,0,0,
  	54,2,1,0,0,0,55,56,5,125,0,0,56,4,1,0,0,0,57,58,5,105,0,0,58,59,5,109,
  	0,0,59,60,5,97,0,0,60,61,5,103,0,0,61,62,5,101,0,0,62,63,5,115,0,0,63,
  	6,1,0,0,0,64,65,5,105,0,0,65,66,5,109,0,0,66,67,5,97,0,0,67,68,5,103,
  	0,0,68,69,5,101,0,0,69,8,1,0,0,0,70,71,5,102,0,0,71,72,5,108,0,0,72,73,
  	5,105,0,0,73,74,5,112,0,0,74,75,5,86,0,0,75,76,5,101,0,0,76,77,5,114,
  	0,0,77,78,5,116,0,0,78,79,5,105,0,0,79,80,5,99,0,0,80,81,5,97,0,0,81,
  	82,5,108,0,0,82,10,1,0,0,0,83,84,5,98,0,0,84,85,5,109,0,0,85,86,5,112,
  	0,0,86,12,1,0,0,0,87,88,5,116,0,0,88,89,5,103,0,0,89,90,5,97,0,0,90,14,
  	1,0,0,0,91,92,5,99,0,0,92,93,5,104,0,0,93,94,5,114,0,0,94,95,5,111,0,
  	0,95,96,5,109,0,0,96,97,5,97,0,0,97,98,5,75,0,0,98,99,5,101,0,0,99,100,
  	5,121,0,0,100,16,1,0,0,0,101,102,5,116,0,0,102,103,5,105,0,0,103,104,
  	5,110,0,0,104,105,5,116,0,0,105,18,1,0,0,0,106,110,3,21,10,0,107,110,
  	3,23,11,0,108,110,3,33,16,0,109,106,1,0,0,0,109,107,1,0,0,0,109,108,1,
  	0,0,0,110,20,1,0,0,0,111,113,3,35,17,0,112,111,1,0,0,0,112,113,1,0,0,
  	0,113,114,1,0,0,0,114,118,3,27,13,0,115,117,3,29,14,0,116,115,1,0,0,0,
  	117,120,1,0,0,0,118,116,1,0,0,0,118,119,1,0,0,0,119,22,1,0,0,0,120,118,
  	1,0,0,0,121,123,3,35,17,0,122,121,1,0,0,0,122,123,1,0,0,0,123,124,1,0,
  	0,0,124,126,3,25,12,0,125,127,3,31,15,0,126,125,1,0,0,0,127,128,1,0,0,
  	0,128,126,1,0,0,0,128,129,1,0,0,0,129,24,1,0,0,0,130,131,5,48,0,0,131,
  	132,7,0,0,0,132,26,1,0,0,0,133,134,7,1,0,0,134,28,1,0,0,0,135,136,7,2,
  	0,0,136,30,1,0,0,0,137,138,7,3,0,0,138,32,1,0,0,0,139,141,3,35,17,0,140,
  	139,1,0,0,0,140,141,1,0,0,0,141,142,1,0,0,0,142,143,5,48,0,0,143,34,1,
  	0,0,0,144,145,7,4,0,0,145,36,1,0,0,0,146,148,5,34,0,0,147,149,3,39,19,
  	0,148,147,1,0,0,0,148,149,1,0,0,0,149,150,1,0,0,0,150,151,5,34,0,0,151,
  	38,1,0,0,0,152,154,3,41,20,0,153,152,1,0,0,0,154,155,1,0,0,0,155,153,
  	1,0,0,0,155,156,1,0,0,0,156,40,1,0,0,0,157,165,8,5,0,0,158,165,3,43,21,
  	0,159,160,5,92,0,0,160,165,5,10,0,0,161,162,5,92,0,0,162,163,5,13,0,0,
  	163,165,5,10,0,0,164,157,1,0,0,0,164,158,1,0,0,0,164,159,1,0,0,0,164,
  	161,1,0,0,0,165,42,1,0,0,0,166,167,5,92,0,0,167,168,7,6,0,0,168,44,1,
  	0,0,0,169,171,7,7,0,0,170,169,1,0,0,0,171,172,1,0,0,0,172,170,1,0,0,0,
  	172,173,1,0,0,0,173,174,1,0,0,0,174,175,6,22,0,0,175,46,1,0,0,0,176,178,
  	5,13,0,0,177,179,5,10,0,0,178,177,1,0,0,0,178,179,1,0,0,0,179,182,1,0,
  	0,0,180,182,5,10,0,0,181,176,1,0,0,0,181,180,1,0,0,0,182,183,1,0,0,0,
  	183,184,6,23,0,0,184,48,1,0,0,0,185,186,5,47,0,0,186,187,5,42,0,0,187,
  	191,1,0,0,0,188,190,9,0,0,0,189,188,1,0,0,0,190,193,1,0,0,0,191,192,1,
  	0,0,0,191,189,1,0,0,0,192,194,1,0,0,0,193,191,1,0,0,0,194,195,5,42,0,
  	0,195,196,5,47,0,0,196,197,1,0,0,0,197,198,6,24,0,0,198,50,1,0,0,0,199,
  	200,5,47,0,0,200,201,5,47,0,0,201,205,1,0,0,0,202,204,8,8,0,0,203,202,
  	1,0,0,0,204,207,1,0,0,0,205,203,1,0,0,0,205,206,1,0,0,0,206,208,1,0,0,
  	0,207,205,1,0,0,0,208,209,6,25,0,0,209,52,1,0,0,0,15,0,109,112,118,122,
  	128,140,148,155,164,172,178,181,191,205,1,6,0,0
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
