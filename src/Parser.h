#pragma once

#include "AST.h"
#include "Lexer.h"

class Parser
{
private:

    std::vector<Token> const& source;
    std::vector<Token>::const_iterator iter;

public:

    Parser(std::vector<Token> const& source);

    auto Parse() -> Equation*;
    
    auto ParseAdditiveOperation() -> Expression*;
    auto ParseMultiplicativeOperation() -> Expression*;
    auto ParseUnary() -> Expression*;
    auto ParsePrimary() -> Expression*;
    
    auto Done() const -> bool;

};

auto Parse(std::vector<Token> const& source) -> Equation*;
auto Parse(std::string const& source) -> Equation*;
