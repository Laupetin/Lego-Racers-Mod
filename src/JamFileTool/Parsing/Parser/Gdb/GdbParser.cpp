
// Generated from ..\..\..\src\JamFileTool\Parsing\Parser\Gdb\Gdb.g4 by ANTLR 4.10.1


#include "GdbListener.h"

#include "GdbParser.h"


using namespace antlrcpp;
using namespace gdb;

using namespace antlr4;

namespace {

struct GdbParserStaticData final {
  GdbParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  GdbParserStaticData(const GdbParserStaticData&) = delete;
  GdbParserStaticData(GdbParserStaticData&&) = delete;
  GdbParserStaticData& operator=(const GdbParserStaticData&) = delete;
  GdbParserStaticData& operator=(GdbParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag gdbParserOnceFlag;
GdbParserStaticData *gdbParserStaticData = nullptr;

void gdbParserInitialize() {
  assert(gdbParserStaticData == nullptr);
  auto staticData = std::make_unique<GdbParserStaticData>(
    std::vector<std::string>{
      "root", "sections", "materialSection", "materialNameList", "materialName", 
      "scaleSection", "vertexSection", "vertexList", "vertexDefPosition", 
      "vertexDefPositionUv", "vertexDefPositionUvColor", "vertexDefPositionUvNormal", 
      "vertexPosition", "vertexUv", "vertexColor", "vertexNormal", "faceSection", 
      "faceList", "face", "metaSection", "metaList", "meta", "keyword31", 
      "keyword2D", "keyword2F", "keyword30", "keyword32", "keyword27", "floatOrIntConstant"
    },
    std::vector<std::string>{
      "", "'{'", "'}'", "'materials'", "'scale'", "'vertices'", "'faces'", 
      "'meta'", "'v'", "'uv'", "'clr'", "'vn'", "'texture'", "'f'", "'keyword27'", 
      "'keyword2D'", "'keyword2F'", "'keyword30'", "'keyword31'", "'keyword32'"
    },
    std::vector<std::string>{
      "", "", "", "Materials", "Scale", "Vertices", "Faces", "Meta", "Vertex", 
      "Uv", "Color", "Normal", "Texture", "Face", "Keyword27", "Keyword2D", 
      "Keyword2F", "Keyword30", "Keyword31", "Keyword32", "IntegerConstant", 
      "FloatingConstant", "DigitSequence", "StringLiteral", "Whitespace", 
      "Newline", "BlockComment", "LineComment"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,27,208,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,1,0,1,0,1,1,1,1,3,1,63,8,1,1,1,1,1,1,1,3,1,68,8,1,1,2,1,2,1,2,3,2,
  	73,8,2,1,2,1,2,1,3,4,3,78,8,3,11,3,12,3,79,1,4,1,4,1,5,1,5,1,5,1,6,1,
  	6,1,6,3,6,90,8,6,1,6,1,6,1,7,4,7,95,8,7,11,7,12,7,96,1,7,4,7,100,8,7,
  	11,7,12,7,101,1,7,4,7,105,8,7,11,7,12,7,106,1,7,4,7,110,8,7,11,7,12,7,
  	111,3,7,114,8,7,1,8,1,8,1,9,1,9,1,9,1,10,1,10,1,10,1,10,1,11,1,11,1,11,
  	1,11,1,12,1,12,1,12,1,12,1,12,1,13,1,13,1,13,1,13,1,14,1,14,1,14,1,14,
  	1,14,1,14,1,15,1,15,1,15,1,15,1,15,1,16,1,16,1,16,3,16,152,8,16,1,16,
  	1,16,1,17,4,17,157,8,17,11,17,12,17,158,1,18,1,18,1,18,1,18,1,18,1,19,
  	1,19,1,19,3,19,169,8,19,1,19,1,19,1,20,4,20,174,8,20,11,20,12,20,175,
  	1,21,1,21,1,21,1,21,1,21,1,21,3,21,184,8,21,1,22,1,22,1,22,1,22,1,22,
  	1,23,1,23,1,23,1,23,1,24,1,24,1,24,1,25,1,25,1,26,1,26,1,26,1,27,1,27,
  	1,27,1,28,1,28,1,28,0,0,29,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,
  	32,34,36,38,40,42,44,46,48,50,52,54,56,0,1,1,0,20,21,199,0,58,1,0,0,0,
  	2,60,1,0,0,0,4,69,1,0,0,0,6,77,1,0,0,0,8,81,1,0,0,0,10,83,1,0,0,0,12,
  	86,1,0,0,0,14,113,1,0,0,0,16,115,1,0,0,0,18,117,1,0,0,0,20,120,1,0,0,
  	0,22,124,1,0,0,0,24,128,1,0,0,0,26,133,1,0,0,0,28,137,1,0,0,0,30,143,
  	1,0,0,0,32,148,1,0,0,0,34,156,1,0,0,0,36,160,1,0,0,0,38,165,1,0,0,0,40,
  	173,1,0,0,0,42,183,1,0,0,0,44,185,1,0,0,0,46,190,1,0,0,0,48,194,1,0,0,
  	0,50,197,1,0,0,0,52,199,1,0,0,0,54,202,1,0,0,0,56,205,1,0,0,0,58,59,3,
  	2,1,0,59,1,1,0,0,0,60,62,3,4,2,0,61,63,3,10,5,0,62,61,1,0,0,0,62,63,1,
  	0,0,0,63,64,1,0,0,0,64,65,3,12,6,0,65,67,3,32,16,0,66,68,3,38,19,0,67,
  	66,1,0,0,0,67,68,1,0,0,0,68,3,1,0,0,0,69,70,5,3,0,0,70,72,5,1,0,0,71,
  	73,3,6,3,0,72,71,1,0,0,0,72,73,1,0,0,0,73,74,1,0,0,0,74,75,5,2,0,0,75,
  	5,1,0,0,0,76,78,3,8,4,0,77,76,1,0,0,0,78,79,1,0,0,0,79,77,1,0,0,0,79,
  	80,1,0,0,0,80,7,1,0,0,0,81,82,5,23,0,0,82,9,1,0,0,0,83,84,5,4,0,0,84,
  	85,3,56,28,0,85,11,1,0,0,0,86,87,5,5,0,0,87,89,5,1,0,0,88,90,3,14,7,0,
  	89,88,1,0,0,0,89,90,1,0,0,0,90,91,1,0,0,0,91,92,5,2,0,0,92,13,1,0,0,0,
  	93,95,3,20,10,0,94,93,1,0,0,0,95,96,1,0,0,0,96,94,1,0,0,0,96,97,1,0,0,
  	0,97,114,1,0,0,0,98,100,3,22,11,0,99,98,1,0,0,0,100,101,1,0,0,0,101,99,
  	1,0,0,0,101,102,1,0,0,0,102,114,1,0,0,0,103,105,3,18,9,0,104,103,1,0,
  	0,0,105,106,1,0,0,0,106,104,1,0,0,0,106,107,1,0,0,0,107,114,1,0,0,0,108,
  	110,3,16,8,0,109,108,1,0,0,0,110,111,1,0,0,0,111,109,1,0,0,0,111,112,
  	1,0,0,0,112,114,1,0,0,0,113,94,1,0,0,0,113,99,1,0,0,0,113,104,1,0,0,0,
  	113,109,1,0,0,0,114,15,1,0,0,0,115,116,3,24,12,0,116,17,1,0,0,0,117,118,
  	3,24,12,0,118,119,3,26,13,0,119,19,1,0,0,0,120,121,3,24,12,0,121,122,
  	3,26,13,0,122,123,3,28,14,0,123,21,1,0,0,0,124,125,3,24,12,0,125,126,
  	3,26,13,0,126,127,3,30,15,0,127,23,1,0,0,0,128,129,5,8,0,0,129,130,3,
  	56,28,0,130,131,3,56,28,0,131,132,3,56,28,0,132,25,1,0,0,0,133,134,5,
  	9,0,0,134,135,3,56,28,0,135,136,3,56,28,0,136,27,1,0,0,0,137,138,5,10,
  	0,0,138,139,5,20,0,0,139,140,5,20,0,0,140,141,5,20,0,0,141,142,5,20,0,
  	0,142,29,1,0,0,0,143,144,5,11,0,0,144,145,3,56,28,0,145,146,3,56,28,0,
  	146,147,3,56,28,0,147,31,1,0,0,0,148,149,5,6,0,0,149,151,5,1,0,0,150,
  	152,3,34,17,0,151,150,1,0,0,0,151,152,1,0,0,0,152,153,1,0,0,0,153,154,
  	5,2,0,0,154,33,1,0,0,0,155,157,3,36,18,0,156,155,1,0,0,0,157,158,1,0,
  	0,0,158,156,1,0,0,0,158,159,1,0,0,0,159,35,1,0,0,0,160,161,5,13,0,0,161,
  	162,5,20,0,0,162,163,5,20,0,0,163,164,5,20,0,0,164,37,1,0,0,0,165,166,
  	5,7,0,0,166,168,5,1,0,0,167,169,3,40,20,0,168,167,1,0,0,0,168,169,1,0,
  	0,0,169,170,1,0,0,0,170,171,5,2,0,0,171,39,1,0,0,0,172,174,3,42,21,0,
  	173,172,1,0,0,0,174,175,1,0,0,0,175,173,1,0,0,0,175,176,1,0,0,0,176,41,
  	1,0,0,0,177,184,3,44,22,0,178,184,3,46,23,0,179,184,3,48,24,0,180,184,
  	3,50,25,0,181,184,3,52,26,0,182,184,3,54,27,0,183,177,1,0,0,0,183,178,
  	1,0,0,0,183,179,1,0,0,0,183,180,1,0,0,0,183,181,1,0,0,0,183,182,1,0,0,
  	0,184,43,1,0,0,0,185,186,5,18,0,0,186,187,5,20,0,0,187,188,5,20,0,0,188,
  	189,5,20,0,0,189,45,1,0,0,0,190,191,5,15,0,0,191,192,5,20,0,0,192,193,
  	5,20,0,0,193,47,1,0,0,0,194,195,5,16,0,0,195,196,5,20,0,0,196,49,1,0,
  	0,0,197,198,5,17,0,0,198,51,1,0,0,0,199,200,5,19,0,0,200,201,5,20,0,0,
  	201,53,1,0,0,0,202,203,5,14,0,0,203,204,5,20,0,0,204,55,1,0,0,0,205,206,
  	7,0,0,0,206,57,1,0,0,0,15,62,67,72,79,89,96,101,106,111,113,151,158,168,
  	175,183
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  gdbParserStaticData = staticData.release();
}

}

GdbParser::GdbParser(TokenStream *input) : GdbParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

GdbParser::GdbParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  GdbParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *gdbParserStaticData->atn, gdbParserStaticData->decisionToDFA, gdbParserStaticData->sharedContextCache, options);
}

GdbParser::~GdbParser() {
  delete _interpreter;
}

const atn::ATN& GdbParser::getATN() const {
  return *gdbParserStaticData->atn;
}

std::string GdbParser::getGrammarFileName() const {
  return "Gdb.g4";
}

const std::vector<std::string>& GdbParser::getRuleNames() const {
  return gdbParserStaticData->ruleNames;
}

const dfa::Vocabulary& GdbParser::getVocabulary() const {
  return gdbParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView GdbParser::getSerializedATN() const {
  return gdbParserStaticData->serializedATN;
}


//----------------- RootContext ------------------------------------------------------------------

GdbParser::RootContext::RootContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GdbParser::SectionsContext* GdbParser::RootContext::sections() {
  return getRuleContext<GdbParser::SectionsContext>(0);
}


size_t GdbParser::RootContext::getRuleIndex() const {
  return GdbParser::RuleRoot;
}

void GdbParser::RootContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRoot(this);
}

void GdbParser::RootContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRoot(this);
}

GdbParser::RootContext* GdbParser::root() {
  RootContext *_localctx = _tracker.createInstance<RootContext>(_ctx, getState());
  enterRule(_localctx, 0, GdbParser::RuleRoot);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(58);
    sections();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SectionsContext ------------------------------------------------------------------

GdbParser::SectionsContext::SectionsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GdbParser::MaterialSectionContext* GdbParser::SectionsContext::materialSection() {
  return getRuleContext<GdbParser::MaterialSectionContext>(0);
}

GdbParser::VertexSectionContext* GdbParser::SectionsContext::vertexSection() {
  return getRuleContext<GdbParser::VertexSectionContext>(0);
}

GdbParser::FaceSectionContext* GdbParser::SectionsContext::faceSection() {
  return getRuleContext<GdbParser::FaceSectionContext>(0);
}

GdbParser::ScaleSectionContext* GdbParser::SectionsContext::scaleSection() {
  return getRuleContext<GdbParser::ScaleSectionContext>(0);
}

GdbParser::MetaSectionContext* GdbParser::SectionsContext::metaSection() {
  return getRuleContext<GdbParser::MetaSectionContext>(0);
}


size_t GdbParser::SectionsContext::getRuleIndex() const {
  return GdbParser::RuleSections;
}

void GdbParser::SectionsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSections(this);
}

void GdbParser::SectionsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSections(this);
}

