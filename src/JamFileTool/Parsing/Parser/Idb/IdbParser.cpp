
// Generated from ..\..\..\src\JamFileTool\Parsing\Parser\Idb\Idb.g4 by ANTLR 4.10.1


#include "IdbListener.h"

#include "IdbParser.h"


using namespace antlrcpp;
using namespace idb;

using namespace antlr4;

namespace {

struct IdbParserStaticData final {
  IdbParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  IdbParserStaticData(const IdbParserStaticData&) = delete;
  IdbParserStaticData(IdbParserStaticData&&) = delete;
  IdbParserStaticData& operator=(const IdbParserStaticData&) = delete;
  IdbParserStaticData& operator=(IdbParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag idbParserOnceFlag;
IdbParserStaticData *idbParserStaticData = nullptr;

void idbParserInitialize() {
  assert(idbParserStaticData == nullptr);
  auto staticData = std::make_unique<IdbParserStaticData>(
    std::vector<std::string>{
      "root", "images", "image", "imageName", "imageProperty", "colorImageProperty", 
      "colorImagePropertyKeyword", "singleValueKeywords", "floatOrIntConstant"
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
  	4,1,17,59,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,7,
  	7,7,2,8,7,8,1,0,1,0,1,1,1,1,1,1,5,1,24,8,1,10,1,12,1,27,9,1,1,1,1,1,1,
  	2,1,2,1,2,1,2,5,2,35,8,2,10,2,12,2,38,9,2,1,2,1,2,1,3,1,3,1,4,1,4,3,4,
  	46,8,4,1,5,1,5,1,5,1,5,1,5,1,6,1,6,1,7,1,7,1,8,1,8,1,8,0,0,9,0,2,4,6,
  	8,10,12,14,16,0,3,1,0,8,9,1,0,5,7,1,0,10,11,52,0,18,1,0,0,0,2,20,1,0,
  	0,0,4,30,1,0,0,0,6,41,1,0,0,0,8,45,1,0,0,0,10,47,1,0,0,0,12,52,1,0,0,
  	0,14,54,1,0,0,0,16,56,1,0,0,0,18,19,3,2,1,0,19,1,1,0,0,0,20,21,5,3,0,
  	0,21,25,5,1,0,0,22,24,3,4,2,0,23,22,1,0,0,0,24,27,1,0,0,0,25,23,1,0,0,
  	0,25,26,1,0,0,0,26,28,1,0,0,0,27,25,1,0,0,0,28,29,5,2,0,0,29,3,1,0,0,
  	0,30,31,5,4,0,0,31,32,3,6,3,0,32,36,5,1,0,0,33,35,3,8,4,0,34,33,1,0,0,
  	0,35,38,1,0,0,0,36,34,1,0,0,0,36,37,1,0,0,0,37,39,1,0,0,0,38,36,1,0,0,
  	0,39,40,5,2,0,0,40,5,1,0,0,0,41,42,5,13,0,0,42,7,1,0,0,0,43,46,3,10,5,
  	0,44,46,3,14,7,0,45,43,1,0,0,0,45,44,1,0,0,0,46,9,1,0,0,0,47,48,3,12,
  	6,0,48,49,5,10,0,0,49,50,5,10,0,0,50,51,5,10,0,0,51,11,1,0,0,0,52,53,
  	7,0,0,0,53,13,1,0,0,0,54,55,7,1,0,0,55,15,1,0,0,0,56,57,7,2,0,0,57,17,
  	1,0,0,0,3,25,36,45
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  idbParserStaticData = staticData.release();
}

}

IdbParser::IdbParser(TokenStream *input) : IdbParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

IdbParser::IdbParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  IdbParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *idbParserStaticData->atn, idbParserStaticData->decisionToDFA, idbParserStaticData->sharedContextCache, options);
}

IdbParser::~IdbParser() {
  delete _interpreter;
}

const atn::ATN& IdbParser::getATN() const {
  return *idbParserStaticData->atn;
}

std::string IdbParser::getGrammarFileName() const {
  return "Idb.g4";
}

const std::vector<std::string>& IdbParser::getRuleNames() const {
  return idbParserStaticData->ruleNames;
}

const dfa::Vocabulary& IdbParser::getVocabulary() const {
  return idbParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView IdbParser::getSerializedATN() const {
  return idbParserStaticData->serializedATN;
}


//----------------- RootContext ------------------------------------------------------------------

IdbParser::RootContext::RootContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IdbParser::ImagesContext* IdbParser::RootContext::images() {
  return getRuleContext<IdbParser::ImagesContext>(0);
}


size_t IdbParser::RootContext::getRuleIndex() const {
  return IdbParser::RuleRoot;
}

void IdbParser::RootContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRoot(this);
}

void IdbParser::RootContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRoot(this);
}

IdbParser::RootContext* IdbParser::root() {
  RootContext *_localctx = _tracker.createInstance<RootContext>(_ctx, getState());
  enterRule(_localctx, 0, IdbParser::RuleRoot);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(18);
    images();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImagesContext ------------------------------------------------------------------

IdbParser::ImagesContext::ImagesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IdbParser::ImagesContext::Images() {
  return getToken(IdbParser::Images, 0);
}

std::vector<IdbParser::ImageContext *> IdbParser::ImagesContext::image() {
  return getRuleContexts<IdbParser::ImageContext>();
}

IdbParser::ImageContext* IdbParser::ImagesContext::image(size_t i) {
  return getRuleContext<IdbParser::ImageContext>(i);
}


size_t IdbParser::ImagesContext::getRuleIndex() const {
  return IdbParser::RuleImages;
}

void IdbParser::ImagesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImages(this);
}

void IdbParser::ImagesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImages(this);
}

