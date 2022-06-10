
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
      "root", "materials", "material", "material_property", "colorMaterialProperty", 
      "colorMaterialPropertyKeyword", "textMaterialProperty", "textMaterialPropertyKeyword", 
      "uint8MaterialProperty", "uint8MaterialPropertyKeyword", "intMaterialProperty", 
      "intMaterialPropertyKeyword", "singleValueKeywords", "keyword2F", 
      "keyword2FSubtoken", "keyword38", "keyword38Subtoken"
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
      "Keyword4F", "Keyword50", "IntegerConstant", "StringLiteral", "Whitespace", 
      "Newline", "BlockComment", "LineComment"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,51,117,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,1,0,1,0,1,1,1,1,1,1,5,1,40,8,1,10,1,12,1,43,9,
  	1,1,1,1,1,1,2,1,2,1,2,1,2,5,2,51,8,2,10,2,12,2,54,9,2,1,2,1,2,1,3,1,3,
  	1,3,1,3,1,3,1,3,1,3,3,3,65,8,3,1,4,1,4,1,4,1,4,1,4,1,4,1,5,1,5,1,6,1,
  	6,1,6,1,7,1,7,1,8,1,8,1,8,1,9,1,9,1,10,1,10,1,10,1,11,1,11,1,12,1,12,
  	1,13,1,13,1,13,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,
  	1,14,1,14,1,14,3,14,109,8,14,1,15,1,15,1,15,1,15,1,16,1,16,1,16,0,0,17,
  	0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,0,4,1,0,5,6,1,0,42,45,4,
  	0,7,8,10,11,33,34,36,41,1,0,22,32,114,0,34,1,0,0,0,2,36,1,0,0,0,4,46,
  	1,0,0,0,6,64,1,0,0,0,8,66,1,0,0,0,10,72,1,0,0,0,12,74,1,0,0,0,14,77,1,
  	0,0,0,16,79,1,0,0,0,18,82,1,0,0,0,20,84,1,0,0,0,22,87,1,0,0,0,24,89,1,
  	0,0,0,26,91,1,0,0,0,28,108,1,0,0,0,30,110,1,0,0,0,32,114,1,0,0,0,34,35,
  	3,2,1,0,35,1,1,0,0,0,36,37,5,3,0,0,37,41,5,1,0,0,38,40,3,4,2,0,39,38,
  	1,0,0,0,40,43,1,0,0,0,41,39,1,0,0,0,41,42,1,0,0,0,42,44,1,0,0,0,43,41,
  	1,0,0,0,44,45,5,2,0,0,45,3,1,0,0,0,46,47,5,4,0,0,47,48,5,47,0,0,48,52,
  	5,1,0,0,49,51,3,6,3,0,50,49,1,0,0,0,51,54,1,0,0,0,52,50,1,0,0,0,52,53,
  	1,0,0,0,53,55,1,0,0,0,54,52,1,0,0,0,55,56,5,2,0,0,56,5,1,0,0,0,57,65,
  	3,8,4,0,58,65,3,12,6,0,59,65,3,16,8,0,60,65,3,20,10,0,61,65,3,24,12,0,
  	62,65,3,26,13,0,63,65,3,30,15,0,64,57,1,0,0,0,64,58,1,0,0,0,64,59,1,0,
  	0,0,64,60,1,0,0,0,64,61,1,0,0,0,64,62,1,0,0,0,64,63,1,0,0,0,65,7,1,0,
  	0,0,66,67,3,10,5,0,67,68,5,46,0,0,68,69,5,46,0,0,69,70,5,46,0,0,70,71,
  	5,46,0,0,71,9,1,0,0,0,72,73,7,0,0,0,73,11,1,0,0,0,74,75,3,14,7,0,75,76,
  	5,47,0,0,76,13,1,0,0,0,77,78,5,9,0,0,78,15,1,0,0,0,79,80,3,18,9,0,80,
  	81,5,46,0,0,81,17,1,0,0,0,82,83,5,35,0,0,83,19,1,0,0,0,84,85,3,22,11,
  	0,85,86,5,46,0,0,86,21,1,0,0,0,87,88,7,1,0,0,88,23,1,0,0,0,89,90,7,2,
  	0,0,90,25,1,0,0,0,91,92,5,12,0,0,92,93,3,28,14,0,93,27,1,0,0,0,94,109,
  	5,13,0,0,95,96,5,14,0,0,96,109,5,46,0,0,97,98,5,15,0,0,98,109,5,46,0,
  	0,99,100,5,16,0,0,100,109,5,46,0,0,101,102,5,17,0,0,102,109,5,46,0,0,
  	103,104,5,18,0,0,104,109,5,46,0,0,105,109,5,19,0,0,106,107,5,20,0,0,107,
  	109,5,46,0,0,108,94,1,0,0,0,108,95,1,0,0,0,108,97,1,0,0,0,108,99,1,0,
  	0,0,108,101,1,0,0,0,108,103,1,0,0,0,108,105,1,0,0,0,108,106,1,0,0,0,109,
  	29,1,0,0,0,110,111,5,21,0,0,111,112,3,32,16,0,112,113,3,32,16,0,113,31,
  	1,0,0,0,114,115,7,3,0,0,115,33,1,0,0,0,4,41,52,64,108
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


