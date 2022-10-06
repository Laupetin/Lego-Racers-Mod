
// Generated from ..\..\..\src\JamFileTool\Parsing\Parser\Gdb\Gdb.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"


namespace gdb {


class  GdbParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, Materials = 3, Scale = 4, Vertices = 5, Faces = 6, 
    Meta = 7, Vertex = 8, Uv = 9, Color = 10, Normal = 11, Texture = 12, 
    Face = 13, Keyword27 = 14, Keyword2D = 15, Keyword2F = 16, Keyword30 = 17, 
    Keyword31 = 18, Keyword32 = 19, IntegerConstant = 20, FloatingConstant = 21, 
    DigitSequence = 22, StringLiteral = 23, Whitespace = 24, Newline = 25, 
    BlockComment = 26, LineComment = 27
  };

  enum {
    RuleRoot = 0, RuleSections = 1, RuleMaterialSection = 2, RuleMaterialNameList = 3, 
    RuleMaterialName = 4, RuleScaleSection = 5, RuleVertexSection = 6, RuleVertexList = 7, 
    RuleVertexDefPosition = 8, RuleVertexDefPositionUv = 9, RuleVertexDefPositionUvColor = 10, 
    RuleVertexDefPositionUvNormal = 11, RuleVertexPosition = 12, RuleVertexUv = 13, 
    RuleVertexColor = 14, RuleVertexNormal = 15, RuleFaceSection = 16, RuleFaceList = 17, 
    RuleFace = 18, RuleMetaSection = 19, RuleMetaList = 20, RuleMeta = 21, 
    RuleKeyword31 = 22, RuleKeyword2D = 23, RuleKeyword2F = 24, RuleKeyword30 = 25, 
    RuleKeyword32 = 26, RuleKeyword27 = 27, RuleFloatOrIntConstant = 28
  };

  explicit GdbParser(antlr4::TokenStream *input);

  GdbParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~GdbParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class RootContext;
  class SectionsContext;
  class MaterialSectionContext;
  class MaterialNameListContext;
  class MaterialNameContext;
  class ScaleSectionContext;
  class VertexSectionContext;
  class VertexListContext;
  class VertexDefPositionContext;
  class VertexDefPositionUvContext;
  class VertexDefPositionUvColorContext;
  class VertexDefPositionUvNormalContext;
  class VertexPositionContext;
  class VertexUvContext;
  class VertexColorContext;
  class VertexNormalContext;
  class FaceSectionContext;
  class FaceListContext;
  class FaceContext;
  class MetaSectionContext;
  class MetaListContext;
  class MetaContext;
  class Keyword31Context;
  class Keyword2DContext;
  class Keyword2FContext;
  class Keyword30Context;
  class Keyword32Context;
  class Keyword27Context;
  class FloatOrIntConstantContext; 

  class  RootContext : public antlr4::ParserRuleContext {
  public:
    RootContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SectionsContext *sections();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RootContext* root();

  class  SectionsContext : public antlr4::ParserRuleContext {
  public:
    SectionsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MaterialSectionContext *materialSection();
    ScaleSectionContext *scaleSection();
    VertexSectionContext *vertexSection();
    FaceSectionContext *faceSection();
    MetaSectionContext *metaSection();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SectionsContext* sections();

  class  MaterialSectionContext : public antlr4::ParserRuleContext {
  public:
    MaterialSectionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Materials();
    MaterialNameListContext *materialNameList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MaterialSectionContext* materialSection();

  class  MaterialNameListContext : public antlr4::ParserRuleContext {
  public:
    MaterialNameListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<MaterialNameContext *> materialName();
    MaterialNameContext* materialName(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MaterialNameListContext* materialNameList();

  class  MaterialNameContext : public antlr4::ParserRuleContext {
  public:
    MaterialNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *StringLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MaterialNameContext* materialName();

  class  ScaleSectionContext : public antlr4::ParserRuleContext {
  public:
    ScaleSectionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Scale();
    FloatOrIntConstantContext *floatOrIntConstant();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ScaleSectionContext* scaleSection();

  class  VertexSectionContext : public antlr4::ParserRuleContext {
  public:
    VertexSectionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Vertices();
    VertexListContext *vertexList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VertexSectionContext* vertexSection();

  class  VertexListContext : public antlr4::ParserRuleContext {
  public:
    VertexListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<VertexDefPositionUvColorContext *> vertexDefPositionUvColor();
    VertexDefPositionUvColorContext* vertexDefPositionUvColor(size_t i);
    std::vector<VertexDefPositionUvNormalContext *> vertexDefPositionUvNormal();
    VertexDefPositionUvNormalContext* vertexDefPositionUvNormal(size_t i);
    std::vector<VertexDefPositionUvContext *> vertexDefPositionUv();
    VertexDefPositionUvContext* vertexDefPositionUv(size_t i);
    std::vector<VertexDefPositionContext *> vertexDefPosition();
    VertexDefPositionContext* vertexDefPosition(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VertexListContext* vertexList();

  class  VertexDefPositionContext : public antlr4::ParserRuleContext {
  public:
    VertexDefPositionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VertexPositionContext *vertexPosition();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VertexDefPositionContext* vertexDefPosition();

  class  VertexDefPositionUvContext : public antlr4::ParserRuleContext {
  public:
    VertexDefPositionUvContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VertexPositionContext *vertexPosition();
    VertexUvContext *vertexUv();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VertexDefPositionUvContext* vertexDefPositionUv();

  class  VertexDefPositionUvColorContext : public antlr4::ParserRuleContext {
  public:
    VertexDefPositionUvColorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VertexPositionContext *vertexPosition();
    VertexUvContext *vertexUv();
    VertexColorContext *vertexColor();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VertexDefPositionUvColorContext* vertexDefPositionUvColor();

  class  VertexDefPositionUvNormalContext : public antlr4::ParserRuleContext {
  public:
    VertexDefPositionUvNormalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VertexPositionContext *vertexPosition();
    VertexUvContext *vertexUv();
    VertexNormalContext *vertexNormal();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VertexDefPositionUvNormalContext* vertexDefPositionUvNormal();

  class  VertexPositionContext : public antlr4::ParserRuleContext {
  public:
    VertexPositionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Vertex();
    std::vector<FloatOrIntConstantContext *> floatOrIntConstant();
    FloatOrIntConstantContext* floatOrIntConstant(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VertexPositionContext* vertexPosition();

  class  VertexUvContext : public antlr4::ParserRuleContext {
  public:
    VertexUvContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Uv();
    std::vector<FloatOrIntConstantContext *> floatOrIntConstant();
    FloatOrIntConstantContext* floatOrIntConstant(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VertexUvContext* vertexUv();

  class  VertexColorContext : public antlr4::ParserRuleContext {
  public:
    VertexColorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Color();
    std::vector<antlr4::tree::TerminalNode *> IntegerConstant();
    antlr4::tree::TerminalNode* IntegerConstant(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VertexColorContext* vertexColor();

  class  VertexNormalContext : public antlr4::ParserRuleContext {
  public:
    VertexNormalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Normal();
    std::vector<FloatOrIntConstantContext *> floatOrIntConstant();
    FloatOrIntConstantContext* floatOrIntConstant(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VertexNormalContext* vertexNormal();

  class  FaceSectionContext : public antlr4::ParserRuleContext {
  public:
    FaceSectionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Faces();
    FaceListContext *faceList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FaceSectionContext* faceSection();

  class  FaceListContext : public antlr4::ParserRuleContext {
  public:
    FaceListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<FaceContext *> face();
    FaceContext* face(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FaceListContext* faceList();

  class  FaceContext : public antlr4::ParserRuleContext {
  public:
    FaceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Face();
    std::vector<antlr4::tree::TerminalNode *> IntegerConstant();
    antlr4::tree::TerminalNode* IntegerConstant(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FaceContext* face();

  class  MetaSectionContext : public antlr4::ParserRuleContext {
  public:
    MetaSectionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Meta();
    MetaListContext *metaList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MetaSectionContext* metaSection();

  class  MetaListContext : public antlr4::ParserRuleContext {
  public:
    MetaListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<MetaContext *> meta();
    MetaContext* meta(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MetaListContext* metaList();

  class  MetaContext : public antlr4::ParserRuleContext {
  public:
    MetaContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Keyword31Context *keyword31();
    Keyword2DContext *keyword2D();
    Keyword2FContext *keyword2F();
    Keyword30Context *keyword30();
    Keyword32Context *keyword32();
    Keyword27Context *keyword27();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MetaContext* meta();

  class  Keyword31Context : public antlr4::ParserRuleContext {
  public:
    Keyword31Context(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Keyword31();
    std::vector<antlr4::tree::TerminalNode *> IntegerConstant();
    antlr4::tree::TerminalNode* IntegerConstant(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Keyword31Context* keyword31();

  class  Keyword2DContext : public antlr4::ParserRuleContext {
  public:
    Keyword2DContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Keyword2D();
    std::vector<antlr4::tree::TerminalNode *> IntegerConstant();
    antlr4::tree::TerminalNode* IntegerConstant(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Keyword2DContext* keyword2D();

  class  Keyword2FContext : public antlr4::ParserRuleContext {
  public:
    Keyword2FContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Keyword2F();
    antlr4::tree::TerminalNode *IntegerConstant();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Keyword2FContext* keyword2F();

  class  Keyword30Context : public antlr4::ParserRuleContext {
  public:
    Keyword30Context(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Keyword30();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Keyword30Context* keyword30();

  class  Keyword32Context : public antlr4::ParserRuleContext {
  public:
    Keyword32Context(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Keyword32();
    antlr4::tree::TerminalNode *IntegerConstant();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Keyword32Context* keyword32();

  class  Keyword27Context : public antlr4::ParserRuleContext {
  public:
    Keyword27Context(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Keyword27();
    antlr4::tree::TerminalNode *IntegerConstant();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Keyword27Context* keyword27();

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

}  // namespace gdb