GdbParser::SectionsContext* GdbParser::sections() {
  SectionsContext *_localctx = _tracker.createInstance<SectionsContext>(_ctx, getState());
  enterRule(_localctx, 2, GdbParser::RuleSections);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(60);
    materialSection();
    setState(62);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == GdbParser::Scale) {
      setState(61);
      scaleSection();
    }
    setState(64);
    vertexSection();
    setState(65);
    faceSection();
    setState(67);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == GdbParser::Meta) {
      setState(66);
      metaSection();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MaterialSectionContext ------------------------------------------------------------------

GdbParser::MaterialSectionContext::MaterialSectionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GdbParser::MaterialSectionContext::Materials() {
  return getToken(GdbParser::Materials, 0);
}

GdbParser::MaterialNameListContext* GdbParser::MaterialSectionContext::materialNameList() {
  return getRuleContext<GdbParser::MaterialNameListContext>(0);
}


size_t GdbParser::MaterialSectionContext::getRuleIndex() const {
  return GdbParser::RuleMaterialSection;
}

void GdbParser::MaterialSectionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMaterialSection(this);
}

void GdbParser::MaterialSectionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMaterialSection(this);
}

GdbParser::MaterialSectionContext* GdbParser::materialSection() {
  MaterialSectionContext *_localctx = _tracker.createInstance<MaterialSectionContext>(_ctx, getState());
  enterRule(_localctx, 4, GdbParser::RuleMaterialSection);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(69);
    match(GdbParser::Materials);
    setState(70);
    match(GdbParser::T__0);
    setState(72);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == GdbParser::StringLiteral) {
      setState(71);
      materialNameList();
    }
    setState(74);
    match(GdbParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MaterialNameListContext ------------------------------------------------------------------

GdbParser::MaterialNameListContext::MaterialNameListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<GdbParser::MaterialNameContext *> GdbParser::MaterialNameListContext::materialName() {
  return getRuleContexts<GdbParser::MaterialNameContext>();
}

GdbParser::MaterialNameContext* GdbParser::MaterialNameListContext::materialName(size_t i) {
  return getRuleContext<GdbParser::MaterialNameContext>(i);
}


size_t GdbParser::MaterialNameListContext::getRuleIndex() const {
  return GdbParser::RuleMaterialNameList;
}

void GdbParser::MaterialNameListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMaterialNameList(this);
}

