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

    auto lhs = dynamic_cast<Literal*>(bin->lhs);
    auto rhs = dynamic_cast<Literal*>(bin->rhs);

    if (!lhs || !rhs)
    {
        return false;
    }

    auto addition = dynamic_cast<Addition*>(bin);
    if (addition)
    {
        expr = new Literal(lhs->value + rhs->value);
        return true;
    }

    auto multiplication = dynamic_cast<Multiplication*>(bin);
    if (multiplication)
    {
        expr = new Literal(lhs->value * rhs->value);
        return true;
    }

    return false;
}

auto TryIdentityRules(Expression*& expr) -> bool
{
    auto bin = dynamic_cast<Binary*>(expr);
    
    if (!bin)
    {
        return false;
    }
    
    auto is_addition = dynamic_cast<Addition*>(bin);
    if (is_addition)
    {
        auto lhs_lit = dynamic_cast<Literal*>(bin->lhs);
        bool additive_identity_lhs = lhs_lit && lhs_lit->value == 0.0;
        if (additive_identity_lhs)
        {
            expr = bin->rhs;
            return true;
        }
        
        auto rhs_lit = dynamic_cast<Literal*>(bin->rhs);
        bool additive_identity_rhs = rhs_lit && rhs_lit->value == 0.0;
        if (additive_identity_rhs)
        {
            expr = bin->lhs;
            return true;
        }
        
        return false;
    }
    
    auto is_multiplication = dynamic_cast<Multiplication*>(bin);
    if (is_multiplication)
    {
        auto lhs_lit = dynamic_cast<Literal*>(bin->lhs);
        bool multiplicative_identity_lhs = lhs_lit && lhs_lit->value == 1.0;
        if (multiplicative_identity_lhs)
        {
            expr = bin->rhs;
            return true;
        }
        
        auto rhs_lit = dynamic_cast<Literal*>(bin->rhs);
        bool multiplicative_identity_rhs = rhs_lit && rhs_lit->value == 1.0;
        if (multiplicative_identity_rhs)
        {
            expr = bin->lhs;
            return true;
        }
        
        return false;
    }

    return false;
}

auto SimplifyStep(Expression*& expr) -> bool
{
    bool changed = false;

    if (auto bin = dynamic_cast<Binary*>(expr))
    {
        changed |= SimplifyStep(bin->lhs);
        changed |= SimplifyStep(bin->rhs);

        if (TryConstantFolding(expr))
        {
            return true;
        }

        if (TryIdentityRules(expr))
        {
            return true;
        }

        // if (TryAnnihilationRules(expr))
        // {
        //     return true;
        // }

        // if (TryCancellationRules(expr))
        // {
        //     return true;
        // }
    }

    return changed;
}

auto Simplify(Equation* root) -> void
{
    bool changed = true;

    while (changed)
    {
        changed = SimplifyStep(root->lhs);
    }

    changed = true;

    while (changed)
    {
        changed = SimplifyStep(root->rhs);
    }

    return;
}
