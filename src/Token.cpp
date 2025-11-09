#include "../h/Token.h"

namespace Novo {
Token::Token(std::string value, TokenType type)
    : value(std::move(value)), type(type) {}

Token Token::newToken(std::string value, TokenType type) {
  return {std::move(value), type};
}

std::string Token::tokenTypeToString(TokenType type) {
  switch (type) {
  case TokenType::Identifier:
    return "Identifier";
  case TokenType::Integer:
    return "Integer";
  case TokenType::String:
    return "String";
  case TokenType::Function:
    return "Function";
  case TokenType::If:
    return "If";
  case TokenType::Else:
    return "Else";
  case TokenType::Return:
    return "Return";
  case TokenType::i32_type:
    return "i32_type";
  case TokenType::i64_type:
    return "i64_type";
  case TokenType::str_type:
    return "str_type";
  case TokenType::Minus:
    return "Minus";
  case TokenType::Plus:
    return "Plus";
  case TokenType::Divide:
    return "Divide";
  case TokenType::Multiply:
    return "Multiply";
  case TokenType::Modulo:
    return "Modulo";
  case TokenType::LBrace:
    return "LBrace";
  case TokenType::RBrace:
    return "RBrace";
  case TokenType::LBracket:
    return "LBracket";
  case TokenType::RBracket:
    return "RBracket";
  case TokenType::LParen:
    return "LParen";
  case TokenType::RParen:
    return "RParen";
  case TokenType::SemiColon:
    return "Semicolon";
  case TokenType::Colon:
    return "Colon";
  case TokenType::Comma:
    return "Comma";
  case TokenType::Ampersand:
    return "Ampersand";
  case TokenType::Bar:
    return "Bar";
  case TokenType::Define:
    return "Define";
  case TokenType::Equals:
    return "Equals";
  case TokenType::Arrow:
    return "Arrow";
  case TokenType::LessThan:
    return "LessThan";
  case TokenType::LessThanOrEqual:
    return "LessThanOrEqual";
  case TokenType::GreaterThan:
    return "GreaterThan";
  case TokenType::GreaterThanOrEqual:
    return "GreaterThanOrEqual";
  case TokenType::IsEqualTo:
    return "IsEqualTo";
  case TokenType::IsNotEqualTo:
    return "IsNotEqualTo";
  case TokenType::Bang:
    return "Bang";
  case TokenType::EndOfFile:
    return "EoF";
  default:
    return "Unknown";
  }
}

std::string Token::toString(const Token &t) {
  return "Token(" + tokenTypeToString(t.type) + ", " + t.value + ")";
}
} // namespace Novo