//----------------- RootContext ------------------------------------------------------------------

MdbParser::RootContext::RootContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MdbParser::MaterialsContext* MdbParser::RootContext::materials() {
  return getRuleContext<MdbParser::MaterialsContext>(0);
}


size_t MdbParser::RootContext::getRuleIndex() const {
  return MdbParser::RuleRoot;
}

void MdbParser::RootContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRoot(this);
}

void MdbParser::RootContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRoot(this);
}

MdbParser::RootContext* MdbParser::root() {
  RootContext *_localctx = _tracker.createInstance<RootContext>(_ctx, getState());
  enterRule(_localctx, 0, MdbParser::RuleRoot);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(34);
    materials();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MaterialsContext ------------------------------------------------------------------

MdbParser::MaterialsContext::MaterialsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MdbParser::MaterialsContext::Materials() {
  return getToken(MdbParser::Materials, 0);
}

std::vector<MdbParser::MaterialContext *> MdbParser::MaterialsContext::material() {
  return getRuleContexts<MdbParser::MaterialContext>();
}

MdbParser::MaterialContext* MdbParser::MaterialsContext::material(size_t i) {
  return getRuleContext<MdbParser::MaterialContext>(i);
}


size_t MdbParser::MaterialsContext::getRuleIndex() const {
  return MdbParser::RuleMaterials;
}

void MdbParser::MaterialsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMaterials(this);
}

void MdbParser::MaterialsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMaterials(this);
}

MdbParser::MaterialsContext* MdbParser::materials() {
  MaterialsContext *_localctx = _tracker.createInstance<MaterialsContext>(_ctx, getState());
  enterRule(_localctx, 2, MdbParser::RuleMaterials);
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
    setState(36);
    match(MdbParser::Materials);
    setState(37);
    match(MdbParser::T__0);
    setState(41);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MdbParser::Material) {
      setState(38);
      material();
      setState(43);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(44);
    match(MdbParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MaterialContext ------------------------------------------------------------------

MdbParser::MaterialContext::MaterialContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MdbParser::MaterialContext::Material() {
  return getToken(MdbParser::Material, 0);
}

tree::TerminalNode* MdbParser::MaterialContext::StringLiteral() {
  return getToken(MdbParser::StringLiteral, 0);
}

std::vector<MdbParser::Material_propertyContext *> MdbParser::MaterialContext::material_property() {
  return getRuleContexts<MdbParser::Material_propertyContext>();
}

MdbParser::Material_propertyContext* MdbParser::MaterialContext::material_property(size_t i) {
  return getRuleContext<MdbParser::Material_propertyContext>(i);
}


size_t MdbParser::MaterialContext::getRuleIndex() const {
  return MdbParser::RuleMaterial;
}

void MdbParser::MaterialContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMaterial(this);
}

void MdbParser::MaterialContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMaterial(this);
}

