#include "Parser.h"

#include <format>
#include <stdexcept>

Parser::Parser(std::vector<Token> const& source)
    : source(source), iter(source.cbegin())
{}

auto Parser::Parse() -> Expression*
{
    return ParseEquation();
}

auto Parser::ParseEquation() -> Expression*
{
    auto left = ParseAdditiveOperation();

    if ((iter++)->type != Token::Type::Equals)
    {
        throw std::runtime_error("expected an equation");
    }

    auto right = ParseAdditiveOperation();

    return new Equation(left, right);
}

auto Parser::ParseAdditiveOperation() -> Expression*
{
    auto root = ParseMultiplicativeOperation();

    while (!Done() && (iter->type == Token::Type::Plus || iter->type == Token::Type::Minus))
    {
        auto op = *(iter++);
        auto right = ParseMultiplicativeOperation();
        root = new Binary(root, right, op);
    }

    return root;
}

auto Parser::ParseMultiplicativeOperation() -> Expression*
{
    auto root = ParseUnary();

    while (!Done() && (iter->type == Token::Type::Star || iter->type == Token::Type::Slash))
    {
        auto op = *(iter++);
        auto right = ParseUnary();
        root = new Binary(root, right, op);
    }

    return root;
}

auto Parser::ParseUnary() -> Expression*
{
    auto current = *iter;
    if (current.type == Token::Type::Minus)
    {
        ++iter;
        return new Unary(ParseUnary(), current);
    }
    else
    {
        return ParsePrimary();
    }
}

auto Parser::ParsePrimary() -> Expression*
{
    auto current = *(iter++);
    switch (current.type)
    {
        case Token::Type::Identifier: return new Variable(current.lexeme);
        case Token::Type::Number: return new Literal(std::stod(current.lexeme));
        default: throw std::runtime_error(std::format("unexpected token '{}'", current.lexeme));
    }
}

auto Parser::Done() const -> bool
{
    return iter == source.cend();
}

auto Parse(std::vector<Token> const& source) -> Expression*
{
    auto parser = Parser(source);
    return parser.Parse();
}

auto Parse(std::string const& source) -> Expression*
{
    auto lexed = Lex(source);
    return Parse(lexed);
}
