#include "Lexer.h"

#include <algorithm>
#include <format>
#include <stdexcept>

Lexer::Lexer(std::string const& source)
    : source(source), iter(source.cbegin())
{}

auto Lexer::Lex() -> std::vector<Token>
{
    auto tokens = std::vector<Token>();

    ConsumeWhitespace();

    while (!Done())
    {
        tokens.push_back(LexElement());
        ConsumeWhitespace();
    }

    return tokens;
}

auto Lexer::LexElement() -> Token
{
    if (std::isalpha(*iter) || *iter == '_')
    {
        return LexIdentifier();
    }
    else if (std::isdigit(*iter) || *iter == '.')
    {
        return LexNumber();
    }
    else if (std::string("+-*/").contains(*iter))
    {
        return LexOperator();
    }

    throw std::runtime_error(std::format("unexpected character '{}'", *iter));
}

auto Lexer::LexIdentifier() -> Token
{
    auto start = iter;
    while (!Done() && (std::isalnum(*iter) || *iter == '_'))
    {
        ++iter;
    }

    return Token {
        .type = Token::Type::Identifier,
        .lexeme = std::string(start, iter)
    };
}

auto Lexer::LexNumber() -> Token
{
    auto start = iter;
    while (!Done() && (std::isdigit(*iter) || *iter == '.'))
    {
        ++iter;
    }

    auto lexeme = std::string(start, iter);
    if (std::count(lexeme.begin(), lexeme.end(), '.') > 1)
    {
        throw std::runtime_error(std::format("invalid number '{}'", lexeme));
    }

    return Token {
        .type = Token::Type::Number,
        .lexeme = lexeme
    };
}

auto Lexer::LexOperator() -> Token
{
    switch (*(iter++))
    {
        case '+': return Token {
            .type = Token::Type::Plus,
            .lexeme = "+"
        };
        case '-': return Token {
            .type = Token::Type::Minus,
            .lexeme = "-"
        };
        case '*': return Token {
            .type = Token::Type::Star,
            .lexeme = "*"
        };
        case '/': return Token {
            .type = Token::Type::Slash,
            .lexeme = "/"
        };
        default: throw std::runtime_error(std::format("unexpected operator '{}'", *iter));
    }
}

auto Lexer::ConsumeWhitespace() -> void
{
    while (!Done() && std::isspace(*iter))
    {
        ++iter;
    }
}

auto Lexer::Done() const -> bool
{
    return iter == source.cend();
}

auto Lex(std::string const& source) -> std::vector<Token>
{
    auto lexer = Lexer(source);
    return lexer.Lex();
}