MdbParser::MaterialContext* MdbParser::material() {
  MaterialContext *_localctx = _tracker.createInstance<MaterialContext>(_ctx, getState());
  enterRule(_localctx, 4, MdbParser::RuleMaterial);
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
    setState(46);
    match(MdbParser::Material);
    setState(47);
    match(MdbParser::StringLiteral);
    setState(48);
    match(MdbParser::T__0);
    setState(52);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << MdbParser::Color1)
      | (1ULL << MdbParser::Color0)
      | (1ULL << MdbParser::Keyword2A)
      | (1ULL << MdbParser::Keyword2B)
      | (1ULL << MdbParser::Texture)
      | (1ULL << MdbParser::Keyword2D)
      | (1ULL << MdbParser::Keyword2E)
      | (1ULL << MdbParser::Keyword2F)
      | (1ULL << MdbParser::Keyword38)
      | (1ULL << MdbParser::Keyword44)
      | (1ULL << MdbParser::Keyword45)
      | (1ULL << MdbParser::Opacity)
      | (1ULL << MdbParser::Keyword47)
      | (1ULL << MdbParser::Keyword48)
      | (1ULL << MdbParser::Keyword49)
      | (1ULL << MdbParser::Keyword4A)
      | (1ULL << MdbParser::Keyword4B)
      | (1ULL << MdbParser::Keyword4C)
      | (1ULL << MdbParser::Keyword4D)
      | (1ULL << MdbParser::Keyword4E)
      | (1ULL << MdbParser::Keyword4F)
      | (1ULL << MdbParser::Keyword50))) != 0)) {
      setState(49);
      material_property();
      setState(54);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(55);
    match(MdbParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Material_propertyContext ------------------------------------------------------------------

MdbParser::Material_propertyContext::Material_propertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MdbParser::ColorMaterialPropertyContext* MdbParser::Material_propertyContext::colorMaterialProperty() {
  return getRuleContext<MdbParser::ColorMaterialPropertyContext>(0);
}

MdbParser::TextMaterialPropertyContext* MdbParser::Material_propertyContext::textMaterialProperty() {
  return getRuleContext<MdbParser::TextMaterialPropertyContext>(0);
}

MdbParser::Uint8MaterialPropertyContext* MdbParser::Material_propertyContext::uint8MaterialProperty() {
  return getRuleContext<MdbParser::Uint8MaterialPropertyContext>(0);
}

MdbParser::IntMaterialPropertyContext* MdbParser::Material_propertyContext::intMaterialProperty() {
  return getRuleContext<MdbParser::IntMaterialPropertyContext>(0);
}

MdbParser::SingleValueKeywordsContext* MdbParser::Material_propertyContext::singleValueKeywords() {
  return getRuleContext<MdbParser::SingleValueKeywordsContext>(0);
}

MdbParser::Keyword2FContext* MdbParser::Material_propertyContext::keyword2F() {
  return getRuleContext<MdbParser::Keyword2FContext>(0);
}

MdbParser::Keyword38Context* MdbParser::Material_propertyContext::keyword38() {
  return getRuleContext<MdbParser::Keyword38Context>(0);
}


size_t MdbParser::Material_propertyContext::getRuleIndex() const {
  return MdbParser::RuleMaterial_property;
}

void MdbParser::Material_propertyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMaterial_property(this);
}

void MdbParser::Material_propertyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMaterial_property(this);
}

MdbParser::Material_propertyContext* MdbParser::material_property() {
  Material_propertyContext *_localctx = _tracker.createInstance<Material_propertyContext>(_ctx, getState());
  enterRule(_localctx, 6, MdbParser::RuleMaterial_property);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(64);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MdbParser::Color1:
      case MdbParser::Color0: {
        enterOuterAlt(_localctx, 1);
        setState(57);
        colorMaterialProperty();
        break;
      }

      case MdbParser::Texture: {
        enterOuterAlt(_localctx, 2);
        setState(58);
        textMaterialProperty();
        break;
      }

      case MdbParser::Opacity: {
        enterOuterAlt(_localctx, 3);
        setState(59);
        uint8MaterialProperty();
        break;
      }

      case MdbParser::Keyword4D:
      case MdbParser::Keyword4E:
      case MdbParser::Keyword4F:
      case MdbParser::Keyword50: {
        enterOuterAlt(_localctx, 4);
        setState(60);
        intMaterialProperty();
        break;
      }

      case MdbParser::Keyword2A:
      case MdbParser::Keyword2B:
      case MdbParser::Keyword2D:
      case MdbParser::Keyword2E:
      case MdbParser::Keyword44:
      case MdbParser::Keyword45:
      case MdbParser::Keyword47:
      case MdbParser::Keyword48:
      case MdbParser::Keyword49:
      case MdbParser::Keyword4A:
      case MdbParser::Keyword4B:
      case MdbParser::Keyword4C: {
        enterOuterAlt(_localctx, 5);
        setState(61);
        singleValueKeywords();
        break;
      }

      case MdbParser::Keyword2F: {
        enterOuterAlt(_localctx, 6);
        setState(62);
        keyword2F();
        break;
      }

      case MdbParser::Keyword38: {
        enterOuterAlt(_localctx, 7);
        setState(63);
        keyword38();
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

//----------------- ColorMaterialPropertyContext ------------------------------------------------------------------

MdbParser::ColorMaterialPropertyContext::ColorMaterialPropertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MdbParser::ColorMaterialPropertyKeywordContext* MdbParser::ColorMaterialPropertyContext::colorMaterialPropertyKeyword() {
  return getRuleContext<MdbParser::ColorMaterialPropertyKeywordContext>(0);
}

std::vector<tree::TerminalNode *> MdbParser::ColorMaterialPropertyContext::IntegerConstant() {
  return getTokens(MdbParser::IntegerConstant);
}

tree::TerminalNode* MdbParser::ColorMaterialPropertyContext::IntegerConstant(size_t i) {
  return getToken(MdbParser::IntegerConstant, i);
}


size_t MdbParser::ColorMaterialPropertyContext::getRuleIndex() const {
  return MdbParser::RuleColorMaterialProperty;
}

void MdbParser::ColorMaterialPropertyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterColorMaterialProperty(this);
}

void MdbParser::ColorMaterialPropertyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitColorMaterialProperty(this);
}

