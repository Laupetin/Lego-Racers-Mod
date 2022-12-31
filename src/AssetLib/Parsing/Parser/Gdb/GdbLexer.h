
// Generated from ..\..\..\src\AssetLib\Parsing\Parser\Gdb\Gdb.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"


namespace gdb {


class  GdbLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, Materials = 3, Scale = 4, Vertices = 5, Faces = 6, 
    Meta = 7, Object = 8, Vertex = 9, Uv = 10, Color = 11, Normal = 12, 
    Texture = 13, Face = 14, Keyword2F = 15, Keyword30 = 16, Bone = 17, 
    IntegerConstant = 18, FloatingConstant = 19, DigitSequence = 20, StringLiteral = 21, 
    Whitespace = 22, Newline = 23, BlockComment = 24, LineComment = 25
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
