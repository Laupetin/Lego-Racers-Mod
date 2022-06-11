
// Generated from ..\..\..\src\JamFileTool\Parsing\Parser\Tdb\Tdb.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "TdbListener.h"


namespace tdb {

/**
 * This class provides an empty implementation of TdbListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  TdbBaseListener : public TdbListener {
public:

  virtual void enterRoot(TdbParser::RootContext * /*ctx*/) override { }
  virtual void exitRoot(TdbParser::RootContext * /*ctx*/) override { }

  virtual void enterTextures(TdbParser::TexturesContext * /*ctx*/) override { }
  virtual void exitTextures(TdbParser::TexturesContext * /*ctx*/) override { }

  virtual void enterTexture(TdbParser::TextureContext * /*ctx*/) override { }
  virtual void exitTexture(TdbParser::TextureContext * /*ctx*/) override { }

  virtual void enterTextureName(TdbParser::TextureNameContext * /*ctx*/) override { }
  virtual void exitTextureName(TdbParser::TextureNameContext * /*ctx*/) override { }

  virtual void enterTextureProperty(TdbParser::TexturePropertyContext * /*ctx*/) override { }
  virtual void exitTextureProperty(TdbParser::TexturePropertyContext * /*ctx*/) override { }

  virtual void enterColorTextureProperty(TdbParser::ColorTexturePropertyContext * /*ctx*/) override { }
  virtual void exitColorTextureProperty(TdbParser::ColorTexturePropertyContext * /*ctx*/) override { }

  virtual void enterColorTexturePropertyKeyword(TdbParser::ColorTexturePropertyKeywordContext * /*ctx*/) override { }
  virtual void exitColorTexturePropertyKeyword(TdbParser::ColorTexturePropertyKeywordContext * /*ctx*/) override { }

  virtual void enterIntTextureProperty(TdbParser::IntTexturePropertyContext * /*ctx*/) override { }
  virtual void exitIntTextureProperty(TdbParser::IntTexturePropertyContext * /*ctx*/) override { }

  virtual void enterIntTexturePropertyKeyword(TdbParser::IntTexturePropertyKeywordContext * /*ctx*/) override { }
  virtual void exitIntTexturePropertyKeyword(TdbParser::IntTexturePropertyKeywordContext * /*ctx*/) override { }

  virtual void enterSingleValueKeywords(TdbParser::SingleValueKeywordsContext * /*ctx*/) override { }
  virtual void exitSingleValueKeywords(TdbParser::SingleValueKeywordsContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

}  // namespace tdb
