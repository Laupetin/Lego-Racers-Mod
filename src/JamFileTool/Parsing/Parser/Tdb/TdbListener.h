
// Generated from ..\..\..\src\JamFileTool\Parsing\Parser\Tdb\Tdb.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "TdbParser.h"


namespace tdb {

/**
 * This interface defines an abstract listener for a parse tree produced by TdbParser.
 */
class  TdbListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterRoot(TdbParser::RootContext *ctx) = 0;
  virtual void exitRoot(TdbParser::RootContext *ctx) = 0;

  virtual void enterTextures(TdbParser::TexturesContext *ctx) = 0;
  virtual void exitTextures(TdbParser::TexturesContext *ctx) = 0;

  virtual void enterTexture(TdbParser::TextureContext *ctx) = 0;
  virtual void exitTexture(TdbParser::TextureContext *ctx) = 0;

  virtual void enterTextureName(TdbParser::TextureNameContext *ctx) = 0;
  virtual void exitTextureName(TdbParser::TextureNameContext *ctx) = 0;

  virtual void enterTextureProperty(TdbParser::TexturePropertyContext *ctx) = 0;
  virtual void exitTextureProperty(TdbParser::TexturePropertyContext *ctx) = 0;

  virtual void enterColorTextureProperty(TdbParser::ColorTexturePropertyContext *ctx) = 0;
  virtual void exitColorTextureProperty(TdbParser::ColorTexturePropertyContext *ctx) = 0;

  virtual void enterColorTexturePropertyKeyword(TdbParser::ColorTexturePropertyKeywordContext *ctx) = 0;
  virtual void exitColorTexturePropertyKeyword(TdbParser::ColorTexturePropertyKeywordContext *ctx) = 0;

  virtual void enterIntTextureProperty(TdbParser::IntTexturePropertyContext *ctx) = 0;
  virtual void exitIntTextureProperty(TdbParser::IntTexturePropertyContext *ctx) = 0;

  virtual void enterIntTexturePropertyKeyword(TdbParser::IntTexturePropertyKeywordContext *ctx) = 0;
  virtual void exitIntTexturePropertyKeyword(TdbParser::IntTexturePropertyKeywordContext *ctx) = 0;

  virtual void enterSingleValueKeywords(TdbParser::SingleValueKeywordsContext *ctx) = 0;
  virtual void exitSingleValueKeywords(TdbParser::SingleValueKeywordsContext *ctx) = 0;


};

}  // namespace tdb
