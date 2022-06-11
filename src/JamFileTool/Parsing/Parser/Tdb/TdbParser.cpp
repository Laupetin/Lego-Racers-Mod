
// Generated from ..\..\..\src\JamFileTool\Parsing\Parser\Tdb\Tdb.g4 by ANTLR 4.10.1


#include "TdbListener.h"

#include "TdbParser.h"


using namespace antlrcpp;
using namespace tdb;

using namespace antlr4;

namespace {

struct TdbParserStaticData final {
  TdbParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  TdbParserStaticData(const TdbParserStaticData&) = delete;
  TdbParserStaticData(TdbParserStaticData&&) = delete;
  TdbParserStaticData& operator=(const TdbParserStaticData&) = delete;
  TdbParserStaticData& operator=(TdbParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag tdbParserOnceFlag;
TdbParserStaticData *tdbParserStaticData = nullptr;

void tdbParserInitialize() {
  assert(tdbParserStaticData == nullptr);
  auto staticData = std::make_unique<TdbParserStaticData>(
    std::vector<std::string>{
      "root", "textures", "texture", "textureName", "textureProperty", "colorTextureProperty", 
      "colorTexturePropertyKeyword", "intTextureProperty", "intTexturePropertyKeyword", 
      "singleValueKeywords"
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
  	4,1,17,65,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,7,
  	7,7,2,8,7,8,2,9,7,9,1,0,1,0,1,1,1,1,1,1,5,1,26,8,1,10,1,12,1,29,9,1,1,
  	1,1,1,1,2,1,2,1,2,1,2,5,2,37,8,2,10,2,12,2,40,9,2,1,2,1,2,1,3,1,3,1,4,
  	1,4,1,4,3,4,49,8,4,1,5,1,5,1,5,1,5,1,5,1,6,1,6,1,7,1,7,1,7,1,8,1,8,1,
  	9,1,9,1,9,0,0,10,0,2,4,6,8,10,12,14,16,18,0,1,3,0,5,5,7,8,10,11,58,0,
  	20,1,0,0,0,2,22,1,0,0,0,4,32,1,0,0,0,6,43,1,0,0,0,8,48,1,0,0,0,10,50,
  	1,0,0,0,12,55,1,0,0,0,14,57,1,0,0,0,16,60,1,0,0,0,18,62,1,0,0,0,20,21,
  	3,2,1,0,21,1,1,0,0,0,22,23,5,3,0,0,23,27,5,1,0,0,24,26,3,4,2,0,25,24,
  	1,0,0,0,26,29,1,0,0,0,27,25,1,0,0,0,27,28,1,0,0,0,28,30,1,0,0,0,29,27,
  	1,0,0,0,30,31,5,2,0,0,31,3,1,0,0,0,32,33,5,4,0,0,33,34,3,6,3,0,34,38,
  	5,1,0,0,35,37,3,8,4,0,36,35,1,0,0,0,37,40,1,0,0,0,38,36,1,0,0,0,38,39,
  	1,0,0,0,39,41,1,0,0,0,40,38,1,0,0,0,41,42,5,2,0,0,42,5,1,0,0,0,43,44,
  	5,13,0,0,44,7,1,0,0,0,45,49,3,10,5,0,46,49,3,14,7,0,47,49,3,18,9,0,48,
  	45,1,0,0,0,48,46,1,0,0,0,48,47,1,0,0,0,49,9,1,0,0,0,50,51,3,12,6,0,51,
  	52,5,12,0,0,52,53,5,12,0,0,53,54,5,12,0,0,54,11,1,0,0,0,55,56,5,9,0,0,
  	56,13,1,0,0,0,57,58,3,16,8,0,58,59,5,12,0,0,59,15,1,0,0,0,60,61,5,6,0,
  	0,61,17,1,0,0,0,62,63,7,0,0,0,63,19,1,0,0,0,3,27,38,48
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  tdbParserStaticData = staticData.release();
}

}

TdbParser::TdbParser(TokenStream *input) : TdbParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

TdbParser::TdbParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  TdbParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *tdbParserStaticData->atn, tdbParserStaticData->decisionToDFA, tdbParserStaticData->sharedContextCache, options);
}

TdbParser::~TdbParser() {
  delete _interpreter;
}

const atn::ATN& TdbParser::getATN() const {
  return *tdbParserStaticData->atn;
}

std::string TdbParser::getGrammarFileName() const {
  return "Tdb.g4";
}

const std::vector<std::string>& TdbParser::getRuleNames() const {
  return tdbParserStaticData->ruleNames;
}

const dfa::Vocabulary& TdbParser::getVocabulary() const {
  return tdbParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView TdbParser::getSerializedATN() const {
  return tdbParserStaticData->serializedATN;
}


//----------------- RootContext ------------------------------------------------------------------

TdbParser::RootContext::RootContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TdbParser::TexturesContext* TdbParser::RootContext::textures() {
  return getRuleContext<TdbParser::TexturesContext>(0);
}


size_t TdbParser::RootContext::getRuleIndex() const {
  return TdbParser::RuleRoot;
}

void TdbParser::RootContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRoot(this);
}

void TdbParser::RootContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRoot(this);
}

TdbParser::RootContext* TdbParser::root() {
  RootContext *_localctx = _tracker.createInstance<RootContext>(_ctx, getState());
  enterRule(_localctx, 0, TdbParser::RuleRoot);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(20);
    textures();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TexturesContext ------------------------------------------------------------------

TdbParser::TexturesContext::TexturesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TdbParser::TexturesContext::Textures() {
  return getToken(TdbParser::Textures, 0);
}

std::vector<TdbParser::TextureContext *> TdbParser::TexturesContext::texture() {
  return getRuleContexts<TdbParser::TextureContext>();
}

TdbParser::TextureContext* TdbParser::TexturesContext::texture(size_t i) {
  return getRuleContext<TdbParser::TextureContext>(i);
}


size_t TdbParser::TexturesContext::getRuleIndex() const {
  return TdbParser::RuleTextures;
}

void TdbParser::TexturesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTextures(this);
}

void TdbParser::TexturesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTextures(this);
}