void GdbParser::MaterialNameListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMaterialNameList(this);
}

GdbParser::MaterialNameListContext* GdbParser::materialNameList() {
  MaterialNameListContext *_localctx = _tracker.createInstance<MaterialNameListContext>(_ctx, getState());
  enterRule(_localctx, 6, GdbParser::RuleMaterialNameList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(77); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(76);
      materialName();
      setState(79); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == GdbParser::StringLiteral);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MaterialNameContext ------------------------------------------------------------------

GdbParser::MaterialNameContext::MaterialNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GdbParser::MaterialNameContext::StringLiteral() {
  return getToken(GdbParser::StringLiteral, 0);
}


size_t GdbParser::MaterialNameContext::getRuleIndex() const {
  return GdbParser::RuleMaterialName;
}

void GdbParser::MaterialNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMaterialName(this);
}

void GdbParser::MaterialNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMaterialName(this);
}

GdbParser::MaterialNameContext* GdbParser::materialName() {
  MaterialNameContext *_localctx = _tracker.createInstance<MaterialNameContext>(_ctx, getState());
  enterRule(_localctx, 8, GdbParser::RuleMaterialName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(81);
    match(GdbParser::StringLiteral);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ScaleSectionContext ------------------------------------------------------------------

GdbParser::ScaleSectionContext::ScaleSectionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GdbParser::ScaleSectionContext::Scale() {
  return getToken(GdbParser::Scale, 0);
}

GdbParser::FloatOrIntConstantContext* GdbParser::ScaleSectionContext::floatOrIntConstant() {
  return getRuleContext<GdbParser::FloatOrIntConstantContext>(0);
}


size_t GdbParser::ScaleSectionContext::getRuleIndex() const {
  return GdbParser::RuleScaleSection;
}

void GdbParser::ScaleSectionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterScaleSection(this);
}

void GdbParser::ScaleSectionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitScaleSection(this);
}

