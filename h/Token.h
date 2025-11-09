#pragma once
#include <iostream>

namespace Novo {

enum class TokenType {
  Identifier,
  Integer,
  String,

  // keywords
  Function, // func
  If,       // if
  Else,     // else
  Return,   // ret

  // characters
  LBrace,
  RBrace,
  LParen,
  RParen,
  LBracket,
  RBracket,
  SemiColon,
  Colon,
  Comma,
  Ampersand,
  Bar,

  // operators
  Define, // :=
  Equals, // =
  Arrow,  // ->
  Plus,
  Minus,
  Divide,
  Multiply,
  Modulo,
  Bang,

  // comparators
  LessThan,
  LessThanOrEqual,
  GreaterThan,
  GreaterThanOrEqual,
  IsEqualTo,    // ==
  IsNotEqualTo, // !=

  EndOfFile,
};

struct Token {
  std::string literal;
  TokenType type;

  Token(std::string literal, TokenType type);

  static Token newToken(std::string literal, TokenType type);
  static std::string tokenTypeToString(TokenType type);
  static std::string toString(const Token &t);
};
} // namespace Novo
