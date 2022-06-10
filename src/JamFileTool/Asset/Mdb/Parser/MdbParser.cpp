
// Generated from ..\..\..\src\JamFileTool\Asset\Mdb\Mdb.g4 by ANTLR 4.10.1


#include "MdbListener.h"

#include "MdbParser.h"


using namespace antlrcpp;
using namespace mdb;

using namespace antlr4;

namespace {

struct MdbParserStaticData final {
  MdbParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  MdbParserStaticData(const MdbParserStaticData&) = delete;
  MdbParserStaticData(MdbParserStaticData&&) = delete;
  MdbParserStaticData& operator=(const MdbParserStaticData&) = delete;
  MdbParserStaticData& operator=(MdbParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag mdbParserOnceFlag;
MdbParserStaticData *mdbParserStaticData = nullptr;

void mdbParserInitialize() {
  assert(mdbParserStaticData == nullptr);
  auto staticData = std::make_unique<MdbParserStaticData>(
    std::vector<std::string>{
      "r"
    },
    std::vector<std::string>{
      "", "'hello'"
    },
    std::vector<std::string>{
      "", "", "ID", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,3,6,2,0,7,0,1,0,1,0,1,0,1,0,0,0,1,0,0,0,4,0,2,1,0,0,0,2,3,5,1,0,0,
  	3,4,5,2,0,0,4,1,1,0,0,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  mdbParserStaticData = staticData.release();
}

}

MdbParser::MdbParser(TokenStream *input) : MdbParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

MdbParser::MdbParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  MdbParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *mdbParserStaticData->atn, mdbParserStaticData->decisionToDFA, mdbParserStaticData->sharedContextCache, options);
}

MdbParser::~MdbParser() {
  delete _interpreter;
}

const atn::ATN& MdbParser::getATN() const {
  return *mdbParserStaticData->atn;
}

std::string MdbParser::getGrammarFileName() const {
  return "Mdb.g4";
}

const std::vector<std::string>& MdbParser::getRuleNames() const {
  return mdbParserStaticData->ruleNames;
}

const dfa::Vocabulary& MdbParser::getVocabulary() const {
  return mdbParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView MdbParser::getSerializedATN() const {
  return mdbParserStaticData->serializedATN;
}


//----------------- RContext ------------------------------------------------------------------

MdbParser::RContext::RContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MdbParser::RContext::ID() {
  return getToken(MdbParser::ID, 0);
}


size_t MdbParser::RContext::getRuleIndex() const {
  return MdbParser::RuleR;
}

void MdbParser::RContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterR(this);
}

void MdbParser::RContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitR(this);
}

MdbParser::RContext* MdbParser::r() {
  RContext *_localctx = _tracker.createInstance<RContext>(_ctx, getState());
  enterRule(_localctx, 0, MdbParser::RuleR);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(2);
    match(MdbParser::T__0);
    setState(3);
    match(MdbParser::ID);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void MdbParser::initialize() {
  std::call_once(mdbParserOnceFlag, mdbParserInitialize);
}
