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

  // type keywords
  i32_type,
  i64_type,
  str_type,

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
  std::string value;
  TokenType type;

  Token(std::string value, TokenType type);

  static Token newToken(std::string value, TokenType type);
  static std::string tokenTypeToString(TokenType type);
  static std::string toString(const Token &t);
};
} // namespace Novo
