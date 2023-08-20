#include "gtest/gtest.h"

#include <iostream>
#include <sstream>
#include <vector>

#include "lexer.h"

void lexer_test(const std::string& input, const std::vector<Token>& expected_tokens) {
    // Setup
    std::istringstream test_stream{input};
    std::vector<Token> results;
    Lexer lexer(test_stream);


    // Run test
    Token token = lexer.nextToken();
    while (token.getType() != TokenType::TOK_EOF) {
        results.push_back(token);
        token = lexer.nextToken();
    }
    results.push_back(Token(TokenType::TOK_EOF, ""));

    // Validate results
    EXPECT_EQ(results.size(), expected_tokens.size());
    for (int i = 0; i < results.size(); ++i) {
        EXPECT_EQ(results[i], expected_tokens[i]);
    }
}

TEST(LexerTest, PlusToken) {
    std::vector<Token> expected_tokens;
    expected_tokens.push_back(Token(TokenType::TOK_PLUS, "+"));
    expected_tokens.push_back(Token(TokenType::TOK_EOF, ""));

    lexer_test("+", expected_tokens);
}

TEST(LexerTest, MinusToken) {
    std::vector<Token> expected_tokens;
    expected_tokens.push_back(Token(TokenType::TOK_MINUS, "-"));
    expected_tokens.push_back(Token(TokenType::TOK_EOF, ""));

    lexer_test("-", expected_tokens);
}

TEST(LexerTest, AssignToken) {
    std::vector<Token> expected_tokens;
    expected_tokens.push_back(Token(TokenType::TOK_ASSIGN, "="));
    expected_tokens.push_back(Token(TokenType::TOK_EOF, ""));

    lexer_test("=", expected_tokens);
}

TEST(LexerTest, ParenthesisOpenToken) {
    std::vector<Token> expected_tokens;
    expected_tokens.push_back(Token(TokenType::TOK_PARENTHESIS_OPEN, "("));
    expected_tokens.push_back(Token(TokenType::TOK_EOF, ""));

    lexer_test("(", expected_tokens);
}

TEST(LexerTest, ParenthesisCloseToken) {
    std::vector<Token> expected_tokens;
    expected_tokens.push_back(Token(TokenType::TOK_PARENTHESIS_CLOSE, ")"));
    expected_tokens.push_back(Token(TokenType::TOK_EOF, ""));

    lexer_test(")", expected_tokens);
}


TEST(LexerTest, SpacesBeforeToken) {
    std::vector<Token> expected_tokens;
    expected_tokens.push_back(Token(TokenType::TOK_PLUS, "+"));
    expected_tokens.push_back(Token(TokenType::TOK_EOF, ""));

    lexer_test("   \t \n +", expected_tokens);
}

TEST(LexerTest, SpacesAfterToken) {
    std::vector<Token> expected_tokens;
    expected_tokens.push_back(Token(TokenType::TOK_ASSIGN, "="));
    expected_tokens.push_back(Token(TokenType::TOK_EOF, ""));

    lexer_test("= \t  \t \n ", expected_tokens);
}

TEST(LexerTest, SpacesSurroundingToken) {
    std::vector<Token> expected_tokens;
    expected_tokens.push_back(Token(TokenType::TOK_PARENTHESIS_CLOSE, ")"));
    expected_tokens.push_back(Token(TokenType::TOK_EOF, ""));

    lexer_test("   \t\t \n ) \t\n   \t", expected_tokens);
}

TEST(LexerTest, AllReservedWordTokens) {
    std::vector<Token> expected_tokens;
    expected_tokens.push_back(Token(TokenType::TOK_PLUS, "+"));
    expected_tokens.push_back(Token(TokenType::TOK_PLUS, "+"));
    expected_tokens.push_back(Token(TokenType::TOK_MINUS, "-"));
    expected_tokens.push_back(Token(TokenType::TOK_PARENTHESIS_OPEN, "("));
    expected_tokens.push_back(Token(TokenType::TOK_PLUS, "+"));
    expected_tokens.push_back(Token(TokenType::TOK_ASSIGN, "="));
    expected_tokens.push_back(Token(TokenType::TOK_ASSIGN, "="));
    expected_tokens.push_back(Token(TokenType::TOK_PARENTHESIS_CLOSE, ")"));
    expected_tokens.push_back(Token(TokenType::TOK_PARENTHESIS_CLOSE, ")"));
    expected_tokens.push_back(Token(TokenType::TOK_ASSIGN, "="));
    expected_tokens.push_back(Token(TokenType::TOK_PLUS, "+"));
    expected_tokens.push_back(Token(TokenType::TOK_MINUS, "-"));
    expected_tokens.push_back(Token(TokenType::TOK_EOF, ""));

    lexer_test("  + \t \n +   - \t (  + = =))= + - ", expected_tokens);
}

TEST(LexerTest, IdentifierToken) {
    std::vector<Token> expected_tokens;
    expected_tokens.push_back(Token(TokenType::TOK_ID, "fib"));
    expected_tokens.push_back(Token(TokenType::TOK_EOF, ""));

    lexer_test("fib", expected_tokens);
}

TEST(LexerTest, NumberToken) {
    std::vector<Token> expected_tokens;
    expected_tokens.push_back(Token(TokenType::TOK_NUM, "33"));
    expected_tokens.push_back(Token(TokenType::TOK_EOF, ""));

    lexer_test("33", expected_tokens);
}

TEST(LexerTest, SmallProgram) {
    std::vector<Token> expected_tokens;
    expected_tokens.push_back(Token(TokenType::TOK_ID, "a"));
    expected_tokens.push_back(Token(TokenType::TOK_ASSIGN, "="));
    expected_tokens.push_back(Token(TokenType::TOK_NUM, "1"));
    expected_tokens.push_back(Token(TokenType::TOK_ID, "b"));
    expected_tokens.push_back(Token(TokenType::TOK_ASSIGN, "="));
    expected_tokens.push_back(Token(TokenType::TOK_NUM, "2"));
    expected_tokens.push_back(Token(TokenType::TOK_ID, "c"));
    expected_tokens.push_back(Token(TokenType::TOK_ASSIGN, "="));
    expected_tokens.push_back(Token(TokenType::TOK_ID, "b"));
    expected_tokens.push_back(Token(TokenType::TOK_PLUS, "+"));
    expected_tokens.push_back(Token(TokenType::TOK_ID, "a"));
    expected_tokens.push_back(Token(TokenType::TOK_MINUS, "-"));
    expected_tokens.push_back(Token(TokenType::TOK_PARENTHESIS_OPEN, "("));
    expected_tokens.push_back(Token(TokenType::TOK_NUM, "3"));
    expected_tokens.push_back(Token(TokenType::TOK_PLUS, "+"));
    expected_tokens.push_back(Token(TokenType::TOK_ID, "b"));
    expected_tokens.push_back(Token(TokenType::TOK_PARENTHESIS_CLOSE, ")"));
    expected_tokens.push_back(Token(TokenType::TOK_EOF, ""));

    lexer_test("a = 1\nb=2\nc =b+a -(3 +b)\n", expected_tokens);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}