#include "gtest/gtest.h"

#include "lexer.h"

TEST(LexerTest, TestName) {
    EXPECT_EQ(3, 3);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}