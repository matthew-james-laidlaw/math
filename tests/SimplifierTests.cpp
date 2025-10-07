#include <gtest/gtest.h>

#include <Parser.h>
#include <Simplifier.h>

using namespace std::string_literals;

TEST(SimplifierTests, ConstantFolding)
{
    auto source = "1 + 2"s;
    auto ast = Parser(Lexer(source).Lex()).ParseAdditiveOperation();

    SimplifyStep(ast);

    auto lit = dynamic_cast<Literal*>(ast);
    ASSERT_NE(lit, nullptr);
    ASSERT_EQ(lit->value, 3.0);
}

TEST(SimplifierTests, AdditiveIdentityLeft)
{
    auto source = "0 + x"s;
    auto ast = Parser(Lexer(source).Lex()).ParseAdditiveOperation();

    SimplifyStep(ast);

    auto var = dynamic_cast<Variable*>(ast);
    ASSERT_NE(var, nullptr);
    ASSERT_EQ(var->identifier, "x");
}

TEST(SimplifierTests, AdditiveIdentityRight)
{
    auto source = "x + 0"s;
    auto ast = Parser(Lexer(source).Lex()).ParseAdditiveOperation();

    SimplifyStep(ast);

    auto var = dynamic_cast<Variable*>(ast);
    ASSERT_NE(var, nullptr);
    ASSERT_EQ(var->identifier, "x");
}

TEST(SimplifierTests, SubtractionIdentity)
{
    auto source = "x - 0"s;
    auto ast = Parser(Lexer(source).Lex()).ParseAdditiveOperation();

    SimplifyStep(ast);

    auto var = dynamic_cast<Variable*>(ast);
    ASSERT_NE(var, nullptr);
    ASSERT_EQ(var->identifier, "x");
}

TEST(SimplifierTests, MultiplicativeIdentityLeft)
{
    auto source = "1 * x"s;
    auto ast = Parser(Lexer(source).Lex()).ParseMultiplicativeOperation();

    SimplifyStep(ast);

    auto var = dynamic_cast<Variable*>(ast);
    ASSERT_NE(var, nullptr);
    ASSERT_EQ(var->identifier, "x");
}

TEST(SimplifierTests, MultiplicativeIdentityRight)
{
    auto source = "x * 1"s;
    auto ast = Parser(Lexer(source).Lex()).ParseMultiplicativeOperation();

    SimplifyStep(ast);

    auto var = dynamic_cast<Variable*>(ast);
    ASSERT_NE(var, nullptr);
    ASSERT_EQ(var->identifier, "x");
}

TEST(SimplifierTests, DivisionIdentity)
{
    auto source = "x / 1"s;
    auto ast = Parser(Lexer(source).Lex()).ParseAdditiveOperation();

    SimplifyStep(ast);

    auto var = dynamic_cast<Variable*>(ast);
    ASSERT_NE(var, nullptr);
    ASSERT_EQ(var->identifier, "x");
}
