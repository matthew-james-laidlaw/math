#pragma once

#include <string>

/*=========================*
 |     Base Expression     |
 *=========================*/

class Expression
{
public:
    virtual ~Expression() = default;
    virtual auto Accept() -> void = 0;
};

/*=============================*
 |     Primary Expressions     |
 *=============================*/

class Literal : public Expression
{
public:
    double value;
    Literal(double value);
    auto Accept() -> void override;
};

class Variable : public Expression
{
public:
    std::string identifier;
    Variable(std::string identifier);
    auto Accept() -> void override;
};

/*===========================*
 |     Unary Expressions     |
 *===========================*/

class Negation : public Expression
{
public:
    Expression* operand;
    Negation(Expression* operand);
    auto Accept() -> void override;
};

class Power : public Expression
{
public:
    Expression* operand;
    double exponent;
    Power(Expression* operand, double exponent);
    auto Accept() -> void override;
};

/*============================*
 |     Binary Expressions     |
 *============================*/

class Binary : public Expression
{
public:
    Expression* lhs;
    Expression* rhs;
    Binary(Expression* lhs, Expression* rhs);
    ~Binary() = default;
    virtual auto Accept() -> void = 0;
};

class Addition : public Binary
{
public:
    Expression* lhs;
    Expression* rhs;
    Addition(Expression* lhs, Expression* rhs);
    auto Accept() -> void override;
};

class Multiplication : public Binary
{
public:
    Expression* lhs;
    Expression* rhs;
    Multiplication(Expression* lhs, Expression* rhs);
    auto Accept() -> void override;
};

/*============================*
 |     Equation Statement     |
 *============================*/

class Equation : public Binary
{
public:
    Expression* lhs;
    Expression* rhs;
    Equation(Expression* lhs, Expression* rhs);
    auto Accept() -> void override;
};
