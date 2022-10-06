
// Generated from ..\..\..\src\JamFileTool\Parsing\Parser\Idb\Idb.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "IdbParser.h"


namespace idb {

/**
 * This interface defines an abstract listener for a parse tree produced by IdbParser.
 */
class  IdbListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterRoot(IdbParser::RootContext *ctx) = 0;
  virtual void exitRoot(IdbParser::RootContext *ctx) = 0;

  virtual void enterImages(IdbParser::ImagesContext *ctx) = 0;
  virtual void exitImages(IdbParser::ImagesContext *ctx) = 0;

  virtual void enterImage(IdbParser::ImageContext *ctx) = 0;
  virtual void exitImage(IdbParser::ImageContext *ctx) = 0;

  virtual void enterImageName(IdbParser::ImageNameContext *ctx) = 0;
  virtual void exitImageName(IdbParser::ImageNameContext *ctx) = 0;

  virtual void enterImageProperty(IdbParser::ImagePropertyContext *ctx) = 0;
  virtual void exitImageProperty(IdbParser::ImagePropertyContext *ctx) = 0;

  virtual void enterColorImageProperty(IdbParser::ColorImagePropertyContext *ctx) = 0;
  virtual void exitColorImageProperty(IdbParser::ColorImagePropertyContext *ctx) = 0;

  virtual void enterColorImagePropertyKeyword(IdbParser::ColorImagePropertyKeywordContext *ctx) = 0;
  virtual void exitColorImagePropertyKeyword(IdbParser::ColorImagePropertyKeywordContext *ctx) = 0;

  virtual void enterSingleValueKeywords(IdbParser::SingleValueKeywordsContext *ctx) = 0;
  virtual void exitSingleValueKeywords(IdbParser::SingleValueKeywordsContext *ctx) = 0;

  virtual void enterFloatOrIntConstant(IdbParser::FloatOrIntConstantContext *ctx) = 0;
  virtual void exitFloatOrIntConstant(IdbParser::FloatOrIntConstantContext *ctx) = 0;


};

}  // namespace idb
