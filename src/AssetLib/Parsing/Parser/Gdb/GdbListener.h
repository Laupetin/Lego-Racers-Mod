
// Generated from ..\..\..\src\AssetLib\Parsing\Parser\Gdb\Gdb.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "GdbParser.h"


namespace gdb {

/**
 * This interface defines an abstract listener for a parse tree produced by GdbParser.
 */
class  GdbListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterRoot(GdbParser::RootContext *ctx) = 0;
  virtual void exitRoot(GdbParser::RootContext *ctx) = 0;

  virtual void enterSections(GdbParser::SectionsContext *ctx) = 0;
  virtual void exitSections(GdbParser::SectionsContext *ctx) = 0;

  virtual void enterMaterialSection(GdbParser::MaterialSectionContext *ctx) = 0;
  virtual void exitMaterialSection(GdbParser::MaterialSectionContext *ctx) = 0;

  virtual void enterMaterialNameList(GdbParser::MaterialNameListContext *ctx) = 0;
  virtual void exitMaterialNameList(GdbParser::MaterialNameListContext *ctx) = 0;

  virtual void enterMaterialName(GdbParser::MaterialNameContext *ctx) = 0;
  virtual void exitMaterialName(GdbParser::MaterialNameContext *ctx) = 0;

  virtual void enterScaleSection(GdbParser::ScaleSectionContext *ctx) = 0;
  virtual void exitScaleSection(GdbParser::ScaleSectionContext *ctx) = 0;

  virtual void enterVertexSection(GdbParser::VertexSectionContext *ctx) = 0;
  virtual void exitVertexSection(GdbParser::VertexSectionContext *ctx) = 0;

  virtual void enterVertexList(GdbParser::VertexListContext *ctx) = 0;
  virtual void exitVertexList(GdbParser::VertexListContext *ctx) = 0;

  virtual void enterVertexDefPosition(GdbParser::VertexDefPositionContext *ctx) = 0;
  virtual void exitVertexDefPosition(GdbParser::VertexDefPositionContext *ctx) = 0;

  virtual void enterVertexDefPositionUv(GdbParser::VertexDefPositionUvContext *ctx) = 0;
  virtual void exitVertexDefPositionUv(GdbParser::VertexDefPositionUvContext *ctx) = 0;

  virtual void enterVertexDefPositionUvColor(GdbParser::VertexDefPositionUvColorContext *ctx) = 0;
  virtual void exitVertexDefPositionUvColor(GdbParser::VertexDefPositionUvColorContext *ctx) = 0;

  virtual void enterVertexDefPositionUvNormal(GdbParser::VertexDefPositionUvNormalContext *ctx) = 0;
  virtual void exitVertexDefPositionUvNormal(GdbParser::VertexDefPositionUvNormalContext *ctx) = 0;

  virtual void enterVertexPosition(GdbParser::VertexPositionContext *ctx) = 0;
  virtual void exitVertexPosition(GdbParser::VertexPositionContext *ctx) = 0;

  virtual void enterVertexUv(GdbParser::VertexUvContext *ctx) = 0;
  virtual void exitVertexUv(GdbParser::VertexUvContext *ctx) = 0;

  virtual void enterVertexColor(GdbParser::VertexColorContext *ctx) = 0;
  virtual void exitVertexColor(GdbParser::VertexColorContext *ctx) = 0;

  virtual void enterVertexNormal(GdbParser::VertexNormalContext *ctx) = 0;
  virtual void exitVertexNormal(GdbParser::VertexNormalContext *ctx) = 0;

  virtual void enterFaceSection(GdbParser::FaceSectionContext *ctx) = 0;
  virtual void exitFaceSection(GdbParser::FaceSectionContext *ctx) = 0;

  virtual void enterFaceList(GdbParser::FaceListContext *ctx) = 0;
  virtual void exitFaceList(GdbParser::FaceListContext *ctx) = 0;

  virtual void enterFace(GdbParser::FaceContext *ctx) = 0;
  virtual void exitFace(GdbParser::FaceContext *ctx) = 0;

  virtual void enterMetaSection(GdbParser::MetaSectionContext *ctx) = 0;
  virtual void exitMetaSection(GdbParser::MetaSectionContext *ctx) = 0;

  virtual void enterMetaList(GdbParser::MetaListContext *ctx) = 0;
  virtual void exitMetaList(GdbParser::MetaListContext *ctx) = 0;

  virtual void enterMeta(GdbParser::MetaContext *ctx) = 0;
  virtual void exitMeta(GdbParser::MetaContext *ctx) = 0;

  virtual void enterMetaVertices(GdbParser::MetaVerticesContext *ctx) = 0;
  virtual void exitMetaVertices(GdbParser::MetaVerticesContext *ctx) = 0;

  virtual void enterMetaFaces(GdbParser::MetaFacesContext *ctx) = 0;
  virtual void exitMetaFaces(GdbParser::MetaFacesContext *ctx) = 0;

  virtual void enterKeyword2F(GdbParser::Keyword2FContext *ctx) = 0;
  virtual void exitKeyword2F(GdbParser::Keyword2FContext *ctx) = 0;

  virtual void enterKeyword30(GdbParser::Keyword30Context *ctx) = 0;
  virtual void exitKeyword30(GdbParser::Keyword30Context *ctx) = 0;

  virtual void enterMetaBone(GdbParser::MetaBoneContext *ctx) = 0;
  virtual void exitMetaBone(GdbParser::MetaBoneContext *ctx) = 0;

  virtual void enterMetaObject(GdbParser::MetaObjectContext *ctx) = 0;
  virtual void exitMetaObject(GdbParser::MetaObjectContext *ctx) = 0;

  virtual void enterFloatOrIntConstant(GdbParser::FloatOrIntConstantContext *ctx) = 0;
  virtual void exitFloatOrIntConstant(GdbParser::FloatOrIntConstantContext *ctx) = 0;


};

}  // namespace gdb
