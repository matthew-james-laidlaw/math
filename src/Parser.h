#pragma once

#include "AST.h"
#include "Lexer.h"

class Parser
{
private:

    std::vector<Token> const& source;
    std::vector<Token>::const_iterator iter;

public:

    Parser(std::vector<Token> const& source)
        : source(source), iter(source.cbegin())
    {}

    auto Parse() -> Expression*
    {

    }

private:

    auto Done() const -> bool
    {
        return iter == source.cend();
    }

};

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
