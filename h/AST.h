#pragma once

#include "Token.h"
#include <vector>

namespace Novo {

class Node {
public:
  virtual ~Node() {};
  virtual std::string TokenLiteral() = 0;
  virtual std::string String() = 0;
  virtual std::string Type() = 0;
};

class Statement : public Node {
public:
  virtual void statementNode() = 0;
  virtual std::string TokenLiteral() = 0;
  virtual std::string String() = 0;
  virtual std::string Type() = 0;
};

class Expression : public Node {
public:
  virtual std::string TokenLiteral() = 0;
  virtual std::string String() = 0;
  virtual std::string Type() = 0;
};

class Program : public Node {
public:
  std::vector<std::shared_ptr<Statement>> statements;

  std::string TokenLiteral();
  std::string String();
  std::string Type() { return "Program"; }
};

class BlockStatement;

class Identifier : public Expression {
public:
  Token t;
  std::string value;

  std::string TokenLiteral() { return t.literal; }
  std::string String() { return value; }
  std::string Type() { return "Identifier"; }
};

class IntegerLiteral : public Expression {
public:
  Token t;
  int value;

  std::string TokenLiteral() { return t.literal; }
  std::string String() { return value; }
  std::string Type() { return "IntegerLiteral"; }
};

class StringLiteral : public Expression {
public:
  Token t;
  std::string value;

  std::string TokenLiteral() { return t.literal; }
  std::string String() { return value; }
  std::string Type() { return "StringLiteral"; }
};

class FunctionLiteral : public Expression {
public:
  Token t;
  std::vector<std::unique_ptr<Identifier>> parameters;
  std::unique_ptr<BlockStatement> body;

  std::string TokenLiteral() { return t.literal; }
  std::string String();
  std::string Type() { return "FunctionLiteral"; }
};

class ArrayLiteral : public Expression {
public:
  Token t;
  std::vector<std::unique_ptr<Expression>> elements;

  std::string TokenLiteral() { return t.literal; }
  std::string String();
  std::string Type() { return "ArrayLiteral"; }
};

class CallExpression : public Expression {
public:
  Token t;
  std::unique_ptr<Expression> function;
  std::vector<std::unique_ptr<Expression>> arguments;

  std::string TokenLiteral() { return t.literal; }
  std::string String();
  std::string Type() { return "CallExpression"; }
};

class IndexExpression : public Expression {
public:
  Token t;
  std::unique_ptr<Expression> index;
  std::unique_ptr<Expression> array;

  std::string TokenLiteral() { return t.literal; }
  std::string String();
  std::string Type() { return "IndexExpression"; }
};

class PrefixExpression : public Expression {
public:
  Token t;
  std::string op;
  std::unique_ptr<Expression> rhs;

  std::string TokenLiteral() { return t.literal; }
  std::string String();
  std::string Type() { return "PrefixExpression"; }
};

/*
class InfixExpression : public Expression {
public:

};
*/



} // namespace Novo