TdbParser::TexturesContext* TdbParser::textures() {
  TexturesContext *_localctx = _tracker.createInstance<TexturesContext>(_ctx, getState());
  enterRule(_localctx, 2, TdbParser::RuleTextures);
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
    setState(22);
    match(TdbParser::Textures);
    setState(23);
    match(TdbParser::T__0);
    setState(27);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == TdbParser::Texture) {
      setState(24);
      texture();
      setState(29);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(30);
    match(TdbParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TextureContext ------------------------------------------------------------------

TdbParser::TextureContext::TextureContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TdbParser::TextureContext::Texture() {
  return getToken(TdbParser::Texture, 0);
}

TdbParser::TextureNameContext* TdbParser::TextureContext::textureName() {
  return getRuleContext<TdbParser::TextureNameContext>(0);
}

std::vector<TdbParser::TexturePropertyContext *> TdbParser::TextureContext::textureProperty() {
  return getRuleContexts<TdbParser::TexturePropertyContext>();
}

TdbParser::TexturePropertyContext* TdbParser::TextureContext::textureProperty(size_t i) {
  return getRuleContext<TdbParser::TexturePropertyContext>(i);
}


size_t TdbParser::TextureContext::getRuleIndex() const {
  return TdbParser::RuleTexture;
}

void TdbParser::TextureContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTexture(this);
}

void TdbParser::TextureContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTexture(this);
}

TdbParser::TextureContext* TdbParser::texture() {
  TextureContext *_localctx = _tracker.createInstance<TextureContext>(_ctx, getState());
  enterRule(_localctx, 4, TdbParser::RuleTexture);
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
    setState(32);
    match(TdbParser::Texture);
    setState(33);
    textureName();
    setState(34);
    match(TdbParser::T__0);
    setState(38);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << TdbParser::FlipVertically)
      | (1ULL << TdbParser::Keyword29)
      | (1ULL << TdbParser::Bmp)
      | (1ULL << TdbParser::Tga)
      | (1ULL << TdbParser::ChromaKey)
      | (1ULL << TdbParser::Keyword2D)
      | (1ULL << TdbParser::Keyword2E))) != 0)) {
      setState(35);
      textureProperty();
      setState(40);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(41);
    match(TdbParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TextureNameContext ------------------------------------------------------------------

TdbParser::TextureNameContext::TextureNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TdbParser::TextureNameContext::StringLiteral() {
  return getToken(TdbParser::StringLiteral, 0);
}


size_t TdbParser::TextureNameContext::getRuleIndex() const {
  return TdbParser::RuleTextureName;
}

void TdbParser::TextureNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTextureName(this);
}

void TdbParser::TextureNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTextureName(this);
}