MdbParser::ColorMaterialPropertyContext* MdbParser::colorMaterialProperty() {
  ColorMaterialPropertyContext *_localctx = _tracker.createInstance<ColorMaterialPropertyContext>(_ctx, getState());
  enterRule(_localctx, 8, MdbParser::RuleColorMaterialProperty);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(66);
    colorMaterialPropertyKeyword();
    setState(67);
    match(MdbParser::IntegerConstant);
    setState(68);
    match(MdbParser::IntegerConstant);
    setState(69);
    match(MdbParser::IntegerConstant);
    setState(70);
    match(MdbParser::IntegerConstant);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ColorMaterialPropertyKeywordContext ------------------------------------------------------------------

MdbParser::ColorMaterialPropertyKeywordContext::ColorMaterialPropertyKeywordContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MdbParser::ColorMaterialPropertyKeywordContext::Color0() {
  return getToken(MdbParser::Color0, 0);
}

tree::TerminalNode* MdbParser::ColorMaterialPropertyKeywordContext::Color1() {
  return getToken(MdbParser::Color1, 0);
}


size_t MdbParser::ColorMaterialPropertyKeywordContext::getRuleIndex() const {
  return MdbParser::RuleColorMaterialPropertyKeyword;
}

void MdbParser::ColorMaterialPropertyKeywordContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterColorMaterialPropertyKeyword(this);
}

void MdbParser::ColorMaterialPropertyKeywordContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitColorMaterialPropertyKeyword(this);
}

MdbParser::ColorMaterialPropertyKeywordContext* MdbParser::colorMaterialPropertyKeyword() {
  ColorMaterialPropertyKeywordContext *_localctx = _tracker.createInstance<ColorMaterialPropertyKeywordContext>(_ctx, getState());
  enterRule(_localctx, 10, MdbParser::RuleColorMaterialPropertyKeyword);
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
    setState(72);
    _la = _input->LA(1);
    if (!(_la == MdbParser::Color1

    || _la == MdbParser::Color0)) {
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

//----------------- TextMaterialPropertyContext ------------------------------------------------------------------

MdbParser::TextMaterialPropertyContext::TextMaterialPropertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MdbParser::TextMaterialPropertyKeywordContext* MdbParser::TextMaterialPropertyContext::textMaterialPropertyKeyword() {
  return getRuleContext<MdbParser::TextMaterialPropertyKeywordContext>(0);
}

tree::TerminalNode* MdbParser::TextMaterialPropertyContext::StringLiteral() {
  return getToken(MdbParser::StringLiteral, 0);
}


size_t MdbParser::TextMaterialPropertyContext::getRuleIndex() const {
  return MdbParser::RuleTextMaterialProperty;
}

void MdbParser::TextMaterialPropertyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTextMaterialProperty(this);
}

void MdbParser::TextMaterialPropertyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTextMaterialProperty(this);
}

MdbParser::TextMaterialPropertyContext* MdbParser::textMaterialProperty() {
  TextMaterialPropertyContext *_localctx = _tracker.createInstance<TextMaterialPropertyContext>(_ctx, getState());
  enterRule(_localctx, 12, MdbParser::RuleTextMaterialProperty);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(74);
    textMaterialPropertyKeyword();
    setState(75);
    match(MdbParser::StringLiteral);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TextMaterialPropertyKeywordContext ------------------------------------------------------------------

MdbParser::TextMaterialPropertyKeywordContext::TextMaterialPropertyKeywordContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MdbParser::TextMaterialPropertyKeywordContext::Texture() {
  return getToken(MdbParser::Texture, 0);
}


size_t MdbParser::TextMaterialPropertyKeywordContext::getRuleIndex() const {
  return MdbParser::RuleTextMaterialPropertyKeyword;
}

void MdbParser::TextMaterialPropertyKeywordContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTextMaterialPropertyKeyword(this);
}

void MdbParser::TextMaterialPropertyKeywordContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTextMaterialPropertyKeyword(this);
}

