
// Generated from ..\..\..\src\JamFileTool\Parsing\Parser\Tdb\Tdb.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"


namespace tdb {


class  TdbParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, Textures = 3, Texture = 4, FlipVertically = 5, Keyword29 = 6, 
    Bmp = 7, Tga = 8, ChromaKey = 9, Keyword2D = 10, Keyword2E = 11, IntegerConstant = 12, 
    StringLiteral = 13, Whitespace = 14, Newline = 15, BlockComment = 16, 
    LineComment = 17
  };

  enum {
    RuleRoot = 0, RuleTextures = 1, RuleTexture = 2, RuleTextureName = 3, 
    RuleTextureProperty = 4, RuleColorTextureProperty = 5, RuleColorTexturePropertyKeyword = 6, 
    RuleIntTextureProperty = 7, RuleIntTexturePropertyKeyword = 8, RuleSingleValueKeywords = 9
  };

  explicit TdbParser(antlr4::TokenStream *input);

  TdbParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~TdbParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class RootContext;
  class TexturesContext;
  class TextureContext;
  class TextureNameContext;
  class TexturePropertyContext;
  class ColorTexturePropertyContext;
  class ColorTexturePropertyKeywordContext;
  class IntTexturePropertyContext;
  class IntTexturePropertyKeywordContext;
  class SingleValueKeywordsContext; 

  class  RootContext : public antlr4::ParserRuleContext {
  public:
    RootContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TexturesContext *textures();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RootContext* root();

  class  TexturesContext : public antlr4::ParserRuleContext {
  public:
    TexturesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Textures();
    std::vector<TextureContext *> texture();
    TextureContext* texture(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TexturesContext* textures();

  class  TextureContext : public antlr4::ParserRuleContext {
  public:
    TextureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Texture();
    TextureNameContext *textureName();
    std::vector<TexturePropertyContext *> textureProperty();
    TexturePropertyContext* textureProperty(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TextureContext* texture();

  class  TextureNameContext : public antlr4::ParserRuleContext {
  public:
    TextureNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *StringLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TextureNameContext* textureName();

  class  TexturePropertyContext : public antlr4::ParserRuleContext {
  public:
    TexturePropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ColorTexturePropertyContext *colorTextureProperty();
    IntTexturePropertyContext *intTextureProperty();
    SingleValueKeywordsContext *singleValueKeywords();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TexturePropertyContext* textureProperty();

  class  ColorTexturePropertyContext : public antlr4::ParserRuleContext {
  public:
    ColorTexturePropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ColorTexturePropertyKeywordContext *colorTexturePropertyKeyword();
    std::vector<antlr4::tree::TerminalNode *> IntegerConstant();
    antlr4::tree::TerminalNode* IntegerConstant(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ColorTexturePropertyContext* colorTextureProperty();

  class  ColorTexturePropertyKeywordContext : public antlr4::ParserRuleContext {
  public:
    ColorTexturePropertyKeywordContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ChromaKey();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ColorTexturePropertyKeywordContext* colorTexturePropertyKeyword();

  class  IntTexturePropertyContext : public antlr4::ParserRuleContext {
  public:
    IntTexturePropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IntTexturePropertyKeywordContext *intTexturePropertyKeyword();
    antlr4::tree::TerminalNode *IntegerConstant();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IntTexturePropertyContext* intTextureProperty();

  class  IntTexturePropertyKeywordContext : public antlr4::ParserRuleContext {
  public:
    IntTexturePropertyKeywordContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Keyword29();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IntTexturePropertyKeywordContext* intTexturePropertyKeyword();

  class  SingleValueKeywordsContext : public antlr4::ParserRuleContext {
  public:
    SingleValueKeywordsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FlipVertically();
    antlr4::tree::TerminalNode *Bmp();
    antlr4::tree::TerminalNode *Tga();
    antlr4::tree::TerminalNode *Keyword2D();
    antlr4::tree::TerminalNode *Keyword2E();

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

}  // namespace tdb
