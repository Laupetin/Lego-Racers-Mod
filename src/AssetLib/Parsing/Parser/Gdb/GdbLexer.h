
// Generated from ..\..\..\src\AssetLib\Parsing\Parser\Gdb\Gdb.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"


namespace gdb {


class  GdbLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, Materials = 3, Scale = 4, Vertices = 5, Faces = 6, 
    Meta = 7, Vertex = 8, Uv = 9, Color = 10, Normal = 11, Texture = 12, 
    Face = 13, Keyword27 = 14, Keyword2D = 15, Keyword2F = 16, Keyword30 = 17, 
    Keyword31 = 18, Keyword32 = 19, IntegerConstant = 20, FloatingConstant = 21, 
    DigitSequence = 22, StringLiteral = 23, Whitespace = 24, Newline = 25, 
    BlockComment = 26, LineComment = 27
  };

  explicit GdbLexer(antlr4::CharStream *input);

  ~GdbLexer() override;


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

}  // namespace gdb