TdbParser::TextureNameContext* TdbParser::textureName() {
  TextureNameContext *_localctx = _tracker.createInstance<TextureNameContext>(_ctx, getState());
  enterRule(_localctx, 6, TdbParser::RuleTextureName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(43);
    match(TdbParser::StringLiteral);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TexturePropertyContext ------------------------------------------------------------------

TdbParser::TexturePropertyContext::TexturePropertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TdbParser::ColorTexturePropertyContext* TdbParser::TexturePropertyContext::colorTextureProperty() {
  return getRuleContext<TdbParser::ColorTexturePropertyContext>(0);
}

TdbParser::IntTexturePropertyContext* TdbParser::TexturePropertyContext::intTextureProperty() {
  return getRuleContext<TdbParser::IntTexturePropertyContext>(0);
}

TdbParser::SingleValueKeywordsContext* TdbParser::TexturePropertyContext::singleValueKeywords() {
  return getRuleContext<TdbParser::SingleValueKeywordsContext>(0);
}


size_t TdbParser::TexturePropertyContext::getRuleIndex() const {
  return TdbParser::RuleTextureProperty;
}

void TdbParser::TexturePropertyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTextureProperty(this);
}

void TdbParser::TexturePropertyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTextureProperty(this);
}

TdbParser::TexturePropertyContext* TdbParser::textureProperty() {
  TexturePropertyContext *_localctx = _tracker.createInstance<TexturePropertyContext>(_ctx, getState());
  enterRule(_localctx, 8, TdbParser::RuleTextureProperty);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(48);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TdbParser::ChromaKey: {
        enterOuterAlt(_localctx, 1);
        setState(45);
        colorTextureProperty();
        break;
      }

      case TdbParser::Keyword29: {
        enterOuterAlt(_localctx, 2);
        setState(46);
        intTextureProperty();
        break;
      }

      case TdbParser::FlipVertically:
      case TdbParser::Bmp:
      case TdbParser::Tga:
      case TdbParser::Keyword2D:
      case TdbParser::Keyword2E: {
        enterOuterAlt(_localctx, 3);
        setState(47);
        singleValueKeywords();
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

//----------------- ColorTexturePropertyContext ------------------------------------------------------------------

TdbParser::ColorTexturePropertyContext::ColorTexturePropertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TdbParser::ColorTexturePropertyKeywordContext* TdbParser::ColorTexturePropertyContext::colorTexturePropertyKeyword() {
  return getRuleContext<TdbParser::ColorTexturePropertyKeywordContext>(0);
}

std::vector<tree::TerminalNode *> TdbParser::ColorTexturePropertyContext::IntegerConstant() {
  return getTokens(TdbParser::IntegerConstant);
}

tree::TerminalNode* TdbParser::ColorTexturePropertyContext::IntegerConstant(size_t i) {
  return getToken(TdbParser::IntegerConstant, i);
}


size_t TdbParser::ColorTexturePropertyContext::getRuleIndex() const {
  return TdbParser::RuleColorTextureProperty;
}

void TdbParser::ColorTexturePropertyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterColorTextureProperty(this);
}

void TdbParser::ColorTexturePropertyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitColorTextureProperty(this);
}

TdbParser::ColorTexturePropertyContext* TdbParser::colorTextureProperty() {
  ColorTexturePropertyContext *_localctx = _tracker.createInstance<ColorTexturePropertyContext>(_ctx, getState());
  enterRule(_localctx, 10, TdbParser::RuleColorTextureProperty);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(50);
    colorTexturePropertyKeyword();
    setState(51);
    match(TdbParser::IntegerConstant);
    setState(52);
    match(TdbParser::IntegerConstant);
    setState(53);
    match(TdbParser::IntegerConstant);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ColorTexturePropertyKeywordContext ------------------------------------------------------------------

TdbParser::ColorTexturePropertyKeywordContext::ColorTexturePropertyKeywordContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TdbParser::ColorTexturePropertyKeywordContext::ChromaKey() {
  return getToken(TdbParser::ChromaKey, 0);
}


size_t TdbParser::ColorTexturePropertyKeywordContext::getRuleIndex() const {
  return TdbParser::RuleColorTexturePropertyKeyword;
}

void TdbParser::ColorTexturePropertyKeywordContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterColorTexturePropertyKeyword(this);
}

void TdbParser::ColorTexturePropertyKeywordContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitColorTexturePropertyKeyword(this);
}