MdbParser::TextMaterialPropertyKeywordContext* MdbParser::textMaterialPropertyKeyword() {
  TextMaterialPropertyKeywordContext *_localctx = _tracker.createInstance<TextMaterialPropertyKeywordContext>(_ctx, getState());
  enterRule(_localctx, 14, MdbParser::RuleTextMaterialPropertyKeyword);

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
    match(MdbParser::Texture);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Uint8MaterialPropertyContext ------------------------------------------------------------------

MdbParser::Uint8MaterialPropertyContext::Uint8MaterialPropertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MdbParser::Uint8MaterialPropertyKeywordContext* MdbParser::Uint8MaterialPropertyContext::uint8MaterialPropertyKeyword() {
  return getRuleContext<MdbParser::Uint8MaterialPropertyKeywordContext>(0);
}

tree::TerminalNode* MdbParser::Uint8MaterialPropertyContext::IntegerConstant() {
  return getToken(MdbParser::IntegerConstant, 0);
}


size_t MdbParser::Uint8MaterialPropertyContext::getRuleIndex() const {
  return MdbParser::RuleUint8MaterialProperty;
}

void MdbParser::Uint8MaterialPropertyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUint8MaterialProperty(this);
}

void MdbParser::Uint8MaterialPropertyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUint8MaterialProperty(this);
}

MdbParser::Uint8MaterialPropertyContext* MdbParser::uint8MaterialProperty() {
  Uint8MaterialPropertyContext *_localctx = _tracker.createInstance<Uint8MaterialPropertyContext>(_ctx, getState());
  enterRule(_localctx, 16, MdbParser::RuleUint8MaterialProperty);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(79);
    uint8MaterialPropertyKeyword();
    setState(80);
    match(MdbParser::IntegerConstant);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Uint8MaterialPropertyKeywordContext ------------------------------------------------------------------

MdbParser::Uint8MaterialPropertyKeywordContext::Uint8MaterialPropertyKeywordContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MdbParser::Uint8MaterialPropertyKeywordContext::Opacity() {
  return getToken(MdbParser::Opacity, 0);
}


size_t MdbParser::Uint8MaterialPropertyKeywordContext::getRuleIndex() const {
  return MdbParser::RuleUint8MaterialPropertyKeyword;
}

void MdbParser::Uint8MaterialPropertyKeywordContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUint8MaterialPropertyKeyword(this);
}

void MdbParser::Uint8MaterialPropertyKeywordContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUint8MaterialPropertyKeyword(this);
}

MdbParser::Uint8MaterialPropertyKeywordContext* MdbParser::uint8MaterialPropertyKeyword() {
  Uint8MaterialPropertyKeywordContext *_localctx = _tracker.createInstance<Uint8MaterialPropertyKeywordContext>(_ctx, getState());
  enterRule(_localctx, 18, MdbParser::RuleUint8MaterialPropertyKeyword);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(82);
    match(MdbParser::Opacity);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IntMaterialPropertyContext ------------------------------------------------------------------

MdbParser::IntMaterialPropertyContext::IntMaterialPropertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MdbParser::IntMaterialPropertyKeywordContext* MdbParser::IntMaterialPropertyContext::intMaterialPropertyKeyword() {
  return getRuleContext<MdbParser::IntMaterialPropertyKeywordContext>(0);
}

tree::TerminalNode* MdbParser::IntMaterialPropertyContext::IntegerConstant() {
  return getToken(MdbParser::IntegerConstant, 0);
}


size_t MdbParser::IntMaterialPropertyContext::getRuleIndex() const {
  return MdbParser::RuleIntMaterialProperty;
}

void MdbParser::IntMaterialPropertyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIntMaterialProperty(this);
}

void MdbParser::IntMaterialPropertyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIntMaterialProperty(this);
}

MdbParser::IntMaterialPropertyContext* MdbParser::intMaterialProperty() {
  IntMaterialPropertyContext *_localctx = _tracker.createInstance<IntMaterialPropertyContext>(_ctx, getState());
  enterRule(_localctx, 20, MdbParser::RuleIntMaterialProperty);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(84);
    intMaterialPropertyKeyword();
    setState(85);
    match(MdbParser::IntegerConstant);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IntMaterialPropertyKeywordContext ------------------------------------------------------------------

MdbParser::IntMaterialPropertyKeywordContext::IntMaterialPropertyKeywordContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MdbParser::IntMaterialPropertyKeywordContext::Keyword4D() {
  return getToken(MdbParser::Keyword4D, 0);
}

tree::TerminalNode* MdbParser::IntMaterialPropertyKeywordContext::Keyword4E() {
  return getToken(MdbParser::Keyword4E, 0);
}

tree::TerminalNode* MdbParser::IntMaterialPropertyKeywordContext::Keyword4F() {
  return getToken(MdbParser::Keyword4F, 0);
}

tree::TerminalNode* MdbParser::IntMaterialPropertyKeywordContext::Keyword50() {
  return getToken(MdbParser::Keyword50, 0);
}


size_t MdbParser::IntMaterialPropertyKeywordContext::getRuleIndex() const {
  return MdbParser::RuleIntMaterialPropertyKeyword;
}

void MdbParser::IntMaterialPropertyKeywordContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIntMaterialPropertyKeyword(this);
}

