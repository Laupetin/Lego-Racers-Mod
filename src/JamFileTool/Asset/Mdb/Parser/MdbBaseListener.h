
// Generated from ..\..\..\src\JamFileTool\Asset\Mdb\Mdb.g4 by ANTLR 4.10.1

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

  virtual void enterR(MdbParser::RContext * /*ctx*/) override { }
  virtual void exitR(MdbParser::RContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

}  // namespace mdb
