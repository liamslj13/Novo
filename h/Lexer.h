#pragma once
#include "./Token.h"
#include <iostream>
#include <vector>

namespace Novo {
struct Lexer {
  char curChar;
  int pos = 0;
  int readPos = 0;
  int curLine = 1;

  std::string input;
  std::vector<Token> tokens;

  static TokenType identifierToTokenType(const std::string &s);

  void advancePosition();
  char peekChar() const;

  std::string readString();
  std::string readIdentifier();
  std::string readInteger();

  std::vector<Token> tokenizeInput();
};
} // namespace Novo
