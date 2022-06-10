
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

  virtual void enterR(MdbParser::RContext *ctx) = 0;
  virtual void exitR(MdbParser::RContext *ctx) = 0;


};

}  // namespace mdb
