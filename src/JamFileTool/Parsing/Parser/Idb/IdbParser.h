
// Generated from ..\..\..\src\JamFileTool\Parsing\Parser\Idb\Idb.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"


namespace idb {


class  IdbParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, Images = 3, Image = 4, FlipVertical = 5, Bmp = 6, 
    Tga = 7, ChromaKey = 8, Tint = 9, IntegerConstant = 10, FloatingConstant = 11, 
    DigitSequence = 12, StringLiteral = 13, Whitespace = 14, Newline = 15, 
    BlockComment = 16, LineComment = 17
  };

  enum {
    RuleRoot = 0, RuleImages = 1, RuleImage = 2, RuleImageName = 3, RuleImageProperty = 4, 
    RuleColorImageProperty = 5, RuleColorImagePropertyKeyword = 6, RuleSingleValueKeywords = 7
  };

  explicit IdbParser(antlr4::TokenStream *input);

  IdbParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~IdbParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class RootContext;
  class ImagesContext;
  class ImageContext;
  class ImageNameContext;
  class ImagePropertyContext;
  class ColorImagePropertyContext;
  class ColorImagePropertyKeywordContext;
  class SingleValueKeywordsContext; 

  class  RootContext : public antlr4::ParserRuleContext {
  public:
    RootContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ImagesContext *images();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RootContext* root();

  class  ImagesContext : public antlr4::ParserRuleContext {
  public:
    ImagesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Images();
    std::vector<ImageContext *> image();
    ImageContext* image(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ImagesContext* images();

  class  ImageContext : public antlr4::ParserRuleContext {
  public:
    ImageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Image();
    ImageNameContext *imageName();
    std::vector<ImagePropertyContext *> imageProperty();
    ImagePropertyContext* imageProperty(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ImageContext* image();

  class  ImageNameContext : public antlr4::ParserRuleContext {
  public:
    ImageNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *StringLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ImageNameContext* imageName();

  class  ImagePropertyContext : public antlr4::ParserRuleContext {
  public:
    ImagePropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ColorImagePropertyContext *colorImageProperty();
    SingleValueKeywordsContext *singleValueKeywords();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ImagePropertyContext* imageProperty();

  class  ColorImagePropertyContext : public antlr4::ParserRuleContext {
  public:
    ColorImagePropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ColorImagePropertyKeywordContext *colorImagePropertyKeyword();
    std::vector<antlr4::tree::TerminalNode *> IntegerConstant();
    antlr4::tree::TerminalNode* IntegerConstant(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ColorImagePropertyContext* colorImageProperty();

  class  ColorImagePropertyKeywordContext : public antlr4::ParserRuleContext {
  public:
    ColorImagePropertyKeywordContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ChromaKey();
    antlr4::tree::TerminalNode *Tint();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ColorImagePropertyKeywordContext* colorImagePropertyKeyword();

  class  SingleValueKeywordsContext : public antlr4::ParserRuleContext {
  public:
    SingleValueKeywordsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FlipVertical();
    antlr4::tree::TerminalNode *Bmp();
    antlr4::tree::TerminalNode *Tga();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SingleValueKeywordsContext* singleValueKeywords();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

}  // namespace idb
