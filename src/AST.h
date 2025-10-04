#pragma once

#include "Token.h"

class Expression
{
public:

    virtual ~Expression() = default;

};

class Literal : public Expression
{
public:

    double value;

    Literal(double value)
        : value(value)
    {}

};

class Variable : public Expression
{
public:

    std::string identifier;

    Variable(std::string identifier)
        : identifier(identifier)
    {}

};

class Binary : public Expression
{
public:

    Expression* left;
    Expression* right;
    Token op;

    Binary(Expression* left, Expression* right, Token op)
        : left(left), right(right), op(op)
    {}

};

class Unary : public Expression
{
public:

    Expression* operand;
    Token op;

    Unary(Expression* operand, Token op)
        : operand(operand), op(op)
    {}
    
};

class Equation : public Expression
{
public:

    Expression* left;
    Expression* right;

    Equation(Expression* left, Expression* right)
        : left(left), right(right)
    {}

};
