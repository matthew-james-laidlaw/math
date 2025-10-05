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
    EXPECT_NE(lit, nullptr);
    EXPECT_EQ(lit->value, 3.0);
}
