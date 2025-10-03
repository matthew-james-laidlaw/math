#include <gtest/gtest.h>

#include <Lexer.h>

using namespace std::string_literals;

TEST(LexerTests, LexIdentifier)
{
    auto source = "abc"s;
    auto lexed = Lex(source);

    EXPECT_EQ(lexed.size(), 1);
    EXPECT_EQ(lexed[0].type, Token::Type::Identifier);
    EXPECT_EQ(lexed[0].lexeme, "abc");
}

TEST(LexerTests, LexNumber)
{
    auto source = "123"s;
    auto lexed = Lex(source);
        
    EXPECT_EQ(lexed.size(), 1);
    EXPECT_EQ(lexed[0].type, Token::Type::Number);
    EXPECT_EQ(lexed[0].lexeme, "123");
}

TEST(LexerTests, LexOperator)
{
    auto source = "+"s;
    auto lexed = Lex(source);

    EXPECT_EQ(lexed.size(), 1);
    EXPECT_EQ(lexed[0].type, Token::Type::Plus);
    EXPECT_EQ(lexed[0].lexeme, "+");
}

TEST(LexerTests, LexMany)
{
    auto source = "x + 1"s;
    auto lexed = Lex(source);

    EXPECT_EQ(lexed.size(), 3);

    EXPECT_EQ(lexed[0].type, Token::Type::Identifier);
    EXPECT_EQ(lexed[0].lexeme, "x");

    EXPECT_EQ(lexed[1].type, Token::Type::Plus);
    EXPECT_EQ(lexed[1].lexeme, "+");

    EXPECT_EQ(lexed[2].type, Token::Type::Number);
    EXPECT_EQ(lexed[2].lexeme, "1");
}