GdbParser::ScaleSectionContext* GdbParser::scaleSection() {
  ScaleSectionContext *_localctx = _tracker.createInstance<ScaleSectionContext>(_ctx, getState());
  enterRule(_localctx, 10, GdbParser::RuleScaleSection);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(83);
    match(GdbParser::Scale);
    setState(84);
    floatOrIntConstant();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VertexSectionContext ------------------------------------------------------------------

GdbParser::VertexSectionContext::VertexSectionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GdbParser::VertexSectionContext::Vertices() {
  return getToken(GdbParser::Vertices, 0);
}

GdbParser::VertexListContext* GdbParser::VertexSectionContext::vertexList() {
  return getRuleContext<GdbParser::VertexListContext>(0);
}


size_t GdbParser::VertexSectionContext::getRuleIndex() const {
  return GdbParser::RuleVertexSection;
}

void GdbParser::VertexSectionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVertexSection(this);
}

void GdbParser::VertexSectionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVertexSection(this);
}

GdbParser::VertexSectionContext* GdbParser::vertexSection() {
  VertexSectionContext *_localctx = _tracker.createInstance<VertexSectionContext>(_ctx, getState());
  enterRule(_localctx, 12, GdbParser::RuleVertexSection);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(86);
    match(GdbParser::Vertices);
    setState(87);
    match(GdbParser::T__0);
    setState(89);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == GdbParser::Vertex) {
      setState(88);
      vertexList();
    }
    setState(91);
    match(GdbParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VertexListContext ------------------------------------------------------------------

GdbParser::VertexListContext::VertexListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<GdbParser::VertexDefPositionUvColorContext *> GdbParser::VertexListContext::vertexDefPositionUvColor() {
  return getRuleContexts<GdbParser::VertexDefPositionUvColorContext>();
}

GdbParser::VertexDefPositionUvColorContext* GdbParser::VertexListContext::vertexDefPositionUvColor(size_t i) {
  return getRuleContext<GdbParser::VertexDefPositionUvColorContext>(i);
}

std::vector<GdbParser::VertexDefPositionUvNormalContext *> GdbParser::VertexListContext::vertexDefPositionUvNormal() {
  return getRuleContexts<GdbParser::VertexDefPositionUvNormalContext>();
}

GdbParser::VertexDefPositionUvNormalContext* GdbParser::VertexListContext::vertexDefPositionUvNormal(size_t i) {
  return getRuleContext<GdbParser::VertexDefPositionUvNormalContext>(i);
}

std::vector<GdbParser::VertexDefPositionUvContext *> GdbParser::VertexListContext::vertexDefPositionUv() {
  return getRuleContexts<GdbParser::VertexDefPositionUvContext>();
}

GdbParser::VertexDefPositionUvContext* GdbParser::VertexListContext::vertexDefPositionUv(size_t i) {
  return getRuleContext<GdbParser::VertexDefPositionUvContext>(i);
}

std::vector<GdbParser::VertexDefPositionContext *> GdbParser::VertexListContext::vertexDefPosition() {
  return getRuleContexts<GdbParser::VertexDefPositionContext>();
}

GdbParser::VertexDefPositionContext* GdbParser::VertexListContext::vertexDefPosition(size_t i) {
  return getRuleContext<GdbParser::VertexDefPositionContext>(i);
}


size_t GdbParser::VertexListContext::getRuleIndex() const {
  return GdbParser::RuleVertexList;
}

void GdbParser::VertexListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVertexList(this);
}

void GdbParser::VertexListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVertexList(this);
}

GdbParser::VertexListContext* GdbParser::vertexList() {
  VertexListContext *_localctx = _tracker.createInstance<VertexListContext>(_ctx, getState());
  enterRule(_localctx, 14, GdbParser::RuleVertexList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(113);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(94); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(93);
        vertexDefPositionUvColor();
        setState(96); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == GdbParser::Vertex);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(99); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(98);
        vertexDefPositionUvNormal();
        setState(101); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == GdbParser::Vertex);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(104); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(103);
        vertexDefPositionUv();
        setState(106); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == GdbParser::Vertex);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(109); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(108);
        vertexDefPosition();
        setState(111); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == GdbParser::Vertex);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VertexDefPositionContext ------------------------------------------------------------------

GdbParser::VertexDefPositionContext::VertexDefPositionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GdbParser::VertexPositionContext* GdbParser::VertexDefPositionContext::vertexPosition() {
  return getRuleContext<GdbParser::VertexPositionContext>(0);
}


size_t GdbParser::VertexDefPositionContext::getRuleIndex() const {
  return GdbParser::RuleVertexDefPosition;
}

void GdbParser::VertexDefPositionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVertexDefPosition(this);
}

void GdbParser::VertexDefPositionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVertexDefPosition(this);
}

GdbParser::VertexDefPositionContext* GdbParser::vertexDefPosition() {
  VertexDefPositionContext *_localctx = _tracker.createInstance<VertexDefPositionContext>(_ctx, getState());
  enterRule(_localctx, 16, GdbParser::RuleVertexDefPosition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(115);
    vertexPosition();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VertexDefPositionUvContext ------------------------------------------------------------------

GdbParser::VertexDefPositionUvContext::VertexDefPositionUvContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GdbParser::VertexPositionContext* GdbParser::VertexDefPositionUvContext::vertexPosition() {
  return getRuleContext<GdbParser::VertexPositionContext>(0);
}

GdbParser::VertexUvContext* GdbParser::VertexDefPositionUvContext::vertexUv() {
  return getRuleContext<GdbParser::VertexUvContext>(0);
}


size_t GdbParser::VertexDefPositionUvContext::getRuleIndex() const {
  return GdbParser::RuleVertexDefPositionUv;
}

void GdbParser::VertexDefPositionUvContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVertexDefPositionUv(this);
}

void GdbParser::VertexDefPositionUvContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVertexDefPositionUv(this);
}

