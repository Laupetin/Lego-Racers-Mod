
// Generated from ..\..\..\src\AssetLib\Parsing\Parser\Idb\Idb.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"


namespace idb {


class  IdbLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, Images = 3, Image = 4, FlipVertical = 5, Bmp = 6, 
    Tga = 7, ChromaKey = 8, Tint = 9, IntegerConstant = 10, FloatingConstant = 11, 
    DigitSequence = 12, StringLiteral = 13, Whitespace = 14, Newline = 15, 
    BlockComment = 16, LineComment = 17
  };

  explicit IdbLexer(antlr4::CharStream *input);

  ~IdbLexer() override;


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

}  // namespace idb
