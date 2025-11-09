#include <gtest/gtest.h>
#include <string>
#include <vector>

#include "../h/Lexer.h"

using namespace Novo;

TEST(LexerTests, TokenizeProgram) {
  const std::string input = R"(
x y z "hello" 123 456

func myFunc() {
    if x < 10 {
        ret
    } else {
        ret
    }
}

a := 42;
b := 10000000000;
s := "world";

{
  [ ( ) ]
  { }
  ;
  :
  ,
  &
  |
}

a := b;
a = b + c - d * e / f % g;
a -> b;
!a;

a < b;
a <= b;
a > b;
a >= b;
a == b;
a != b;
)";

  Lexer l;
  l.input = input;
  auto tList = l.tokenizeInput();

  std::vector<std::pair<TokenType, std::string>> expected = {
      {TokenType::Identifier, "x"},
      {TokenType::Identifier, "y"},
      {TokenType::Identifier, "z"},
      {TokenType::String, "hello"},
      {TokenType::Integer, "123"},
      {TokenType::Integer, "456"},

      {TokenType::Function, "func"},
      {TokenType::Identifier, "myFunc"},
      {TokenType::LParen, "("},
      {TokenType::RParen, ")"},
      {TokenType::LBrace, "{"},

      {TokenType::If, "if"},
      {TokenType::Identifier, "x"},
      {TokenType::LessThan, "<"},
      {TokenType::Integer, "10"},
      {TokenType::LBrace, "{"},
      {TokenType::Return, "ret"},
      {TokenType::RBrace, "}"},
      {TokenType::Else, "else"},
      {TokenType::LBrace, "{"},
      {TokenType::Return, "ret"},
      {TokenType::RBrace, "}"},
      {TokenType::RBrace, "}"},

      {TokenType::Identifier, "a"},
      {TokenType::Define, ":="},
      {TokenType::Integer, "42"},
      {TokenType::SemiColon, ";"},

      {TokenType::Identifier, "b"},
      {TokenType::Define, ":="},
      {TokenType::Integer, "10000000000"},
      {TokenType::SemiColon, ";"},

      {TokenType::Identifier, "s"},
      {TokenType::Define, ":="},
      {TokenType::String, "world"},
      {TokenType::SemiColon, ";"},

      {TokenType::LBrace, "{"},
      {TokenType::LBracket, "["},
      {TokenType::LParen, "("},
      {TokenType::RParen, ")"},
      {TokenType::RBracket, "]"},
      {TokenType::LBrace, "{"},
      {TokenType::RBrace, "}"},
      {TokenType::SemiColon, ";"},
      {TokenType::Colon, ":"},
      {TokenType::Comma, ","},
      {TokenType::Ampersand, "&"},
      {TokenType::Bar, "|"},
      {TokenType::RBrace, "}"},

      {TokenType::Identifier, "a"},
      {TokenType::Define, ":="},
      {TokenType::Identifier, "b"},
      {TokenType::SemiColon, ";"},

      {TokenType::Identifier, "a"},
      {TokenType::Equals, "="},
      {TokenType::Identifier, "b"},
      {TokenType::Plus, "+"},
      {TokenType::Identifier, "c"},
      {TokenType::Minus, "-"},
      {TokenType::Identifier, "d"},
      {TokenType::Multiply, "*"},
      {TokenType::Identifier, "e"},
      {TokenType::Divide, "/"},
      {TokenType::Identifier, "f"},
      {TokenType::Modulo, "%"},
      {TokenType::Identifier, "g"},
      {TokenType::SemiColon, ";"},

      {TokenType::Identifier, "a"},
      {TokenType::Arrow, "->"},
      {TokenType::Identifier, "b"},
      {TokenType::SemiColon, ";"},

      {TokenType::Bang, "!"},
      {TokenType::Identifier, "a"},
      {TokenType::SemiColon, ";"},

      {TokenType::Identifier, "a"},
      {TokenType::LessThan, "<"},
      {TokenType::Identifier, "b"},
      {TokenType::SemiColon, ";"},

      {TokenType::Identifier, "a"},
      {TokenType::LessThanOrEqual, "<="},
      {TokenType::Identifier, "b"},
      {TokenType::SemiColon, ";"},

      {TokenType::Identifier, "a"},
      {TokenType::GreaterThan, ">"},
      {TokenType::Identifier, "b"},
      {TokenType::SemiColon, ";"},

      {TokenType::Identifier, "a"},
      {TokenType::GreaterThanOrEqual, ">="},
      {TokenType::Identifier, "b"},
      {TokenType::SemiColon, ";"},

      {TokenType::Identifier, "a"},
      {TokenType::IsEqualTo, "=="},
      {TokenType::Identifier, "b"},
      {TokenType::SemiColon, ";"},

      {TokenType::Identifier, "a"},
      {TokenType::IsNotEqualTo, "!="},
      {TokenType::Identifier, "b"},
      {TokenType::SemiColon, ";"},

      {TokenType::EndOfFile, ""}};

  ASSERT_EQ(tList.size(), expected.size()) << "Token count mismatch";

  for (size_t i = 0; i < expected.size(); i++) {
    EXPECT_EQ(tList[i].type, expected[i].first)
        << "TokenType mismatch at index " << i;
    EXPECT_EQ(tList[i].literal, expected[i].second)
        << "Token literal mismatch at index " << i;
  }
}