IdbParser::ImagesContext* IdbParser::images() {
  ImagesContext *_localctx = _tracker.createInstance<ImagesContext>(_ctx, getState());
  enterRule(_localctx, 2, IdbParser::RuleImages);
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
    setState(20);
    match(IdbParser::Images);
    setState(21);
    match(IdbParser::T__0);
    setState(25);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IdbParser::Image) {
      setState(22);
      image();
      setState(27);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(28);
    match(IdbParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImageContext ------------------------------------------------------------------

IdbParser::ImageContext::ImageContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IdbParser::ImageContext::Image() {
  return getToken(IdbParser::Image, 0);
}

IdbParser::ImageNameContext* IdbParser::ImageContext::imageName() {
  return getRuleContext<IdbParser::ImageNameContext>(0);
}

std::vector<IdbParser::ImagePropertyContext *> IdbParser::ImageContext::imageProperty() {
  return getRuleContexts<IdbParser::ImagePropertyContext>();
}

IdbParser::ImagePropertyContext* IdbParser::ImageContext::imageProperty(size_t i) {
  return getRuleContext<IdbParser::ImagePropertyContext>(i);
}


size_t IdbParser::ImageContext::getRuleIndex() const {
  return IdbParser::RuleImage;
}

void IdbParser::ImageContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImage(this);
}

void IdbParser::ImageContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImage(this);
}

IdbParser::ImageContext* IdbParser::image() {
  ImageContext *_localctx = _tracker.createInstance<ImageContext>(_ctx, getState());
  enterRule(_localctx, 4, IdbParser::RuleImage);
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
    setState(30);
    match(IdbParser::Image);
    setState(31);
    imageName();
    setState(32);
    match(IdbParser::T__0);
    setState(36);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IdbParser::FlipVertical)
      | (1ULL << IdbParser::Bmp)
      | (1ULL << IdbParser::Tga)
      | (1ULL << IdbParser::ChromaKey)
      | (1ULL << IdbParser::Tint))) != 0)) {
      setState(33);
      imageProperty();
      setState(38);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(39);
    match(IdbParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImageNameContext ------------------------------------------------------------------

IdbParser::ImageNameContext::ImageNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IdbParser::ImageNameContext::StringLiteral() {
  return getToken(IdbParser::StringLiteral, 0);
}


size_t IdbParser::ImageNameContext::getRuleIndex() const {
  return IdbParser::RuleImageName;
}

void IdbParser::ImageNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImageName(this);
}

void IdbParser::ImageNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImageName(this);
}