GdbParser::VertexDefPositionUvContext* GdbParser::vertexDefPositionUv() {
  VertexDefPositionUvContext *_localctx = _tracker.createInstance<VertexDefPositionUvContext>(_ctx, getState());
  enterRule(_localctx, 18, GdbParser::RuleVertexDefPositionUv);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(117);
    vertexPosition();
    setState(118);
    vertexUv();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VertexDefPositionUvColorContext ------------------------------------------------------------------

GdbParser::VertexDefPositionUvColorContext::VertexDefPositionUvColorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GdbParser::VertexPositionContext* GdbParser::VertexDefPositionUvColorContext::vertexPosition() {
  return getRuleContext<GdbParser::VertexPositionContext>(0);
}

GdbParser::VertexUvContext* GdbParser::VertexDefPositionUvColorContext::vertexUv() {
  return getRuleContext<GdbParser::VertexUvContext>(0);
}

GdbParser::VertexColorContext* GdbParser::VertexDefPositionUvColorContext::vertexColor() {
  return getRuleContext<GdbParser::VertexColorContext>(0);
}


size_t GdbParser::VertexDefPositionUvColorContext::getRuleIndex() const {
  return GdbParser::RuleVertexDefPositionUvColor;
}

void GdbParser::VertexDefPositionUvColorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVertexDefPositionUvColor(this);
}

void GdbParser::VertexDefPositionUvColorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVertexDefPositionUvColor(this);
}

GdbParser::VertexDefPositionUvColorContext* GdbParser::vertexDefPositionUvColor() {
  VertexDefPositionUvColorContext *_localctx = _tracker.createInstance<VertexDefPositionUvColorContext>(_ctx, getState());
  enterRule(_localctx, 20, GdbParser::RuleVertexDefPositionUvColor);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(120);
    vertexPosition();
    setState(121);
    vertexUv();
    setState(122);
    vertexColor();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VertexDefPositionUvNormalContext ------------------------------------------------------------------

GdbParser::VertexDefPositionUvNormalContext::VertexDefPositionUvNormalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GdbParser::VertexPositionContext* GdbParser::VertexDefPositionUvNormalContext::vertexPosition() {
  return getRuleContext<GdbParser::VertexPositionContext>(0);
}

GdbParser::VertexUvContext* GdbParser::VertexDefPositionUvNormalContext::vertexUv() {
  return getRuleContext<GdbParser::VertexUvContext>(0);
}

GdbParser::VertexNormalContext* GdbParser::VertexDefPositionUvNormalContext::vertexNormal() {
  return getRuleContext<GdbParser::VertexNormalContext>(0);
}


size_t GdbParser::VertexDefPositionUvNormalContext::getRuleIndex() const {
  return GdbParser::RuleVertexDefPositionUvNormal;
}

void GdbParser::VertexDefPositionUvNormalContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVertexDefPositionUvNormal(this);
}

void GdbParser::VertexDefPositionUvNormalContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVertexDefPositionUvNormal(this);
}

GdbParser::VertexDefPositionUvNormalContext* GdbParser::vertexDefPositionUvNormal() {
  VertexDefPositionUvNormalContext *_localctx = _tracker.createInstance<VertexDefPositionUvNormalContext>(_ctx, getState());
  enterRule(_localctx, 22, GdbParser::RuleVertexDefPositionUvNormal);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(124);
    vertexPosition();
    setState(125);
    vertexUv();
    setState(126);
    vertexNormal();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VertexPositionContext ------------------------------------------------------------------

GdbParser::VertexPositionContext::VertexPositionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GdbParser::VertexPositionContext::Vertex() {
  return getToken(GdbParser::Vertex, 0);
}

std::vector<GdbParser::FloatOrIntConstantContext *> GdbParser::VertexPositionContext::floatOrIntConstant() {
  return getRuleContexts<GdbParser::FloatOrIntConstantContext>();
}

GdbParser::FloatOrIntConstantContext* GdbParser::VertexPositionContext::floatOrIntConstant(size_t i) {
  return getRuleContext<GdbParser::FloatOrIntConstantContext>(i);
}


size_t GdbParser::VertexPositionContext::getRuleIndex() const {
  return GdbParser::RuleVertexPosition;
}

void GdbParser::VertexPositionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVertexPosition(this);
}

void GdbParser::VertexPositionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVertexPosition(this);
}

GdbParser::VertexPositionContext* GdbParser::vertexPosition() {
  VertexPositionContext *_localctx = _tracker.createInstance<VertexPositionContext>(_ctx, getState());
  enterRule(_localctx, 24, GdbParser::RuleVertexPosition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(128);
    match(GdbParser::Vertex);
    setState(129);
    floatOrIntConstant();
    setState(130);
    floatOrIntConstant();
    setState(131);
    floatOrIntConstant();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VertexUvContext ------------------------------------------------------------------

GdbParser::VertexUvContext::VertexUvContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GdbParser::VertexUvContext::Uv() {
  return getToken(GdbParser::Uv, 0);
}

std::vector<GdbParser::FloatOrIntConstantContext *> GdbParser::VertexUvContext::floatOrIntConstant() {
  return getRuleContexts<GdbParser::FloatOrIntConstantContext>();
}

GdbParser::FloatOrIntConstantContext* GdbParser::VertexUvContext::floatOrIntConstant(size_t i) {
  return getRuleContext<GdbParser::FloatOrIntConstantContext>(i);
}


size_t GdbParser::VertexUvContext::getRuleIndex() const {
  return GdbParser::RuleVertexUv;
}

void GdbParser::VertexUvContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVertexUv(this);
}

void GdbParser::VertexUvContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVertexUv(this);
}

GdbParser::VertexUvContext* GdbParser::vertexUv() {
  VertexUvContext *_localctx = _tracker.createInstance<VertexUvContext>(_ctx, getState());
  enterRule(_localctx, 26, GdbParser::RuleVertexUv);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(133);
    match(GdbParser::Uv);
    setState(134);
    floatOrIntConstant();
    setState(135);
    floatOrIntConstant();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VertexColorContext ------------------------------------------------------------------

GdbParser::VertexColorContext::VertexColorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GdbParser::VertexColorContext::Color() {
  return getToken(GdbParser::Color, 0);
}

std::vector<tree::TerminalNode *> GdbParser::VertexColorContext::IntegerConstant() {
  return getTokens(GdbParser::IntegerConstant);
}

tree::TerminalNode* GdbParser::VertexColorContext::IntegerConstant(size_t i) {
  return getToken(GdbParser::IntegerConstant, i);
}


size_t GdbParser::VertexColorContext::getRuleIndex() const {
  return GdbParser::RuleVertexColor;
}

void GdbParser::VertexColorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVertexColor(this);
}

