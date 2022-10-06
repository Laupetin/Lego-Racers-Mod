
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
  	4,0,17,229,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,1,0,
  	1,0,1,1,1,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,3,1,3,1,3,1,3,1,3,1,3,1,4,1,
  	4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,6,1,6,
  	1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,
  	9,1,9,1,9,3,9,114,8,9,1,10,3,10,117,8,10,1,10,1,10,5,10,121,8,10,10,10,
  	12,10,124,9,10,1,11,3,11,127,8,11,1,11,1,11,4,11,131,8,11,11,11,12,11,
  	132,1,12,1,12,1,12,1,13,3,13,139,8,13,1,13,1,13,1,13,1,13,1,13,3,13,146,
  	8,13,1,14,4,14,149,8,14,11,14,12,14,150,1,15,1,15,1,16,1,16,1,17,1,17,
  	1,18,3,18,160,8,18,1,18,1,18,1,19,1,19,1,20,1,20,3,20,168,8,20,1,20,1,
  	20,1,21,4,21,173,8,21,11,21,12,21,174,1,22,1,22,1,22,1,22,1,22,1,22,1,
  	22,3,22,184,8,22,1,23,1,23,1,23,1,24,4,24,190,8,24,11,24,12,24,191,1,
  	24,1,24,1,25,1,25,3,25,198,8,25,1,25,3,25,201,8,25,1,25,1,25,1,26,1,26,
  	1,26,1,26,5,26,209,8,26,10,26,12,26,212,9,26,1,26,1,26,1,26,1,26,1,26,
  	1,27,1,27,1,27,1,27,5,27,223,8,27,10,27,12,27,226,9,27,1,27,1,27,1,210,
  	0,28,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,0,23,0,25,0,27,
  	11,29,12,31,0,33,0,35,0,37,0,39,0,41,13,43,0,45,0,47,0,49,14,51,15,53,
  	16,55,17,1,0,9,2,0,88,88,120,120,1,0,49,57,1,0,48,57,3,0,48,57,65,70,
  	97,102,2,0,43,43,45,45,4,0,10,10,13,13,34,34,92,92,10,0,34,34,39,39,63,
  	63,92,92,97,98,102,102,110,110,114,114,116,116,118,118,2,0,9,9,32,32,
  	2,0,10,10,13,13,237,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,
  	9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,
  	0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,41,1,0,0,0,0,49,1,0,0,0,0,51,1,0,0,
  	0,0,53,1,0,0,0,0,55,1,0,0,0,1,57,1,0,0,0,3,59,1,0,0,0,5,61,1,0,0,0,7,
  	68,1,0,0,0,9,74,1,0,0,0,11,87,1,0,0,0,13,91,1,0,0,0,15,95,1,0,0,0,17,
  	105,1,0,0,0,19,113,1,0,0,0,21,116,1,0,0,0,23,126,1,0,0,0,25,134,1,0,0,
  	0,27,145,1,0,0,0,29,148,1,0,0,0,31,152,1,0,0,0,33,154,1,0,0,0,35,156,
  	1,0,0,0,37,159,1,0,0,0,39,163,1,0,0,0,41,165,1,0,0,0,43,172,1,0,0,0,45,
  	183,1,0,0,0,47,185,1,0,0,0,49,189,1,0,0,0,51,200,1,0,0,0,53,204,1,0,0,
  	0,55,218,1,0,0,0,57,58,5,123,0,0,58,2,1,0,0,0,59,60,5,125,0,0,60,4,1,
  	0,0,0,61,62,5,105,0,0,62,63,5,109,0,0,63,64,5,97,0,0,64,65,5,103,0,0,
  	65,66,5,101,0,0,66,67,5,115,0,0,67,6,1,0,0,0,68,69,5,105,0,0,69,70,5,
  	109,0,0,70,71,5,97,0,0,71,72,5,103,0,0,72,73,5,101,0,0,73,8,1,0,0,0,74,
  	75,5,102,0,0,75,76,5,108,0,0,76,77,5,105,0,0,77,78,5,112,0,0,78,79,5,
  	86,0,0,79,80,5,101,0,0,80,81,5,114,0,0,81,82,5,116,0,0,82,83,5,105,0,
  	0,83,84,5,99,0,0,84,85,5,97,0,0,85,86,5,108,0,0,86,10,1,0,0,0,87,88,5,
  	98,0,0,88,89,5,109,0,0,89,90,5,112,0,0,90,12,1,0,0,0,91,92,5,116,0,0,
  	92,93,5,103,0,0,93,94,5,97,0,0,94,14,1,0,0,0,95,96,5,99,0,0,96,97,5,104,
  	0,0,97,98,5,114,0,0,98,99,5,111,0,0,99,100,5,109,0,0,100,101,5,97,0,0,
  	101,102,5,75,0,0,102,103,5,101,0,0,103,104,5,121,0,0,104,16,1,0,0,0,105,
  	106,5,116,0,0,106,107,5,105,0,0,107,108,5,110,0,0,108,109,5,116,0,0,109,
  	18,1,0,0,0,110,114,3,21,10,0,111,114,3,23,11,0,112,114,3,37,18,0,113,
  	110,1,0,0,0,113,111,1,0,0,0,113,112,1,0,0,0,114,20,1,0,0,0,115,117,3,
  	39,19,0,116,115,1,0,0,0,116,117,1,0,0,0,117,118,1,0,0,0,118,122,3,31,
  	15,0,119,121,3,33,16,0,120,119,1,0,0,0,121,124,1,0,0,0,122,120,1,0,0,
  	0,122,123,1,0,0,0,123,22,1,0,0,0,124,122,1,0,0,0,125,127,3,39,19,0,126,
  	125,1,0,0,0,126,127,1,0,0,0,127,128,1,0,0,0,128,130,3,25,12,0,129,131,
  	3,35,17,0,130,129,1,0,0,0,131,132,1,0,0,0,132,130,1,0,0,0,132,133,1,0,
  	0,0,133,24,1,0,0,0,134,135,5,48,0,0,135,136,7,0,0,0,136,26,1,0,0,0,137,
  	139,3,29,14,0,138,137,1,0,0,0,138,139,1,0,0,0,139,140,1,0,0,0,140,141,
  	5,46,0,0,141,146,3,29,14,0,142,143,3,29,14,0,143,144,5,46,0,0,144,146,
  	1,0,0,0,145,138,1,0,0,0,145,142,1,0,0,0,146,28,1,0,0,0,147,149,3,33,16,
  	0,148,147,1,0,0,0,149,150,1,0,0,0,150,148,1,0,0,0,150,151,1,0,0,0,151,
  	30,1,0,0,0,152,153,7,1,0,0,153,32,1,0,0,0,154,155,7,2,0,0,155,34,1,0,
  	0,0,156,157,7,3,0,0,157,36,1,0,0,0,158,160,3,39,19,0,159,158,1,0,0,0,
  	159,160,1,0,0,0,160,161,1,0,0,0,161,162,5,48,0,0,162,38,1,0,0,0,163,164,
  	7,4,0,0,164,40,1,0,0,0,165,167,5,34,0,0,166,168,3,43,21,0,167,166,1,0,
  	0,0,167,168,1,0,0,0,168,169,1,0,0,0,169,170,5,34,0,0,170,42,1,0,0,0,171,
  	173,3,45,22,0,172,171,1,0,0,0,173,174,1,0,0,0,174,172,1,0,0,0,174,175,
  	1,0,0,0,175,44,1,0,0,0,176,184,8,5,0,0,177,184,3,47,23,0,178,179,5,92,
  	0,0,179,184,5,10,0,0,180,181,5,92,0,0,181,182,5,13,0,0,182,184,5,10,0,
  	0,183,176,1,0,0,0,183,177,1,0,0,0,183,178,1,0,0,0,183,180,1,0,0,0,184,
  	46,1,0,0,0,185,186,5,92,0,0,186,187,7,6,0,0,187,48,1,0,0,0,188,190,7,
  	7,0,0,189,188,1,0,0,0,190,191,1,0,0,0,191,189,1,0,0,0,191,192,1,0,0,0,
  	192,193,1,0,0,0,193,194,6,24,0,0,194,50,1,0,0,0,195,197,5,13,0,0,196,
  	198,5,10,0,0,197,196,1,0,0,0,197,198,1,0,0,0,198,201,1,0,0,0,199,201,
  	5,10,0,0,200,195,1,0,0,0,200,199,1,0,0,0,201,202,1,0,0,0,202,203,6,25,
  	0,0,203,52,1,0,0,0,204,205,5,47,0,0,205,206,5,42,0,0,206,210,1,0,0,0,
  	207,209,9,0,0,0,208,207,1,0,0,0,209,212,1,0,0,0,210,211,1,0,0,0,210,208,
  	1,0,0,0,211,213,1,0,0,0,212,210,1,0,0,0,213,214,5,42,0,0,214,215,5,47,
  	0,0,215,216,1,0,0,0,216,217,6,26,0,0,217,54,1,0,0,0,218,219,5,47,0,0,
  	219,220,5,47,0,0,220,224,1,0,0,0,221,223,8,8,0,0,222,221,1,0,0,0,223,
  	226,1,0,0,0,224,222,1,0,0,0,224,225,1,0,0,0,225,227,1,0,0,0,226,224,1,
  	0,0,0,227,228,6,27,0,0,228,56,1,0,0,0,18,0,113,116,122,126,132,138,145,
  	150,159,167,174,183,191,197,200,210,224,1,6,0,0
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
