
// Generated from ..\..\..\src\AssetLib\Parsing\Parser\Gdb\Gdb.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "GdbListener.h"


namespace gdb {

/**
 * This class provides an empty implementation of GdbListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  GdbBaseListener : public GdbListener {
public:

  virtual void enterRoot(GdbParser::RootContext * /*ctx*/) override { }
  virtual void exitRoot(GdbParser::RootContext * /*ctx*/) override { }

  virtual void enterSections(GdbParser::SectionsContext * /*ctx*/) override { }
  virtual void exitSections(GdbParser::SectionsContext * /*ctx*/) override { }

  virtual void enterMaterialSection(GdbParser::MaterialSectionContext * /*ctx*/) override { }
  virtual void exitMaterialSection(GdbParser::MaterialSectionContext * /*ctx*/) override { }

  virtual void enterMaterialNameList(GdbParser::MaterialNameListContext * /*ctx*/) override { }
  virtual void exitMaterialNameList(GdbParser::MaterialNameListContext * /*ctx*/) override { }

  virtual void enterMaterialName(GdbParser::MaterialNameContext * /*ctx*/) override { }
  virtual void exitMaterialName(GdbParser::MaterialNameContext * /*ctx*/) override { }

  virtual void enterScaleSection(GdbParser::ScaleSectionContext * /*ctx*/) override { }
  virtual void exitScaleSection(GdbParser::ScaleSectionContext * /*ctx*/) override { }

  virtual void enterVertexSection(GdbParser::VertexSectionContext * /*ctx*/) override { }
  virtual void exitVertexSection(GdbParser::VertexSectionContext * /*ctx*/) override { }

  virtual void enterVertexList(GdbParser::VertexListContext * /*ctx*/) override { }
  virtual void exitVertexList(GdbParser::VertexListContext * /*ctx*/) override { }

  virtual void enterVertexDefPosition(GdbParser::VertexDefPositionContext * /*ctx*/) override { }
  virtual void exitVertexDefPosition(GdbParser::VertexDefPositionContext * /*ctx*/) override { }

  virtual void enterVertexDefPositionUv(GdbParser::VertexDefPositionUvContext * /*ctx*/) override { }
  virtual void exitVertexDefPositionUv(GdbParser::VertexDefPositionUvContext * /*ctx*/) override { }

  virtual void enterVertexDefPositionUvColor(GdbParser::VertexDefPositionUvColorContext * /*ctx*/) override { }
  virtual void exitVertexDefPositionUvColor(GdbParser::VertexDefPositionUvColorContext * /*ctx*/) override { }

  virtual void enterVertexDefPositionUvNormal(GdbParser::VertexDefPositionUvNormalContext * /*ctx*/) override { }
  virtual void exitVertexDefPositionUvNormal(GdbParser::VertexDefPositionUvNormalContext * /*ctx*/) override { }

  virtual void enterVertexPosition(GdbParser::VertexPositionContext * /*ctx*/) override { }
  virtual void exitVertexPosition(GdbParser::VertexPositionContext * /*ctx*/) override { }

  virtual void enterVertexUv(GdbParser::VertexUvContext * /*ctx*/) override { }
  virtual void exitVertexUv(GdbParser::VertexUvContext * /*ctx*/) override { }

  virtual void enterVertexColor(GdbParser::VertexColorContext * /*ctx*/) override { }
  virtual void exitVertexColor(GdbParser::VertexColorContext * /*ctx*/) override { }

  virtual void enterVertexNormal(GdbParser::VertexNormalContext * /*ctx*/) override { }
  virtual void exitVertexNormal(GdbParser::VertexNormalContext * /*ctx*/) override { }

  virtual void enterFaceSection(GdbParser::FaceSectionContext * /*ctx*/) override { }
  virtual void exitFaceSection(GdbParser::FaceSectionContext * /*ctx*/) override { }

  virtual void enterFaceList(GdbParser::FaceListContext * /*ctx*/) override { }
  virtual void exitFaceList(GdbParser::FaceListContext * /*ctx*/) override { }

  virtual void enterFace(GdbParser::FaceContext * /*ctx*/) override { }
  virtual void exitFace(GdbParser::FaceContext * /*ctx*/) override { }

  virtual void enterMetaSection(GdbParser::MetaSectionContext * /*ctx*/) override { }
  virtual void exitMetaSection(GdbParser::MetaSectionContext * /*ctx*/) override { }

  virtual void enterMetaList(GdbParser::MetaListContext * /*ctx*/) override { }
  virtual void exitMetaList(GdbParser::MetaListContext * /*ctx*/) override { }

  virtual void enterMeta(GdbParser::MetaContext * /*ctx*/) override { }
  virtual void exitMeta(GdbParser::MetaContext * /*ctx*/) override { }

  virtual void enterMetaVertices(GdbParser::MetaVerticesContext * /*ctx*/) override { }
  virtual void exitMetaVertices(GdbParser::MetaVerticesContext * /*ctx*/) override { }

  virtual void enterMetaFaces(GdbParser::MetaFacesContext * /*ctx*/) override { }
  virtual void exitMetaFaces(GdbParser::MetaFacesContext * /*ctx*/) override { }

  virtual void enterKeyword2F(GdbParser::Keyword2FContext * /*ctx*/) override { }
  virtual void exitKeyword2F(GdbParser::Keyword2FContext * /*ctx*/) override { }

  virtual void enterKeyword30(GdbParser::Keyword30Context * /*ctx*/) override { }
  virtual void exitKeyword30(GdbParser::Keyword30Context * /*ctx*/) override { }

  virtual void enterKeyword32(GdbParser::Keyword32Context * /*ctx*/) override { }
  virtual void exitKeyword32(GdbParser::Keyword32Context * /*ctx*/) override { }

  virtual void enterMetaObject(GdbParser::MetaObjectContext * /*ctx*/) override { }
  virtual void exitMetaObject(GdbParser::MetaObjectContext * /*ctx*/) override { }

  virtual void enterFloatOrIntConstant(GdbParser::FloatOrIntConstantContext * /*ctx*/) override { }
  virtual void exitFloatOrIntConstant(GdbParser::FloatOrIntConstantContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

}  // namespace gdb
