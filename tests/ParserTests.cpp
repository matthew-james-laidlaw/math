#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Parser.h>
#include <Lexer.h>

using namespace std::string_literals;

MATCHER_P(IsVariable, identifier, "")
{
    auto var = dynamic_cast<Variable*>(arg);
    return var && var->identifier == identifier;
}

MATCHER_P(IsLiteral, value, "")
{
    auto lit = dynamic_cast<Literal*>(arg);
    return lit && lit->value == value;
}

MATCHER_P2(IsAddition, lhs_matcher, rhs_matcher, "")
{
    auto add = dynamic_cast<Addition*>(arg);
    return add
        && ExplainMatchResult(lhs_matcher, add->lhs, result_listener)
        && ExplainMatchResult(rhs_matcher, add->rhs, result_listener);
}

MATCHER_P2(IsMultiplication, lhs_matcher, rhs_matcher, "")
{
    auto add = dynamic_cast<Multiplication*>(arg);
    return add
        && ExplainMatchResult(lhs_matcher, add->lhs, result_listener)
        && ExplainMatchResult(rhs_matcher, add->rhs, result_listener);
}

MATCHER_P2(IsEquation, lhs_matcher, rhs_matcher, "")
{
    auto add = dynamic_cast<Equation*>(arg);
    return add
        && ExplainMatchResult(lhs_matcher, add->lhs, result_listener)
        && ExplainMatchResult(rhs_matcher, add->rhs, result_listener);
}

TEST(ParserTests, ParseIdentifier)
{
    auto source = "abc"s;
    auto ast = Parser(Lexer(source).Lex()).ParseAdditiveOperation();
    ASSERT_THAT(ast, IsVariable("abc"));
}

TEST(ParserTests, ParseNumber)
{
    auto source = "123"s;
    auto ast = Parser(Lexer(source).Lex()).ParseAdditiveOperation();
    ASSERT_THAT(ast, IsLiteral(123.0));
}

TEST(ParserTests, ParseExpression)
{
    auto source = "1 + 2 * 3"s;
    auto ast = Parser(Lexer(source).Lex()).ParseAdditiveOperation();
    ASSERT_THAT(ast,
        IsAddition(
            IsLiteral(1.0),
            IsMultiplication(
                IsLiteral(2.0),
                IsLiteral(3.0)
            )
        )
    );
}

TEST(ParserTests, ParseEquation)
{
    auto source = "1 + 2 = 3 * 4"s;
    auto ast = Parser(Lexer(source).Lex()).ParseAdditiveOperation();
    ASSERT_THAT(ast,
        IsEquation(
            IsAddition(
                IsLiteral(1.0),
                IsLiteral(2.0)
            ),
            IsMultiplication(
                IsLiteral(3.0),
                IsLiteral(4.0)
            )
        )
    );
}
