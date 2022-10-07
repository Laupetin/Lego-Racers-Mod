
// Generated from ..\..\..\src\AssetLib\Parsing\Parser\Mdb\Mdb.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "MdbListener.h"


namespace mdb {

/**
 * This class provides an empty implementation of MdbListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  MdbBaseListener : public MdbListener {
public:

  virtual void enterRoot(MdbParser::RootContext * /*ctx*/) override { }
  virtual void exitRoot(MdbParser::RootContext * /*ctx*/) override { }

  virtual void enterMaterials(MdbParser::MaterialsContext * /*ctx*/) override { }
  virtual void exitMaterials(MdbParser::MaterialsContext * /*ctx*/) override { }

  virtual void enterMaterial(MdbParser::MaterialContext * /*ctx*/) override { }
  virtual void exitMaterial(MdbParser::MaterialContext * /*ctx*/) override { }

  virtual void enterMaterialName(MdbParser::MaterialNameContext * /*ctx*/) override { }
  virtual void exitMaterialName(MdbParser::MaterialNameContext * /*ctx*/) override { }

  virtual void enterMaterialProperty(MdbParser::MaterialPropertyContext * /*ctx*/) override { }
  virtual void exitMaterialProperty(MdbParser::MaterialPropertyContext * /*ctx*/) override { }

  virtual void enterColorMaterialProperty(MdbParser::ColorMaterialPropertyContext * /*ctx*/) override { }
  virtual void exitColorMaterialProperty(MdbParser::ColorMaterialPropertyContext * /*ctx*/) override { }

  virtual void enterColorMaterialPropertyKeyword(MdbParser::ColorMaterialPropertyKeywordContext * /*ctx*/) override { }
  virtual void exitColorMaterialPropertyKeyword(MdbParser::ColorMaterialPropertyKeywordContext * /*ctx*/) override { }

  virtual void enterTextMaterialProperty(MdbParser::TextMaterialPropertyContext * /*ctx*/) override { }
  virtual void exitTextMaterialProperty(MdbParser::TextMaterialPropertyContext * /*ctx*/) override { }

  virtual void enterTextMaterialPropertyKeyword(MdbParser::TextMaterialPropertyKeywordContext * /*ctx*/) override { }
  virtual void exitTextMaterialPropertyKeyword(MdbParser::TextMaterialPropertyKeywordContext * /*ctx*/) override { }

  virtual void enterUint8MaterialProperty(MdbParser::Uint8MaterialPropertyContext * /*ctx*/) override { }
  virtual void exitUint8MaterialProperty(MdbParser::Uint8MaterialPropertyContext * /*ctx*/) override { }

  virtual void enterUint8MaterialPropertyKeyword(MdbParser::Uint8MaterialPropertyKeywordContext * /*ctx*/) override { }
  virtual void exitUint8MaterialPropertyKeyword(MdbParser::Uint8MaterialPropertyKeywordContext * /*ctx*/) override { }

  virtual void enterIntMaterialProperty(MdbParser::IntMaterialPropertyContext * /*ctx*/) override { }
  virtual void exitIntMaterialProperty(MdbParser::IntMaterialPropertyContext * /*ctx*/) override { }

  virtual void enterIntMaterialPropertyKeyword(MdbParser::IntMaterialPropertyKeywordContext * /*ctx*/) override { }
  virtual void exitIntMaterialPropertyKeyword(MdbParser::IntMaterialPropertyKeywordContext * /*ctx*/) override { }

  virtual void enterSingleValueKeywords(MdbParser::SingleValueKeywordsContext * /*ctx*/) override { }
  virtual void exitSingleValueKeywords(MdbParser::SingleValueKeywordsContext * /*ctx*/) override { }

  virtual void enterKeyword2F(MdbParser::Keyword2FContext * /*ctx*/) override { }
  virtual void exitKeyword2F(MdbParser::Keyword2FContext * /*ctx*/) override { }

  virtual void enterKeyword2FSubtoken(MdbParser::Keyword2FSubtokenContext * /*ctx*/) override { }
  virtual void exitKeyword2FSubtoken(MdbParser::Keyword2FSubtokenContext * /*ctx*/) override { }

  virtual void enterKeyword38(MdbParser::Keyword38Context * /*ctx*/) override { }
  virtual void exitKeyword38(MdbParser::Keyword38Context * /*ctx*/) override { }

  virtual void enterKeyword38Subtoken(MdbParser::Keyword38SubtokenContext * /*ctx*/) override { }
  virtual void exitKeyword38Subtoken(MdbParser::Keyword38SubtokenContext * /*ctx*/) override { }

  virtual void enterFloatOrIntConstant(MdbParser::FloatOrIntConstantContext * /*ctx*/) override { }
  virtual void exitFloatOrIntConstant(MdbParser::FloatOrIntConstantContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

}  // namespace mdb
