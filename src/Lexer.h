#pragma once

#include "Token.h"

#include <string>
#include <vector>

class Lexer
{
private:

    std::string const& source;
    std::string::const_iterator iter;

public:

    Lexer(std::string const& source);

    auto Lex() -> std::vector<Token>;

private:

    auto LexElement() -> Token;
    auto LexIdentifier() -> Token;
    auto LexNumber() -> Token;
    auto LexOperator() -> Token;

    auto ConsumeWhitespace() -> void;

    auto Done() const -> bool;

};

auto Lex(std::string const& source) -> std::vector<Token>;
