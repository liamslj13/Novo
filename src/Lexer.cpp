#include "../h/Lexer.h"

namespace Novo {

TokenType Lexer::identifierToTokenType(const std::string &s) {
  if (s == "func")
    return TokenType::Function;
  if (s == "ret")
    return TokenType::Return;
  if (s == "if")
    return TokenType::If;
  if (s == "else")
    return TokenType::Else;
  return TokenType::Identifier;
}

void Lexer::advancePosition() {
  pos = readPos;
  if (readPos <= input.size())
    readPos++;
}

char Lexer::peekChar() const {
  if (readPos >= input.size())
    return '\0';
  return input[readPos];
}

std::string Lexer::readString() {
  std::string res;
  advancePosition(); // consume opening quote
  curChar = input[pos];
  while (curChar != '"') {
    res += curChar;
    advancePosition();
    curChar = input[pos];
  }
  advancePosition();
  curChar = input[pos];
  return res;
}

std::string Lexer::readIdentifier() {
  std::string res;
  res += curChar;
  advancePosition();
  curChar = input[pos];
  while (isalnum(curChar) || curChar == '_') {
    res += curChar;
    advancePosition();
    curChar = input[pos];
  }
  return res;
}

std::string Lexer::readInteger() {
  std::string res;
  res += curChar;
  advancePosition();
  curChar = input[pos];
  while (isdigit(curChar)) {
    res += curChar;
    advancePosition();
    curChar = input[pos];
  }
  return res;
}

std::vector<Token> Lexer::tokenizeInput() {
  advancePosition();
  std::string res;
  std::vector<Token> tokens;

  while (pos < input.size()) {
    curChar = input[pos];

    if (isspace(curChar)) {
      if (curChar == '\n')
        curLine++;
      advancePosition();
      curChar = input[pos];
      continue;
    }

    switch (curChar) {
    case '{':
      tokens.push_back(Token::newToken("{", TokenType::LBrace));
      advancePosition();
      break;
    case '}':
      tokens.push_back(Token::newToken("}", TokenType::RBrace));
      advancePosition();
      break;
    case '(':
      tokens.push_back(Token::newToken("(", TokenType::LParen));
      advancePosition();
      break;
    case ')':
      tokens.push_back(Token::newToken(")", TokenType::RParen));
      advancePosition();
      break;
    case '[':
      tokens.push_back(Token::newToken("[", TokenType::LBracket));
      advancePosition();
      break;
    case ']':
      tokens.push_back(Token::newToken("]", TokenType::RBracket));
      advancePosition();
      break;
    case ':':
      if (peekChar() == '=') {
        advancePosition();
        advancePosition();
        tokens.push_back(Token::newToken(":=", TokenType::Define));
        break;
      }
      tokens.push_back(Token::newToken(":", TokenType::Colon));
      advancePosition();
      break;
    case ';':
      tokens.push_back(Token::newToken(";", TokenType::SemiColon));
      advancePosition();
      break;
    case '&':
      tokens.push_back(Token::newToken("&", TokenType::Ampersand));
      advancePosition();
      break;
    case ',':
      tokens.push_back(Token::newToken(",", TokenType::Comma));
      advancePosition();
      break;
    case '|':
      tokens.push_back(Token::newToken("|", TokenType::Bar));
      advancePosition();
      break;
    case '=':
      if (peekChar() == '=') {
        advancePosition();
        advancePosition();
        tokens.push_back(Token::newToken("==", TokenType::IsEqualTo));
        break;
      }
      tokens.push_back(Token::newToken("=", TokenType::Equals));
      advancePosition();
      break;
    case '-':
      if (peekChar() == '>') {
        advancePosition();
        advancePosition();
        tokens.push_back(Token::newToken("->", TokenType::Arrow));
        break;
      }
      tokens.push_back(Token::newToken("-", TokenType::Minus));
      advancePosition();
      break;
    case '+':
      tokens.push_back(Token::newToken("+", TokenType::Plus));
      advancePosition();
      break;
    case '*':
      tokens.push_back(Token::newToken("*", TokenType::Multiply));
      advancePosition();
      break;
    case '/':
      tokens.push_back(Token::newToken("/", TokenType::Divide));
      advancePosition();
      break;
    case '%':
      tokens.push_back(Token::newToken("%", TokenType::Modulo));
      advancePosition();
      break;
    case '"':
      res = readString();
      tokens.push_back(Token::newToken(res, TokenType::String));
      break;
    case '!':
      if (peekChar() == '=') {
        advancePosition();
        advancePosition();
        tokens.push_back(Token::newToken("!=", TokenType::IsNotEqualTo));
        break;
      }
      tokens.push_back(Token::newToken("!", TokenType::Bang));
      advancePosition();
      break;
    case '<':
      if (peekChar() == '=') {
        advancePosition();
        advancePosition();
        tokens.push_back(Token::newToken("<=", TokenType::LessThanOrEqual));
        break;
      }
      tokens.push_back(Token::newToken("<", TokenType::LessThan));
      advancePosition();
      break;
    case '>':
      if (peekChar() == '=') {
        advancePosition();
        advancePosition();
        tokens.push_back(Token::newToken(">=", TokenType::GreaterThanOrEqual));
        break;
      }
      tokens.push_back(Token::newToken(">", TokenType::GreaterThan));
      advancePosition();
      break;
    default:
      if (isalpha(curChar)) {
        res = readIdentifier();
        TokenType tt = identifierToTokenType(res);
        tokens.push_back(Token::newToken(res, tt));
        break;
      }
      if (isdigit(curChar)) {
        res = readInteger();
        tokens.push_back(Token::newToken(res, TokenType::Integer));
        break;
      }
      std::cerr << "Erroneous character " << curChar << " on line " << curLine
                << "\n";
      advancePosition();
      break;
    }
  }

  tokens.push_back(Token::newToken("", TokenType::EndOfFile));
  return tokens;
}

} // namespace Novo
