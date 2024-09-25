#include "../src/Parser.h"
#include "gtest/gtest.h"

TEST(Parser, splitIntoWords)
{
    std::string input = "Hello, World!";
    std::list<std::string> expected = {"hello", "world"};
    std::list<std::string> result = Parser::splitIntoWords(input);
    ASSERT_EQ(result, expected);
}

TEST(Parser, splitIntoWordsWithPunctuationAndCase)
{
    std::string input = "Hello, World! This is a Test.";
    std::list<std::string> expected = {"hello", "world", "this", "is", "a", "test"};
    std::list<std::string> result = Parser::splitIntoWords(input);
    ASSERT_EQ(result, expected);
}

TEST(Parser, splitIntoWordsEmptyString)
{
    std::string input = "";
    std::list<std::string> expected = {};
    std::list<std::string> result = Parser::splitIntoWords(input);
    ASSERT_EQ(result, expected);
}

// Тест для проверки разбиения строки с пробелами
TEST(Parser, splitIntoWordsWithSpaces)
{
    std::string input = "   Hello   World   ";
    std::list<std::string> expected = {"hello", "world"};
    std::list<std::string> result = Parser::splitIntoWords(input);
    ASSERT_EQ(result, expected);
}

TEST(Parser, splitIntoWordsWithMultipleSpaces)
{
    std::string input = "Hello   World";
    std::list<std::string> expected = {"hello", "world"};
    std::list<std::string> result = Parser::splitIntoWords(input);
    ASSERT_EQ(result, expected);
}

TEST(Parser, splitIntoWordsWithNumbers)
{
    std::string input = "Hello123 World456";
    std::list<std::string> expected = {"hello123", "world456"};
    std::list<std::string> result = Parser::splitIntoWords(input);
    ASSERT_EQ(result, expected);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}