void MdbParser::IntMaterialPropertyKeywordContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIntMaterialPropertyKeyword(this);
}

MdbParser::IntMaterialPropertyKeywordContext* MdbParser::intMaterialPropertyKeyword() {
  IntMaterialPropertyKeywordContext *_localctx = _tracker.createInstance<IntMaterialPropertyKeywordContext>(_ctx, getState());
  enterRule(_localctx, 22, MdbParser::RuleIntMaterialPropertyKeyword);
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
    setState(87);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << MdbParser::Keyword4D)
      | (1ULL << MdbParser::Keyword4E)
      | (1ULL << MdbParser::Keyword4F)
      | (1ULL << MdbParser::Keyword50))) != 0))) {
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

//----------------- SingleValueKeywordsContext ------------------------------------------------------------------

MdbParser::SingleValueKeywordsContext::SingleValueKeywordsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MdbParser::SingleValueKeywordsContext::Keyword2A() {
  return getToken(MdbParser::Keyword2A, 0);
}

tree::TerminalNode* MdbParser::SingleValueKeywordsContext::Keyword2B() {
  return getToken(MdbParser::Keyword2B, 0);
}

tree::TerminalNode* MdbParser::SingleValueKeywordsContext::Keyword2D() {
  return getToken(MdbParser::Keyword2D, 0);
}

tree::TerminalNode* MdbParser::SingleValueKeywordsContext::Keyword2E() {
  return getToken(MdbParser::Keyword2E, 0);
}

tree::TerminalNode* MdbParser::SingleValueKeywordsContext::Keyword44() {
  return getToken(MdbParser::Keyword44, 0);
}

tree::TerminalNode* MdbParser::SingleValueKeywordsContext::Keyword45() {
  return getToken(MdbParser::Keyword45, 0);
}

tree::TerminalNode* MdbParser::SingleValueKeywordsContext::Keyword47() {
  return getToken(MdbParser::Keyword47, 0);
}

tree::TerminalNode* MdbParser::SingleValueKeywordsContext::Keyword48() {
  return getToken(MdbParser::Keyword48, 0);
}

tree::TerminalNode* MdbParser::SingleValueKeywordsContext::Keyword49() {
  return getToken(MdbParser::Keyword49, 0);
}

tree::TerminalNode* MdbParser::SingleValueKeywordsContext::Keyword4A() {
  return getToken(MdbParser::Keyword4A, 0);
}

tree::TerminalNode* MdbParser::SingleValueKeywordsContext::Keyword4B() {
  return getToken(MdbParser::Keyword4B, 0);
}

tree::TerminalNode* MdbParser::SingleValueKeywordsContext::Keyword4C() {
  return getToken(MdbParser::Keyword4C, 0);
}


size_t MdbParser::SingleValueKeywordsContext::getRuleIndex() const {
  return MdbParser::RuleSingleValueKeywords;
}

void MdbParser::SingleValueKeywordsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSingleValueKeywords(this);
}

void MdbParser::SingleValueKeywordsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSingleValueKeywords(this);
}

MdbParser::SingleValueKeywordsContext* MdbParser::singleValueKeywords() {
  SingleValueKeywordsContext *_localctx = _tracker.createInstance<SingleValueKeywordsContext>(_ctx, getState());
  enterRule(_localctx, 24, MdbParser::RuleSingleValueKeywords);
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
    setState(89);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << MdbParser::Keyword2A)
      | (1ULL << MdbParser::Keyword2B)
      | (1ULL << MdbParser::Keyword2D)
      | (1ULL << MdbParser::Keyword2E)
      | (1ULL << MdbParser::Keyword44)
      | (1ULL << MdbParser::Keyword45)
      | (1ULL << MdbParser::Keyword47)
      | (1ULL << MdbParser::Keyword48)
      | (1ULL << MdbParser::Keyword49)
      | (1ULL << MdbParser::Keyword4A)
      | (1ULL << MdbParser::Keyword4B)
      | (1ULL << MdbParser::Keyword4C))) != 0))) {
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

//----------------- Keyword2FContext ------------------------------------------------------------------

MdbParser::Keyword2FContext::Keyword2FContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MdbParser::Keyword2FContext::Keyword2F() {
  return getToken(MdbParser::Keyword2F, 0);
}

MdbParser::Keyword2FSubtokenContext* MdbParser::Keyword2FContext::keyword2FSubtoken() {
  return getRuleContext<MdbParser::Keyword2FSubtokenContext>(0);
}


size_t MdbParser::Keyword2FContext::getRuleIndex() const {
  return MdbParser::RuleKeyword2F;
}

void MdbParser::Keyword2FContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterKeyword2F(this);
}

