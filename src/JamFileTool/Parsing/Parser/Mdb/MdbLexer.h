
// Generated from ..\..\..\src\JamFileTool\Parsing\Parser\Mdb\Mdb.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"


namespace mdb {


class  MdbLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, Materials = 3, Material = 4, Color1 = 5, Color0 = 6, 
    Keyword2A = 7, Keyword2B = 8, Texture = 9, Keyword2D = 10, Keyword2E = 11, 
    Keyword2F = 12, Keyword30 = 13, Keyword31 = 14, Keyword32 = 15, Keyword33 = 16, 
    Keyword34 = 17, Keyword35 = 18, Keyword36 = 19, Keyword37 = 20, Keyword38 = 21, 
    Keyword39 = 22, Keyword3A = 23, Keyword3B = 24, Keyword3C = 25, Keyword3D = 26, 
    Keyword3E = 27, Keyword3F = 28, Keyword40 = 29, Keyword41 = 30, Keyword42 = 31, 
    Keyword43 = 32, Keyword44 = 33, Keyword45 = 34, Opacity = 35, Keyword47 = 36, 
    Keyword48 = 37, Keyword49 = 38, Keyword4A = 39, Keyword4B = 40, Keyword4C = 41, 
    Keyword4D = 42, Keyword4E = 43, Keyword4F = 44, Keyword50 = 45, IntegerConstant = 46, 
    FloatingConstant = 47, DigitSequence = 48, StringLiteral = 49, Whitespace = 50, 
    Newline = 51, BlockComment = 52, LineComment = 53
  };

  explicit MdbLexer(antlr4::CharStream *input);

  ~MdbLexer() override;


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

}  // namespace mdb
