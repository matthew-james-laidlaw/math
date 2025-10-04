#pragma once

#include <string>

struct Token
{
    enum class Type
    {
        Plus, Minus, Star, Slash,
        Identifier, Number, Equals
    };

    Type type;
    std::string lexeme;
};