void MdbParser::Keyword2FContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitKeyword2F(this);
}

MdbParser::Keyword2FContext* MdbParser::keyword2F() {
  Keyword2FContext *_localctx = _tracker.createInstance<Keyword2FContext>(_ctx, getState());
  enterRule(_localctx, 26, MdbParser::RuleKeyword2F);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(91);
    match(MdbParser::Keyword2F);
    setState(92);
    keyword2FSubtoken();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Keyword2FSubtokenContext ------------------------------------------------------------------

MdbParser::Keyword2FSubtokenContext::Keyword2FSubtokenContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MdbParser::Keyword2FSubtokenContext::Keyword30() {
  return getToken(MdbParser::Keyword30, 0);
}

tree::TerminalNode* MdbParser::Keyword2FSubtokenContext::Keyword31() {
  return getToken(MdbParser::Keyword31, 0);
}

tree::TerminalNode* MdbParser::Keyword2FSubtokenContext::IntegerConstant() {
  return getToken(MdbParser::IntegerConstant, 0);
}

tree::TerminalNode* MdbParser::Keyword2FSubtokenContext::Keyword32() {
  return getToken(MdbParser::Keyword32, 0);
}

tree::TerminalNode* MdbParser::Keyword2FSubtokenContext::Keyword33() {
  return getToken(MdbParser::Keyword33, 0);
}

tree::TerminalNode* MdbParser::Keyword2FSubtokenContext::Keyword34() {
  return getToken(MdbParser::Keyword34, 0);
}

tree::TerminalNode* MdbParser::Keyword2FSubtokenContext::Keyword35() {
  return getToken(MdbParser::Keyword35, 0);
}

tree::TerminalNode* MdbParser::Keyword2FSubtokenContext::Keyword36() {
  return getToken(MdbParser::Keyword36, 0);
}

tree::TerminalNode* MdbParser::Keyword2FSubtokenContext::Keyword37() {
  return getToken(MdbParser::Keyword37, 0);
}


size_t MdbParser::Keyword2FSubtokenContext::getRuleIndex() const {
  return MdbParser::RuleKeyword2FSubtoken;
}

void MdbParser::Keyword2FSubtokenContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterKeyword2FSubtoken(this);
}

void MdbParser::Keyword2FSubtokenContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitKeyword2FSubtoken(this);
}

