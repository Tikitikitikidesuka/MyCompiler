#include "gtest/gtest.h"

#include <iostream>
#include <sstream>

#include "lexer.h"

TEST(LexerTest, TestName) {
    // Temporarily redirect cin to a string stream
    std::istringstream new_cin{"fn fib ( a )"};
    auto cin_rdbuf = std::cin.rdbuf(new_cin.rdbuf());

    Lexer lexer;
    Token token_res = lexer.getToken();
    while (token_res) {
        std::cerr << token_res << " ";
        token_res = lexer.getToken();
    }

    // Reset cin and cout to normal.
    std::cin.rdbuf(cin_rdbuf);

    EXPECT_EQ(3, 3);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}