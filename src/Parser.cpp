#include "Parser.h"

#include <format>
#include <stdexcept>

Parser::Parser(std::vector<Token> const& source)
    : source(source), iter(source.cbegin())
{}

auto Parser::Parse() -> Equation*
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

        if (op.type == Token::Type::Minus)
        {
            right = new Negation(right);
        }

        root = new Addition(root, right);
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

        if (op.type == Token::Type::Slash)
        {
            right = new Power(right, -1.0);
        }

        root = new Multiplication(root, right);
    }

    return root;
}

auto Parser::ParseUnary() -> Expression*
{
    if (iter->type == Token::Type::Minus)
    {
        ++iter;
        return new Negation(ParseUnary());
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

auto Parse(std::vector<Token> const& source) -> Equation*
{
    auto parser = Parser(source);
    return parser.Parse();
}

auto Parse(std::string const& source) -> Equation*
{
    auto lexed = Lex(source);
    return Parse(lexed);
}
