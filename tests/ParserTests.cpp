#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Parser.h>

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

MATCHER_P(IsBinary, op, "")
{
    auto bin = dynamic_cast<Binary*>(arg);
    return bin && bin->op.type == op;
}

TEST(ParserTests, ParseIdentifier)
{
    auto source = "abc"s;
    auto ast = Parse(source);
    EXPECT_THAT(ast, IsVariable("abc"));
}

TEST(ParserTests, ParseNumber)
{
    auto source = "123"s;
    auto ast = Parse(source);
    EXPECT_THAT(ast, IsLiteral(123.0));
}

TEST(ParserTests, ParseExpression)
{
    auto source = "1 + 2 * 3 + 4";
    auto ast = Parse(source);

    auto root = dynamic_cast<Binary*>(ast);
    ASSERT_THAT(root, IsBinary(Token::Type::Plus));

    auto left = dynamic_cast<Binary*>(root->left);
    ASSERT_THAT(left, IsBinary(Token::Type::Plus));

    EXPECT_THAT(root->right, IsLiteral(4.0));
    EXPECT_THAT(left->left, IsLiteral(1.0));

    auto mul = dynamic_cast<Binary*>(left->right);
    ASSERT_THAT(mul, IsBinary(Token::Type::Star));

    EXPECT_THAT(mul->left, IsLiteral(2.0));
    EXPECT_THAT(mul->right, IsLiteral(3.0));
}
