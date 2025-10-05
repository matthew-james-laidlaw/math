#pragma once

#include "AST.h"

#include <functional>
#include <format>

auto GetOp(Token op) -> std::function<double(double, double)>
{
    switch (op.type)
    {
        case Token::Type::Plus: return std::plus<>();
        case Token::Type::Minus: return std::minus<>();
        case Token::Type::Star: return std::multiplies<>();
        case Token::Type::Slash: return std::divides<>();
        default: throw std::runtime_error(std::format("unexpected operator '{}'", op.lexeme));
    }
}

auto TryConstantFolding(Expression*& expr) -> bool
{
    auto bin = dynamic_cast<Binary*>(expr);
    
    if (!bin)
    {
        return false;
    }

    auto lhs = dynamic_cast<Literal*>(bin->left);
    auto rhs = dynamic_cast<Literal*>(bin->right);

    if (!lhs || !rhs)
    {
        return false;
    }

    expr = new Literal(GetOp(bin->op)(lhs->value, rhs->value));
    return true;
}

auto TryIdentityRules(Expression*& expr) -> bool
{
    auto bin = dynamic_cast<Binary*>(expr);
    
    if (!bin)
    {
        return false;
    }

    return true;
}

auto SimplifyStep(Expression*& expr) -> bool
{
    bool changed = false;

    if (auto bin = dynamic_cast<Binary*>(expr))
    {
        changed |= SimplifyStep(bin->left);
        changed |= SimplifyStep(bin->right);

        if (TryConstantFolding(expr))
        {
            return true;
        }

        if (TryIdentityRules(expr))
        {
            return true;
        }
    }

    return changed;
}

auto Simplify(Equation* root) -> void
{
    bool changed = true;

    while (changed)
    {
        changed = SimplifyStep(root->left);
    }

    changed = true;

    while (changed)
    {
        changed = SimplifyStep(root->right);
    }

    return;
}
