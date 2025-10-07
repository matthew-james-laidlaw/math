#include "AST.h"

Literal::Literal(double value)
    : value(value)
{}

auto Literal::Accept() -> void
{
    return;
}

Variable::Variable(std::string identifier)
    : identifier(identifier)
{}

auto Variable::Accept() -> void
{
    return;
}

Negation::Negation(Expression* operand)
    : operand(operand)
{}

auto Negation::Accept() -> void
{
    return;
}

Power::Power(Expression* operand, double exponent)
    : operand(operand), exponent(exponent)
{}

auto Power::Accept() -> void
{
    return;
}

Binary::Binary(Expression* lhs, Expression* rhs)
    : lhs(lhs), rhs(rhs)
{}

auto Binary::Accept() -> void
{
    return;
}

Addition::Addition(Expression* lhs, Expression* rhs)
    : Binary(lhs, rhs)
{}

auto Addition::Accept() -> void
{
    return;
}

Multiplication::Multiplication(Expression* lhs, Expression* rhs)
    : Binary(lhs, rhs)
{}

auto Multiplication::Accept() -> void
{
    return;
}

Equation::Equation(Expression* lhs, Expression* rhs)
    : Binary(lhs, rhs)
{}

auto Equation::Accept() -> void
{
    return;
}
