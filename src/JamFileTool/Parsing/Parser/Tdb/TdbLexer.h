
// Generated from ..\..\..\src\JamFileTool\Parsing\Parser\Tdb\Tdb.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"


namespace tdb {


class  TdbLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, Textures = 3, Texture = 4, FlipVertically = 5, Keyword29 = 6, 
    Bmp = 7, Tga = 8, ChromaKey = 9, Keyword2D = 10, Keyword2E = 11, IntegerConstant = 12, 
    StringLiteral = 13, Whitespace = 14, Newline = 15, BlockComment = 16, 
    LineComment = 17
  };

  explicit TdbLexer(antlr4::CharStream *input);

  ~TdbLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

}  // namespace tdb
