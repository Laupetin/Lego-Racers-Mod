
// Generated from ..\..\..\src\JamFileTool\Parsing\Parser\Mdb\Mdb.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"


namespace mdb {


class  MdbParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, Materials = 3, Material = 4, Color1 = 5, Color0 = 6, 
    Keyword2A = 7, Keyword2B = 8, Texture = 9, Keyword2D = 10, Keyword2E = 11, 
    Keyword2F = 12, Keyword30 = 13, Keyword31 = 14, Keyword32 = 15, Keyword33 = 16, 
    Keyword34 = 17, Keyword35 = 18, Keyword36 = 19, Keyword37 = 20, Keyword38 = 21, 
    Keyword39 = 22, Keyword3A = 23, Keyword3B = 24, Keyword3C = 25, Keyword3D = 26, 
    Keyword3E = 27, Keyword3F = 28, Keyword40 = 29, Keyword41 = 30, Keyword42 = 31, 
    Keyword43 = 32, Keyword44 = 33, Keyword45 = 34, Opacity = 35, Keyword47 = 36, 
    Keyword48 = 37, Keyword49 = 38, Keyword4A = 39, Keyword4B = 40, Keyword4C = 41, 
    Keyword4D = 42, Keyword4E = 43, Keyword4F = 44, Keyword50 = 45, IntegerConstant = 46, 
    FloatingConstant = 47, DigitSequence = 48, StringLiteral = 49, Whitespace = 50, 
    Newline = 51, BlockComment = 52, LineComment = 53
  };

  enum {
    RuleRoot = 0, RuleMaterials = 1, RuleMaterial = 2, RuleMaterialName = 3, 
    RuleMaterialProperty = 4, RuleColorMaterialProperty = 5, RuleColorMaterialPropertyKeyword = 6, 
    RuleTextMaterialProperty = 7, RuleTextMaterialPropertyKeyword = 8, RuleUint8MaterialProperty = 9, 
    RuleUint8MaterialPropertyKeyword = 10, RuleIntMaterialProperty = 11, 
    RuleIntMaterialPropertyKeyword = 12, RuleSingleValueKeywords = 13, RuleKeyword2F = 14, 
    RuleKeyword2FSubtoken = 15, RuleKeyword38 = 16, RuleKeyword38Subtoken = 17, 
    RuleFloatOrIntConstant = 18
  };

  explicit MdbParser(antlr4::TokenStream *input);

  MdbParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~MdbParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class RootContext;
  class MaterialsContext;
  class MaterialContext;
  class MaterialNameContext;
  class MaterialPropertyContext;
  class ColorMaterialPropertyContext;
  class ColorMaterialPropertyKeywordContext;
  class TextMaterialPropertyContext;
  class TextMaterialPropertyKeywordContext;
  class Uint8MaterialPropertyContext;
  class Uint8MaterialPropertyKeywordContext;
  class IntMaterialPropertyContext;
  class IntMaterialPropertyKeywordContext;
  class SingleValueKeywordsContext;
  class Keyword2FContext;
  class Keyword2FSubtokenContext;
  class Keyword38Context;
  class Keyword38SubtokenContext;
  class FloatOrIntConstantContext; 

  class  RootContext : public antlr4::ParserRuleContext {
  public:
    RootContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MaterialsContext *materials();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RootContext* root();

  class  MaterialsContext : public antlr4::ParserRuleContext {
  public:
    MaterialsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Materials();
    std::vector<MaterialContext *> material();
    MaterialContext* material(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MaterialsContext* materials();

  class  MaterialContext : public antlr4::ParserRuleContext {
  public:
    MaterialContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Material();
    MaterialNameContext *materialName();
    std::vector<MaterialPropertyContext *> materialProperty();
    MaterialPropertyContext* materialProperty(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MaterialContext* material();

  class  MaterialNameContext : public antlr4::ParserRuleContext {
  public:
    MaterialNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *StringLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MaterialNameContext* materialName();

  class  MaterialPropertyContext : public antlr4::ParserRuleContext {
  public:
    MaterialPropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ColorMaterialPropertyContext *colorMaterialProperty();
    TextMaterialPropertyContext *textMaterialProperty();
    Uint8MaterialPropertyContext *uint8MaterialProperty();
    IntMaterialPropertyContext *intMaterialProperty();
    SingleValueKeywordsContext *singleValueKeywords();
    Keyword2FContext *keyword2F();
    Keyword38Context *keyword38();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MaterialPropertyContext* materialProperty();

  class  ColorMaterialPropertyContext : public antlr4::ParserRuleContext {
  public:
    ColorMaterialPropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ColorMaterialPropertyKeywordContext *colorMaterialPropertyKeyword();
    std::vector<antlr4::tree::TerminalNode *> IntegerConstant();
    antlr4::tree::TerminalNode* IntegerConstant(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ColorMaterialPropertyContext* colorMaterialProperty();

  class  ColorMaterialPropertyKeywordContext : public antlr4::ParserRuleContext {
  public:
    ColorMaterialPropertyKeywordContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Color0();
    antlr4::tree::TerminalNode *Color1();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ColorMaterialPropertyKeywordContext* colorMaterialPropertyKeyword();

  class  TextMaterialPropertyContext : public antlr4::ParserRuleContext {
  public:
    TextMaterialPropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TextMaterialPropertyKeywordContext *textMaterialPropertyKeyword();
    antlr4::tree::TerminalNode *StringLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TextMaterialPropertyContext* textMaterialProperty();

  class  TextMaterialPropertyKeywordContext : public antlr4::ParserRuleContext {
  public:
    TextMaterialPropertyKeywordContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Texture();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TextMaterialPropertyKeywordContext* textMaterialPropertyKeyword();

  class  Uint8MaterialPropertyContext : public antlr4::ParserRuleContext {
  public:
    Uint8MaterialPropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Uint8MaterialPropertyKeywordContext *uint8MaterialPropertyKeyword();
    antlr4::tree::TerminalNode *IntegerConstant();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Uint8MaterialPropertyContext* uint8MaterialProperty();

  class  Uint8MaterialPropertyKeywordContext : public antlr4::ParserRuleContext {
  public:
    Uint8MaterialPropertyKeywordContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Opacity();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Uint8MaterialPropertyKeywordContext* uint8MaterialPropertyKeyword();

  class  IntMaterialPropertyContext : public antlr4::ParserRuleContext {
  public:
    IntMaterialPropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IntMaterialPropertyKeywordContext *intMaterialPropertyKeyword();
    antlr4::tree::TerminalNode *IntegerConstant();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IntMaterialPropertyContext* intMaterialProperty();

  class  IntMaterialPropertyKeywordContext : public antlr4::ParserRuleContext {
  public:
    IntMaterialPropertyKeywordContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Keyword4D();
    antlr4::tree::TerminalNode *Keyword4E();
    antlr4::tree::TerminalNode *Keyword4F();
    antlr4::tree::TerminalNode *Keyword50();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IntMaterialPropertyKeywordContext* intMaterialPropertyKeyword();

  class  SingleValueKeywordsContext : public antlr4::ParserRuleContext {
  public:
    SingleValueKeywordsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Keyword2A();
    antlr4::tree::TerminalNode *Keyword2B();
    antlr4::tree::TerminalNode *Keyword2D();
    antlr4::tree::TerminalNode *Keyword2E();
    antlr4::tree::TerminalNode *Keyword44();
    antlr4::tree::TerminalNode *Keyword45();
    antlr4::tree::TerminalNode *Keyword47();
    antlr4::tree::TerminalNode *Keyword48();
    antlr4::tree::TerminalNode *Keyword49();
    antlr4::tree::TerminalNode *Keyword4A();
    antlr4::tree::TerminalNode *Keyword4B();
    antlr4::tree::TerminalNode *Keyword4C();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SingleValueKeywordsContext* singleValueKeywords();

  class  Keyword2FContext : public antlr4::ParserRuleContext {
  public:
    Keyword2FContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Keyword2F();
    Keyword2FSubtokenContext *keyword2FSubtoken();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Keyword2FContext* keyword2F();

  class  Keyword2FSubtokenContext : public antlr4::ParserRuleContext {
  public:
    Keyword2FSubtokenContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Keyword30();
    antlr4::tree::TerminalNode *Keyword31();
    antlr4::tree::TerminalNode *IntegerConstant();
    antlr4::tree::TerminalNode *Keyword32();
    antlr4::tree::TerminalNode *Keyword33();
    antlr4::tree::TerminalNode *Keyword34();
    antlr4::tree::TerminalNode *Keyword35();
    antlr4::tree::TerminalNode *Keyword36();
    antlr4::tree::TerminalNode *Keyword37();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Keyword2FSubtokenContext* keyword2FSubtoken();

  class  Keyword38Context : public antlr4::ParserRuleContext {
  public:
    Keyword38Context(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Keyword38();
    std::vector<Keyword38SubtokenContext *> keyword38Subtoken();
    Keyword38SubtokenContext* keyword38Subtoken(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Keyword38Context* keyword38();

  class  Keyword38SubtokenContext : public antlr4::ParserRuleContext {
  public:
    Keyword38SubtokenContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Keyword39();
    antlr4::tree::TerminalNode *Keyword3A();
    antlr4::tree::TerminalNode *Keyword3B();
    antlr4::tree::TerminalNode *Keyword3C();
    antlr4::tree::TerminalNode *Keyword3D();
    antlr4::tree::TerminalNode *Keyword3E();
    antlr4::tree::TerminalNode *Keyword3F();
    antlr4::tree::TerminalNode *Keyword40();
    antlr4::tree::TerminalNode *Keyword41();
    antlr4::tree::TerminalNode *Keyword42();
    antlr4::tree::TerminalNode *Keyword43();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Keyword38SubtokenContext* keyword38Subtoken();

  class  FloatOrIntConstantContext : public antlr4::ParserRuleContext {
  public:
    FloatOrIntConstantContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FloatingConstant();
    antlr4::tree::TerminalNode *IntegerConstant();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FloatOrIntConstantContext* floatOrIntConstant();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

}  // namespace mdb
