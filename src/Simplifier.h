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

    auto lhs_lit = dynamic_cast<Literal*>(bin->left);
    auto rhs_lit = dynamic_cast<Literal*>(bin->right);

    if (bin->op.type == Token::Type::Plus)
    {
        bool additive_identity_left = lhs_lit && lhs_lit->value == 0.0;
        bool additive_identity_right = rhs_lit && rhs_lit->value == 0.0;
        if (additive_identity_left) { expr = bin->right; return true; }
        if (additive_identity_right) { expr = bin->left; return true; }
    }
    else if (bin->op.type == Token::Type::Minus)
    {
        bool subtraction_identity = rhs_lit && rhs_lit->value == 0.0;
        if (subtraction_identity) { expr = bin->left; return true; }
    }
    else if (bin->op.type == Token::Type::Star)
    {
        bool multiplicative_identity_left = lhs_lit && lhs_lit->value == 1.0;
        bool multiplicative_identity_right = rhs_lit && rhs_lit->value == 1.0;
        if (multiplicative_identity_left) { expr = bin->right; return true; }
        if (multiplicative_identity_right) { expr = bin->left; return true; }
    }
    else if (bin->op.type == Token::Type::Slash)
    {
        bool division_identity = rhs_lit && rhs_lit->value == 1.0;
        if (division_identity) { expr = bin->left; return true; }
    }

    return false;
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