void GdbParser::VertexColorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVertexColor(this);
}

GdbParser::VertexColorContext* GdbParser::vertexColor() {
  VertexColorContext *_localctx = _tracker.createInstance<VertexColorContext>(_ctx, getState());
  enterRule(_localctx, 28, GdbParser::RuleVertexColor);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(137);
    match(GdbParser::Color);
    setState(138);
    match(GdbParser::IntegerConstant);
    setState(139);
    match(GdbParser::IntegerConstant);
    setState(140);
    match(GdbParser::IntegerConstant);
    setState(141);
    match(GdbParser::IntegerConstant);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VertexNormalContext ------------------------------------------------------------------

GdbParser::VertexNormalContext::VertexNormalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GdbParser::VertexNormalContext::Normal() {
  return getToken(GdbParser::Normal, 0);
}

std::vector<GdbParser::FloatOrIntConstantContext *> GdbParser::VertexNormalContext::floatOrIntConstant() {
  return getRuleContexts<GdbParser::FloatOrIntConstantContext>();
}

GdbParser::FloatOrIntConstantContext* GdbParser::VertexNormalContext::floatOrIntConstant(size_t i) {
  return getRuleContext<GdbParser::FloatOrIntConstantContext>(i);
}


size_t GdbParser::VertexNormalContext::getRuleIndex() const {
  return GdbParser::RuleVertexNormal;
}

void GdbParser::VertexNormalContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVertexNormal(this);
}

void GdbParser::VertexNormalContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVertexNormal(this);
}

GdbParser::VertexNormalContext* GdbParser::vertexNormal() {
  VertexNormalContext *_localctx = _tracker.createInstance<VertexNormalContext>(_ctx, getState());
  enterRule(_localctx, 30, GdbParser::RuleVertexNormal);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(143);
    match(GdbParser::Normal);
    setState(144);
    floatOrIntConstant();
    setState(145);
    floatOrIntConstant();
    setState(146);
    floatOrIntConstant();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FaceSectionContext ------------------------------------------------------------------

GdbParser::FaceSectionContext::FaceSectionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GdbParser::FaceSectionContext::Faces() {
  return getToken(GdbParser::Faces, 0);
}

GdbParser::FaceListContext* GdbParser::FaceSectionContext::faceList() {
  return getRuleContext<GdbParser::FaceListContext>(0);
}


size_t GdbParser::FaceSectionContext::getRuleIndex() const {
  return GdbParser::RuleFaceSection;
}

void GdbParser::FaceSectionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFaceSection(this);
}

void GdbParser::FaceSectionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFaceSection(this);
}

GdbParser::FaceSectionContext* GdbParser::faceSection() {
  FaceSectionContext *_localctx = _tracker.createInstance<FaceSectionContext>(_ctx, getState());
  enterRule(_localctx, 32, GdbParser::RuleFaceSection);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(148);
    match(GdbParser::Faces);
    setState(149);
    match(GdbParser::T__0);
    setState(151);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == GdbParser::Face) {
      setState(150);
      faceList();
    }
    setState(153);
    match(GdbParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FaceListContext ------------------------------------------------------------------

GdbParser::FaceListContext::FaceListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<GdbParser::FaceContext *> GdbParser::FaceListContext::face() {
  return getRuleContexts<GdbParser::FaceContext>();
}

GdbParser::FaceContext* GdbParser::FaceListContext::face(size_t i) {
  return getRuleContext<GdbParser::FaceContext>(i);
}


size_t GdbParser::FaceListContext::getRuleIndex() const {
  return GdbParser::RuleFaceList;
}

void GdbParser::FaceListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFaceList(this);
}

void GdbParser::FaceListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFaceList(this);
}

GdbParser::FaceListContext* GdbParser::faceList() {
  FaceListContext *_localctx = _tracker.createInstance<FaceListContext>(_ctx, getState());
  enterRule(_localctx, 34, GdbParser::RuleFaceList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(156); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(155);
      face();
      setState(158); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == GdbParser::Face);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FaceContext ------------------------------------------------------------------

GdbParser::FaceContext::FaceContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GdbParser::FaceContext::Face() {
  return getToken(GdbParser::Face, 0);
}

std::vector<tree::TerminalNode *> GdbParser::FaceContext::IntegerConstant() {
  return getTokens(GdbParser::IntegerConstant);
}

tree::TerminalNode* GdbParser::FaceContext::IntegerConstant(size_t i) {
  return getToken(GdbParser::IntegerConstant, i);
}


size_t GdbParser::FaceContext::getRuleIndex() const {
  return GdbParser::RuleFace;
}

void GdbParser::FaceContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFace(this);
}

void GdbParser::FaceContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFace(this);
}

GdbParser::FaceContext* GdbParser::face() {
  FaceContext *_localctx = _tracker.createInstance<FaceContext>(_ctx, getState());
  enterRule(_localctx, 36, GdbParser::RuleFace);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(160);
    match(GdbParser::Face);
    setState(161);
    match(GdbParser::IntegerConstant);
    setState(162);
    match(GdbParser::IntegerConstant);
    setState(163);
    match(GdbParser::IntegerConstant);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MetaSectionContext ------------------------------------------------------------------

GdbParser::MetaSectionContext::MetaSectionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GdbParser::MetaSectionContext::Meta() {
  return getToken(GdbParser::Meta, 0);
}

GdbParser::MetaListContext* GdbParser::MetaSectionContext::metaList() {
  return getRuleContext<GdbParser::MetaListContext>(0);
}


size_t GdbParser::MetaSectionContext::getRuleIndex() const {
  return GdbParser::RuleMetaSection;
}

void GdbParser::MetaSectionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMetaSection(this);
}

void GdbParser::MetaSectionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMetaSection(this);
}

