
// Generated from ..\..\..\src\JamFileTool\Asset\Mdb\Mdb.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "MdbParser.h"


namespace mdb {

/**
 * This interface defines an abstract listener for a parse tree produced by MdbParser.
 */
class  MdbListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterRoot(MdbParser::RootContext *ctx) = 0;
  virtual void exitRoot(MdbParser::RootContext *ctx) = 0;

  virtual void enterMaterials(MdbParser::MaterialsContext *ctx) = 0;
  virtual void exitMaterials(MdbParser::MaterialsContext *ctx) = 0;

  virtual void enterMaterial(MdbParser::MaterialContext *ctx) = 0;
  virtual void exitMaterial(MdbParser::MaterialContext *ctx) = 0;

  virtual void enterMaterial_property(MdbParser::Material_propertyContext *ctx) = 0;
  virtual void exitMaterial_property(MdbParser::Material_propertyContext *ctx) = 0;

  virtual void enterColorMaterialProperty(MdbParser::ColorMaterialPropertyContext *ctx) = 0;
  virtual void exitColorMaterialProperty(MdbParser::ColorMaterialPropertyContext *ctx) = 0;

  virtual void enterColorMaterialPropertyKeyword(MdbParser::ColorMaterialPropertyKeywordContext *ctx) = 0;
  virtual void exitColorMaterialPropertyKeyword(MdbParser::ColorMaterialPropertyKeywordContext *ctx) = 0;

  virtual void enterTextMaterialProperty(MdbParser::TextMaterialPropertyContext *ctx) = 0;
  virtual void exitTextMaterialProperty(MdbParser::TextMaterialPropertyContext *ctx) = 0;

  virtual void enterTextMaterialPropertyKeyword(MdbParser::TextMaterialPropertyKeywordContext *ctx) = 0;
  virtual void exitTextMaterialPropertyKeyword(MdbParser::TextMaterialPropertyKeywordContext *ctx) = 0;

  virtual void enterUint8MaterialProperty(MdbParser::Uint8MaterialPropertyContext *ctx) = 0;
  virtual void exitUint8MaterialProperty(MdbParser::Uint8MaterialPropertyContext *ctx) = 0;

  virtual void enterUint8MaterialPropertyKeyword(MdbParser::Uint8MaterialPropertyKeywordContext *ctx) = 0;
  virtual void exitUint8MaterialPropertyKeyword(MdbParser::Uint8MaterialPropertyKeywordContext *ctx) = 0;

  virtual void enterIntMaterialProperty(MdbParser::IntMaterialPropertyContext *ctx) = 0;
  virtual void exitIntMaterialProperty(MdbParser::IntMaterialPropertyContext *ctx) = 0;

  virtual void enterIntMaterialPropertyKeyword(MdbParser::IntMaterialPropertyKeywordContext *ctx) = 0;
  virtual void exitIntMaterialPropertyKeyword(MdbParser::IntMaterialPropertyKeywordContext *ctx) = 0;

  virtual void enterSingleValueKeywords(MdbParser::SingleValueKeywordsContext *ctx) = 0;
  virtual void exitSingleValueKeywords(MdbParser::SingleValueKeywordsContext *ctx) = 0;

  virtual void enterKeyword2F(MdbParser::Keyword2FContext *ctx) = 0;
  virtual void exitKeyword2F(MdbParser::Keyword2FContext *ctx) = 0;

  virtual void enterKeyword2FSubtoken(MdbParser::Keyword2FSubtokenContext *ctx) = 0;
  virtual void exitKeyword2FSubtoken(MdbParser::Keyword2FSubtokenContext *ctx) = 0;

  virtual void enterKeyword38(MdbParser::Keyword38Context *ctx) = 0;
  virtual void exitKeyword38(MdbParser::Keyword38Context *ctx) = 0;

  virtual void enterKeyword38Subtoken(MdbParser::Keyword38SubtokenContext *ctx) = 0;
  virtual void exitKeyword38Subtoken(MdbParser::Keyword38SubtokenContext *ctx) = 0;


};

}  // namespace mdb