MdbParser::Keyword2FSubtokenContext* MdbParser::keyword2FSubtoken() {
  Keyword2FSubtokenContext *_localctx = _tracker.createInstance<Keyword2FSubtokenContext>(_ctx, getState());
  enterRule(_localctx, 28, MdbParser::RuleKeyword2FSubtoken);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(108);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MdbParser::Keyword30: {
        enterOuterAlt(_localctx, 1);
        setState(94);
        match(MdbParser::Keyword30);
        break;
      }

      case MdbParser::Keyword31: {
        enterOuterAlt(_localctx, 2);
        setState(95);
        match(MdbParser::Keyword31);
        setState(96);
        match(MdbParser::IntegerConstant);
        break;
      }

      case MdbParser::Keyword32: {
        enterOuterAlt(_localctx, 3);
        setState(97);
        match(MdbParser::Keyword32);
        setState(98);
        match(MdbParser::IntegerConstant);
        break;
      }

      case MdbParser::Keyword33: {
        enterOuterAlt(_localctx, 4);
        setState(99);
        match(MdbParser::Keyword33);
        setState(100);
        match(MdbParser::IntegerConstant);
        break;
      }

      case MdbParser::Keyword34: {
        enterOuterAlt(_localctx, 5);
        setState(101);
        match(MdbParser::Keyword34);
        setState(102);
        match(MdbParser::IntegerConstant);
        break;
      }

      case MdbParser::Keyword35: {
        enterOuterAlt(_localctx, 6);
        setState(103);
        match(MdbParser::Keyword35);
        setState(104);
        match(MdbParser::IntegerConstant);
        break;
      }

      case MdbParser::Keyword36: {
        enterOuterAlt(_localctx, 7);
        setState(105);
        match(MdbParser::Keyword36);
        break;
      }

      case MdbParser::Keyword37: {
        enterOuterAlt(_localctx, 8);
        setState(106);
        match(MdbParser::Keyword37);
        setState(107);
        match(MdbParser::IntegerConstant);
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

//----------------- Keyword38Context ------------------------------------------------------------------

MdbParser::Keyword38Context::Keyword38Context(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MdbParser::Keyword38Context::Keyword38() {
  return getToken(MdbParser::Keyword38, 0);
}

std::vector<MdbParser::Keyword38SubtokenContext *> MdbParser::Keyword38Context::keyword38Subtoken() {
  return getRuleContexts<MdbParser::Keyword38SubtokenContext>();
}

MdbParser::Keyword38SubtokenContext* MdbParser::Keyword38Context::keyword38Subtoken(size_t i) {
  return getRuleContext<MdbParser::Keyword38SubtokenContext>(i);
}


size_t MdbParser::Keyword38Context::getRuleIndex() const {
  return MdbParser::RuleKeyword38;
}

void MdbParser::Keyword38Context::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterKeyword38(this);
}

void MdbParser::Keyword38Context::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitKeyword38(this);
}

MdbParser::Keyword38Context* MdbParser::keyword38() {
  Keyword38Context *_localctx = _tracker.createInstance<Keyword38Context>(_ctx, getState());
  enterRule(_localctx, 30, MdbParser::RuleKeyword38);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(110);
    match(MdbParser::Keyword38);
    setState(111);
    keyword38Subtoken();
    setState(112);
    keyword38Subtoken();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Keyword38SubtokenContext ------------------------------------------------------------------

MdbParser::Keyword38SubtokenContext::Keyword38SubtokenContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MdbParser::Keyword38SubtokenContext::Keyword39() {
  return getToken(MdbParser::Keyword39, 0);
}

tree::TerminalNode* MdbParser::Keyword38SubtokenContext::Keyword3A() {
  return getToken(MdbParser::Keyword3A, 0);
}

tree::TerminalNode* MdbParser::Keyword38SubtokenContext::Keyword3B() {
  return getToken(MdbParser::Keyword3B, 0);
}

tree::TerminalNode* MdbParser::Keyword38SubtokenContext::Keyword3C() {
  return getToken(MdbParser::Keyword3C, 0);
}

tree::TerminalNode* MdbParser::Keyword38SubtokenContext::Keyword3D() {
  return getToken(MdbParser::Keyword3D, 0);
}

tree::TerminalNode* MdbParser::Keyword38SubtokenContext::Keyword3E() {
  return getToken(MdbParser::Keyword3E, 0);
}

tree::TerminalNode* MdbParser::Keyword38SubtokenContext::Keyword3F() {
  return getToken(MdbParser::Keyword3F, 0);
}

tree::TerminalNode* MdbParser::Keyword38SubtokenContext::Keyword40() {
  return getToken(MdbParser::Keyword40, 0);
}

tree::TerminalNode* MdbParser::Keyword38SubtokenContext::Keyword41() {
  return getToken(MdbParser::Keyword41, 0);
}

tree::TerminalNode* MdbParser::Keyword38SubtokenContext::Keyword42() {
  return getToken(MdbParser::Keyword42, 0);
}

tree::TerminalNode* MdbParser::Keyword38SubtokenContext::Keyword43() {
  return getToken(MdbParser::Keyword43, 0);
}


size_t MdbParser::Keyword38SubtokenContext::getRuleIndex() const {
  return MdbParser::RuleKeyword38Subtoken;
}

void MdbParser::Keyword38SubtokenContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterKeyword38Subtoken(this);
}

void MdbParser::Keyword38SubtokenContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitKeyword38Subtoken(this);
}

MdbParser::Keyword38SubtokenContext* MdbParser::keyword38Subtoken() {
  Keyword38SubtokenContext *_localctx = _tracker.createInstance<Keyword38SubtokenContext>(_ctx, getState());
  enterRule(_localctx, 32, MdbParser::RuleKeyword38Subtoken);
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
    setState(114);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << MdbParser::Keyword39)
      | (1ULL << MdbParser::Keyword3A)
      | (1ULL << MdbParser::Keyword3B)
      | (1ULL << MdbParser::Keyword3C)
      | (1ULL << MdbParser::Keyword3D)
      | (1ULL << MdbParser::Keyword3E)
      | (1ULL << MdbParser::Keyword3F)
      | (1ULL << MdbParser::Keyword40)
      | (1ULL << MdbParser::Keyword41)
      | (1ULL << MdbParser::Keyword42)
      | (1ULL << MdbParser::Keyword43))) != 0))) {
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

void MdbParser::initialize() {
  std::call_once(mdbParserOnceFlag, mdbParserInitialize);
}