GdbParser::MetaSectionContext* GdbParser::metaSection() {
  MetaSectionContext *_localctx = _tracker.createInstance<MetaSectionContext>(_ctx, getState());
  enterRule(_localctx, 38, GdbParser::RuleMetaSection);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(165);
    match(GdbParser::Meta);
    setState(166);
    match(GdbParser::T__0);
    setState(168);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << GdbParser::Keyword27)
      | (1ULL << GdbParser::Keyword2D)
      | (1ULL << GdbParser::Keyword2F)
      | (1ULL << GdbParser::Keyword30)
      | (1ULL << GdbParser::Keyword31)
      | (1ULL << GdbParser::Keyword32))) != 0)) {
      setState(167);
      metaList();
    }
    setState(170);
    match(GdbParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MetaListContext ------------------------------------------------------------------

GdbParser::MetaListContext::MetaListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<GdbParser::MetaContext *> GdbParser::MetaListContext::meta() {
  return getRuleContexts<GdbParser::MetaContext>();
}

GdbParser::MetaContext* GdbParser::MetaListContext::meta(size_t i) {
  return getRuleContext<GdbParser::MetaContext>(i);
}


size_t GdbParser::MetaListContext::getRuleIndex() const {
  return GdbParser::RuleMetaList;
}

void GdbParser::MetaListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMetaList(this);
}

void GdbParser::MetaListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMetaList(this);
}

GdbParser::MetaListContext* GdbParser::metaList() {
  MetaListContext *_localctx = _tracker.createInstance<MetaListContext>(_ctx, getState());
  enterRule(_localctx, 40, GdbParser::RuleMetaList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(173); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(172);
      meta();
      setState(175); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << GdbParser::Keyword27)
      | (1ULL << GdbParser::Keyword2D)
      | (1ULL << GdbParser::Keyword2F)
      | (1ULL << GdbParser::Keyword30)
      | (1ULL << GdbParser::Keyword31)
      | (1ULL << GdbParser::Keyword32))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MetaContext ------------------------------------------------------------------

GdbParser::MetaContext::MetaContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GdbParser::Keyword31Context* GdbParser::MetaContext::keyword31() {
  return getRuleContext<GdbParser::Keyword31Context>(0);
}

GdbParser::Keyword2DContext* GdbParser::MetaContext::keyword2D() {
  return getRuleContext<GdbParser::Keyword2DContext>(0);
}

GdbParser::Keyword2FContext* GdbParser::MetaContext::keyword2F() {
  return getRuleContext<GdbParser::Keyword2FContext>(0);
}

GdbParser::Keyword30Context* GdbParser::MetaContext::keyword30() {
  return getRuleContext<GdbParser::Keyword30Context>(0);
}

GdbParser::Keyword32Context* GdbParser::MetaContext::keyword32() {
  return getRuleContext<GdbParser::Keyword32Context>(0);
}

GdbParser::Keyword27Context* GdbParser::MetaContext::keyword27() {
  return getRuleContext<GdbParser::Keyword27Context>(0);
}


size_t GdbParser::MetaContext::getRuleIndex() const {
  return GdbParser::RuleMeta;
}

void GdbParser::MetaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMeta(this);
}

void GdbParser::MetaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMeta(this);
}

GdbParser::MetaContext* GdbParser::meta() {
  MetaContext *_localctx = _tracker.createInstance<MetaContext>(_ctx, getState());
  enterRule(_localctx, 42, GdbParser::RuleMeta);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(183);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case GdbParser::Keyword31: {
        enterOuterAlt(_localctx, 1);
        setState(177);
        keyword31();
        break;
      }

      case GdbParser::Keyword2D: {
        enterOuterAlt(_localctx, 2);
        setState(178);
        keyword2D();
        break;
      }

      case GdbParser::Keyword2F: {
        enterOuterAlt(_localctx, 3);
        setState(179);
        keyword2F();
        break;
      }

      case GdbParser::Keyword30: {
        enterOuterAlt(_localctx, 4);
        setState(180);
        keyword30();
        break;
      }

      case GdbParser::Keyword32: {
        enterOuterAlt(_localctx, 5);
        setState(181);
        keyword32();
        break;
      }

      case GdbParser::Keyword27: {
        enterOuterAlt(_localctx, 6);
        setState(182);
        keyword27();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Keyword31Context ------------------------------------------------------------------

GdbParser::Keyword31Context::Keyword31Context(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GdbParser::Keyword31Context::Keyword31() {
  return getToken(GdbParser::Keyword31, 0);
}

std::vector<tree::TerminalNode *> GdbParser::Keyword31Context::IntegerConstant() {
  return getTokens(GdbParser::IntegerConstant);
}

tree::TerminalNode* GdbParser::Keyword31Context::IntegerConstant(size_t i) {
  return getToken(GdbParser::IntegerConstant, i);
}


size_t GdbParser::Keyword31Context::getRuleIndex() const {
  return GdbParser::RuleKeyword31;
}

void GdbParser::Keyword31Context::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterKeyword31(this);
}

void GdbParser::Keyword31Context::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitKeyword31(this);
}

GdbParser::Keyword31Context* GdbParser::keyword31() {
  Keyword31Context *_localctx = _tracker.createInstance<Keyword31Context>(_ctx, getState());
  enterRule(_localctx, 44, GdbParser::RuleKeyword31);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(185);
    match(GdbParser::Keyword31);
    setState(186);
    match(GdbParser::IntegerConstant);
    setState(187);
    match(GdbParser::IntegerConstant);
    setState(188);
    match(GdbParser::IntegerConstant);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Keyword2DContext ------------------------------------------------------------------

GdbParser::Keyword2DContext::Keyword2DContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GdbParser::Keyword2DContext::Keyword2D() {
  return getToken(GdbParser::Keyword2D, 0);
}

std::vector<tree::TerminalNode *> GdbParser::Keyword2DContext::IntegerConstant() {
  return getTokens(GdbParser::IntegerConstant);
}

tree::TerminalNode* GdbParser::Keyword2DContext::IntegerConstant(size_t i) {
  return getToken(GdbParser::IntegerConstant, i);
}


size_t GdbParser::Keyword2DContext::getRuleIndex() const {
  return GdbParser::RuleKeyword2D;
}

void GdbParser::Keyword2DContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterKeyword2D(this);
}

void GdbParser::Keyword2DContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitKeyword2D(this);
}

