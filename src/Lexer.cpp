#include "Token.cpp"
#include <iostream>
#include <unordered_map>
#include <vector>

struct Lexer {

  char curChar;
  int pos = 0;
  int readPos = 0;
  int curLine = 1;

  std::string input;
  std::vector<Token> tokens;

  static TokenType identifierToTokenType(const std::string &s) {
    if (s == "func")
      return TokenType::Function;
    if (s == "ret")
      return TokenType::Return;
    if (s == "i32")
      return TokenType::i32_type;
    if (s == "i64")
      return TokenType::i64_type;
    if (s == "str")
      return TokenType::str_type;
    if (s == "if")
      return TokenType::If;
    if (s == "else")
      return TokenType::Else;
    return TokenType::Identifier;
  }

  void advancePosition() {
    pos = readPos;
    if (readPos <= input.size())
      readPos++;
  }

  char peekChar() const {
    if (readPos >= input.size())
      return '\0';
    return input[readPos];
  }

  std::string readString() {
    std::string res;

    advancePosition(); // consume " token
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

  std::string readIdentifier() {
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

  std::string readInteger() {
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

  std::vector<Token> tokenizeInput() {
    // init current pos to 0, readPos to 1
    advancePosition();

    std::string res; // for functions that require string building
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
          advancePosition(); // consume : token and =
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
          tokens.push_back(
              Token::newToken(">=", TokenType::GreaterThanOrEqual));
          break;
        }
        tokens.push_back(Token::newToken(">", TokenType::GreaterThan));
        advancePosition();
        break;
      default: {
        if (isalpha(curChar)) {
          res = readIdentifier();
          TokenType tt = identifierToTokenType(res);
          tokens.push_back(Token::newToken(res, tt));
          break;
        }
        if (isdigit(curChar)) {
          res = "";
          res = readInteger();
          tokens.push_back(Token::newToken(res, TokenType::Integer));
          break;
        }
        std::cerr << "Erroneous character " << curChar
                  << "\n found on line=" << curLine;
        advancePosition();
      }
      }
    }
    // signifies eof reached
    tokens.push_back(Token::newToken("", TokenType::EndOfFile));

    return tokens;
  }
};