TdbParser::ColorTexturePropertyKeywordContext* TdbParser::colorTexturePropertyKeyword() {
  ColorTexturePropertyKeywordContext *_localctx = _tracker.createInstance<ColorTexturePropertyKeywordContext>(_ctx, getState());
  enterRule(_localctx, 12, TdbParser::RuleColorTexturePropertyKeyword);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(55);
    match(TdbParser::ChromaKey);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IntTexturePropertyContext ------------------------------------------------------------------

TdbParser::IntTexturePropertyContext::IntTexturePropertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TdbParser::IntTexturePropertyKeywordContext* TdbParser::IntTexturePropertyContext::intTexturePropertyKeyword() {
  return getRuleContext<TdbParser::IntTexturePropertyKeywordContext>(0);
}

tree::TerminalNode* TdbParser::IntTexturePropertyContext::IntegerConstant() {
  return getToken(TdbParser::IntegerConstant, 0);
}


size_t TdbParser::IntTexturePropertyContext::getRuleIndex() const {
  return TdbParser::RuleIntTextureProperty;
}

void TdbParser::IntTexturePropertyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIntTextureProperty(this);
}

void TdbParser::IntTexturePropertyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIntTextureProperty(this);
}

TdbParser::IntTexturePropertyContext* TdbParser::intTextureProperty() {
  IntTexturePropertyContext *_localctx = _tracker.createInstance<IntTexturePropertyContext>(_ctx, getState());
  enterRule(_localctx, 14, TdbParser::RuleIntTextureProperty);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(57);
    intTexturePropertyKeyword();
    setState(58);
    match(TdbParser::IntegerConstant);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IntTexturePropertyKeywordContext ------------------------------------------------------------------

TdbParser::IntTexturePropertyKeywordContext::IntTexturePropertyKeywordContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TdbParser::IntTexturePropertyKeywordContext::Keyword29() {
  return getToken(TdbParser::Keyword29, 0);
}


size_t TdbParser::IntTexturePropertyKeywordContext::getRuleIndex() const {
  return TdbParser::RuleIntTexturePropertyKeyword;
}

void TdbParser::IntTexturePropertyKeywordContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIntTexturePropertyKeyword(this);
}

void TdbParser::IntTexturePropertyKeywordContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIntTexturePropertyKeyword(this);
}

TdbParser::IntTexturePropertyKeywordContext* TdbParser::intTexturePropertyKeyword() {
  IntTexturePropertyKeywordContext *_localctx = _tracker.createInstance<IntTexturePropertyKeywordContext>(_ctx, getState());
  enterRule(_localctx, 16, TdbParser::RuleIntTexturePropertyKeyword);

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
    match(TdbParser::Keyword29);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SingleValueKeywordsContext ------------------------------------------------------------------

TdbParser::SingleValueKeywordsContext::SingleValueKeywordsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TdbParser::SingleValueKeywordsContext::FlipVertically() {
  return getToken(TdbParser::FlipVertically, 0);
}

tree::TerminalNode* TdbParser::SingleValueKeywordsContext::Bmp() {
  return getToken(TdbParser::Bmp, 0);
}

tree::TerminalNode* TdbParser::SingleValueKeywordsContext::Tga() {
  return getToken(TdbParser::Tga, 0);
}

tree::TerminalNode* TdbParser::SingleValueKeywordsContext::Keyword2D() {
  return getToken(TdbParser::Keyword2D, 0);
}

tree::TerminalNode* TdbParser::SingleValueKeywordsContext::Keyword2E() {
  return getToken(TdbParser::Keyword2E, 0);
}


size_t TdbParser::SingleValueKeywordsContext::getRuleIndex() const {
  return TdbParser::RuleSingleValueKeywords;
}

void TdbParser::SingleValueKeywordsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSingleValueKeywords(this);
}

void TdbParser::SingleValueKeywordsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSingleValueKeywords(this);
}

TdbParser::SingleValueKeywordsContext* TdbParser::singleValueKeywords() {
  SingleValueKeywordsContext *_localctx = _tracker.createInstance<SingleValueKeywordsContext>(_ctx, getState());
  enterRule(_localctx, 18, TdbParser::RuleSingleValueKeywords);
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
    setState(62);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << TdbParser::FlipVertically)
      | (1ULL << TdbParser::Bmp)
      | (1ULL << TdbParser::Tga)
      | (1ULL << TdbParser::Keyword2D)
      | (1ULL << TdbParser::Keyword2E))) != 0))) {
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

void TdbParser::initialize() {
  std::call_once(tdbParserOnceFlag, tdbParserInitialize);
}
