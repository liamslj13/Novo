#include <iostream>
#include "src/Lexer.cpp"

int main() {
    std::string in = R"(
x y z "hello" 123 456

func myFunc() {
    if x < 10 {
        ret i32_type
    } else {
        ret str_type
    }
}

i32_type a := 42;
i64_type b := 10000000000;
str_type s := "world";

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
    l.input = in;
    std::vector<Token> t = l.tokenizeInput();

    int cur = 1;
    for (const auto& token : t) {
      std::cout << ' ' + Token::toString(token) + ' ';
      std::cout << cur << std::endl;
      cur++;
    }

    std::cout << '\n';
}