IdbParser::ImageNameContext* IdbParser::imageName() {
  ImageNameContext *_localctx = _tracker.createInstance<ImageNameContext>(_ctx, getState());
  enterRule(_localctx, 6, IdbParser::RuleImageName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(41);
    match(IdbParser::StringLiteral);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImagePropertyContext ------------------------------------------------------------------

IdbParser::ImagePropertyContext::ImagePropertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IdbParser::ColorImagePropertyContext* IdbParser::ImagePropertyContext::colorImageProperty() {
  return getRuleContext<IdbParser::ColorImagePropertyContext>(0);
}

IdbParser::SingleValueKeywordsContext* IdbParser::ImagePropertyContext::singleValueKeywords() {
  return getRuleContext<IdbParser::SingleValueKeywordsContext>(0);
}


size_t IdbParser::ImagePropertyContext::getRuleIndex() const {
  return IdbParser::RuleImageProperty;
}

void IdbParser::ImagePropertyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImageProperty(this);
}

void IdbParser::ImagePropertyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImageProperty(this);
}

IdbParser::ImagePropertyContext* IdbParser::imageProperty() {
  ImagePropertyContext *_localctx = _tracker.createInstance<ImagePropertyContext>(_ctx, getState());
  enterRule(_localctx, 8, IdbParser::RuleImageProperty);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(45);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IdbParser::ChromaKey:
      case IdbParser::Tint: {
        enterOuterAlt(_localctx, 1);
        setState(43);
        colorImageProperty();
        break;
      }

      case IdbParser::FlipVertical:
      case IdbParser::Bmp:
      case IdbParser::Tga: {
        enterOuterAlt(_localctx, 2);
        setState(44);
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

//----------------- ColorImagePropertyContext ------------------------------------------------------------------

IdbParser::ColorImagePropertyContext::ColorImagePropertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IdbParser::ColorImagePropertyKeywordContext* IdbParser::ColorImagePropertyContext::colorImagePropertyKeyword() {
  return getRuleContext<IdbParser::ColorImagePropertyKeywordContext>(0);
}

std::vector<tree::TerminalNode *> IdbParser::ColorImagePropertyContext::IntegerConstant() {
  return getTokens(IdbParser::IntegerConstant);
}

tree::TerminalNode* IdbParser::ColorImagePropertyContext::IntegerConstant(size_t i) {
  return getToken(IdbParser::IntegerConstant, i);
}


size_t IdbParser::ColorImagePropertyContext::getRuleIndex() const {
  return IdbParser::RuleColorImageProperty;
}

void IdbParser::ColorImagePropertyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterColorImageProperty(this);
}

void IdbParser::ColorImagePropertyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitColorImageProperty(this);
}

IdbParser::ColorImagePropertyContext* IdbParser::colorImageProperty() {
  ColorImagePropertyContext *_localctx = _tracker.createInstance<ColorImagePropertyContext>(_ctx, getState());
  enterRule(_localctx, 10, IdbParser::RuleColorImageProperty);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(47);
    colorImagePropertyKeyword();
    setState(48);
    match(IdbParser::IntegerConstant);
    setState(49);
    match(IdbParser::IntegerConstant);
    setState(50);
    match(IdbParser::IntegerConstant);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ColorImagePropertyKeywordContext ------------------------------------------------------------------

IdbParser::ColorImagePropertyKeywordContext::ColorImagePropertyKeywordContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IdbParser::ColorImagePropertyKeywordContext::ChromaKey() {
  return getToken(IdbParser::ChromaKey, 0);
}

tree::TerminalNode* IdbParser::ColorImagePropertyKeywordContext::Tint() {
  return getToken(IdbParser::Tint, 0);
}


size_t IdbParser::ColorImagePropertyKeywordContext::getRuleIndex() const {
  return IdbParser::RuleColorImagePropertyKeyword;
}

void IdbParser::ColorImagePropertyKeywordContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterColorImagePropertyKeyword(this);
}

void IdbParser::ColorImagePropertyKeywordContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitColorImagePropertyKeyword(this);
}

IdbParser::ColorImagePropertyKeywordContext* IdbParser::colorImagePropertyKeyword() {
  ColorImagePropertyKeywordContext *_localctx = _tracker.createInstance<ColorImagePropertyKeywordContext>(_ctx, getState());
  enterRule(_localctx, 12, IdbParser::RuleColorImagePropertyKeyword);
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
    setState(52);
    _la = _input->LA(1);
    if (!(_la == IdbParser::ChromaKey

    || _la == IdbParser::Tint)) {
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

IdbParser::SingleValueKeywordsContext::SingleValueKeywordsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IdbParser::SingleValueKeywordsContext::FlipVertical() {
  return getToken(IdbParser::FlipVertical, 0);
}

tree::TerminalNode* IdbParser::SingleValueKeywordsContext::Bmp() {
  return getToken(IdbParser::Bmp, 0);
}

tree::TerminalNode* IdbParser::SingleValueKeywordsContext::Tga() {
  return getToken(IdbParser::Tga, 0);
}


size_t IdbParser::SingleValueKeywordsContext::getRuleIndex() const {
  return IdbParser::RuleSingleValueKeywords;
}

void IdbParser::SingleValueKeywordsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSingleValueKeywords(this);
}

void IdbParser::SingleValueKeywordsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSingleValueKeywords(this);
}

IdbParser::SingleValueKeywordsContext* IdbParser::singleValueKeywords() {
  SingleValueKeywordsContext *_localctx = _tracker.createInstance<SingleValueKeywordsContext>(_ctx, getState());
  enterRule(_localctx, 14, IdbParser::RuleSingleValueKeywords);
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
    setState(54);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IdbParser::FlipVertical)
      | (1ULL << IdbParser::Bmp)
      | (1ULL << IdbParser::Tga))) != 0))) {
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

//----------------- FloatOrIntConstantContext ------------------------------------------------------------------

IdbParser::FloatOrIntConstantContext::FloatOrIntConstantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IdbParser::FloatOrIntConstantContext::FloatingConstant() {
  return getToken(IdbParser::FloatingConstant, 0);
}

tree::TerminalNode* IdbParser::FloatOrIntConstantContext::IntegerConstant() {
  return getToken(IdbParser::IntegerConstant, 0);
}


size_t IdbParser::FloatOrIntConstantContext::getRuleIndex() const {
  return IdbParser::RuleFloatOrIntConstant;
}

void IdbParser::FloatOrIntConstantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFloatOrIntConstant(this);
}

void IdbParser::FloatOrIntConstantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IdbListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFloatOrIntConstant(this);
}

IdbParser::FloatOrIntConstantContext* IdbParser::floatOrIntConstant() {
  FloatOrIntConstantContext *_localctx = _tracker.createInstance<FloatOrIntConstantContext>(_ctx, getState());
  enterRule(_localctx, 16, IdbParser::RuleFloatOrIntConstant);
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
    setState(56);
    _la = _input->LA(1);
    if (!(_la == IdbParser::IntegerConstant

    || _la == IdbParser::FloatingConstant)) {
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

void IdbParser::initialize() {
  std::call_once(idbParserOnceFlag, idbParserInitialize);
}