GdbParser::Keyword2DContext* GdbParser::keyword2D() {
  Keyword2DContext *_localctx = _tracker.createInstance<Keyword2DContext>(_ctx, getState());
  enterRule(_localctx, 46, GdbParser::RuleKeyword2D);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(190);
    match(GdbParser::Keyword2D);
    setState(191);
    match(GdbParser::IntegerConstant);
    setState(192);
    match(GdbParser::IntegerConstant);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Keyword2FContext ------------------------------------------------------------------

GdbParser::Keyword2FContext::Keyword2FContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GdbParser::Keyword2FContext::Keyword2F() {
  return getToken(GdbParser::Keyword2F, 0);
}

tree::TerminalNode* GdbParser::Keyword2FContext::IntegerConstant() {
  return getToken(GdbParser::IntegerConstant, 0);
}


size_t GdbParser::Keyword2FContext::getRuleIndex() const {
  return GdbParser::RuleKeyword2F;
}

void GdbParser::Keyword2FContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterKeyword2F(this);
}

void GdbParser::Keyword2FContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitKeyword2F(this);
}

GdbParser::Keyword2FContext* GdbParser::keyword2F() {
  Keyword2FContext *_localctx = _tracker.createInstance<Keyword2FContext>(_ctx, getState());
  enterRule(_localctx, 48, GdbParser::RuleKeyword2F);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(194);
    match(GdbParser::Keyword2F);
    setState(195);
    match(GdbParser::IntegerConstant);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Keyword30Context ------------------------------------------------------------------

GdbParser::Keyword30Context::Keyword30Context(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GdbParser::Keyword30Context::Keyword30() {
  return getToken(GdbParser::Keyword30, 0);
}


size_t GdbParser::Keyword30Context::getRuleIndex() const {
  return GdbParser::RuleKeyword30;
}

void GdbParser::Keyword30Context::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterKeyword30(this);
}

void GdbParser::Keyword30Context::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitKeyword30(this);
}

GdbParser::Keyword30Context* GdbParser::keyword30() {
  Keyword30Context *_localctx = _tracker.createInstance<Keyword30Context>(_ctx, getState());
  enterRule(_localctx, 50, GdbParser::RuleKeyword30);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(197);
    match(GdbParser::Keyword30);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Keyword32Context ------------------------------------------------------------------

GdbParser::Keyword32Context::Keyword32Context(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GdbParser::Keyword32Context::Keyword32() {
  return getToken(GdbParser::Keyword32, 0);
}

tree::TerminalNode* GdbParser::Keyword32Context::IntegerConstant() {
  return getToken(GdbParser::IntegerConstant, 0);
}


size_t GdbParser::Keyword32Context::getRuleIndex() const {
  return GdbParser::RuleKeyword32;
}

void GdbParser::Keyword32Context::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterKeyword32(this);
}

void GdbParser::Keyword32Context::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitKeyword32(this);
}

GdbParser::Keyword32Context* GdbParser::keyword32() {
  Keyword32Context *_localctx = _tracker.createInstance<Keyword32Context>(_ctx, getState());
  enterRule(_localctx, 52, GdbParser::RuleKeyword32);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(199);
    match(GdbParser::Keyword32);
    setState(200);
    match(GdbParser::IntegerConstant);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Keyword27Context ------------------------------------------------------------------

GdbParser::Keyword27Context::Keyword27Context(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GdbParser::Keyword27Context::Keyword27() {
  return getToken(GdbParser::Keyword27, 0);
}

tree::TerminalNode* GdbParser::Keyword27Context::IntegerConstant() {
  return getToken(GdbParser::IntegerConstant, 0);
}


size_t GdbParser::Keyword27Context::getRuleIndex() const {
  return GdbParser::RuleKeyword27;
}

void GdbParser::Keyword27Context::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterKeyword27(this);
}

void GdbParser::Keyword27Context::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitKeyword27(this);
}

GdbParser::Keyword27Context* GdbParser::keyword27() {
  Keyword27Context *_localctx = _tracker.createInstance<Keyword27Context>(_ctx, getState());
  enterRule(_localctx, 54, GdbParser::RuleKeyword27);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(202);
    match(GdbParser::Keyword27);
    setState(203);
    match(GdbParser::IntegerConstant);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FloatOrIntConstantContext ------------------------------------------------------------------

GdbParser::FloatOrIntConstantContext::FloatOrIntConstantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GdbParser::FloatOrIntConstantContext::FloatingConstant() {
  return getToken(GdbParser::FloatingConstant, 0);
}

tree::TerminalNode* GdbParser::FloatOrIntConstantContext::IntegerConstant() {
  return getToken(GdbParser::IntegerConstant, 0);
}


size_t GdbParser::FloatOrIntConstantContext::getRuleIndex() const {
  return GdbParser::RuleFloatOrIntConstant;
}

void GdbParser::FloatOrIntConstantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFloatOrIntConstant(this);
}

void GdbParser::FloatOrIntConstantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFloatOrIntConstant(this);
}

GdbParser::FloatOrIntConstantContext* GdbParser::floatOrIntConstant() {
  FloatOrIntConstantContext *_localctx = _tracker.createInstance<FloatOrIntConstantContext>(_ctx, getState());
  enterRule(_localctx, 56, GdbParser::RuleFloatOrIntConstant);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(205);
    _la = _input->LA(1);
    if (!(_la == GdbParser::IntegerConstant

    || _la == GdbParser::FloatingConstant)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void GdbParser::initialize() {
  std::call_once(gdbParserOnceFlag, gdbParserInitialize);
}
