#include "../src/FileWriter.h"
#include "gtest/gtest.h"
#include <fstream>
#include <string>
#include <vector>

std::string readFileContent(const std::string &fileName)
{
    std::ifstream file(fileName);
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return content;
}

TEST(FileWriter, open)
{
    std::string fileName = "test_open.txt";
    FileWriter fileWriter(fileName);
    fileWriter.open();
    ASSERT_TRUE(fileWriter.isOpen());
    fileWriter.close();
}

TEST(FileWriter, close)
{
    std::string fileName = "test_close.txt";
    FileWriter fileWriter(fileName);
    fileWriter.open();
    fileWriter.close();
    ASSERT_FALSE(fileWriter.isOpen());
}

TEST(FileWriter, writeWordsFrequencyToFile)
{
    std::string fileName = "test_write_words_frequency.txt";
    FileWriter fileWriter(fileName);
    fileWriter.open();
    std::vector<std::pair<std::string, int>> sortedWords = {
            {"word1", 3},
            {"word2", 2},
            {"word3", 1}};
    int wordsAmount = 6;
    fileWriter.writeWordsFrequencyToFile(sortedWords, wordsAmount);
    fileWriter.close();
    std::string expectedContent = "Word, Frequency, Frequency(%)\nword1,3,50.00\nword2,2,33.33\nword3,1,16.67\n";
    std::string actualContent = readFileContent(fileName);
    ASSERT_EQ(actualContent, expectedContent);
}

TEST(FileWriter, writeWordsFrequencyToFileEmptyList)
{
    std::string fileName = "test_write_words_frequency_empty_list.txt";
    FileWriter fileWriter(fileName);
    fileWriter.open();
    std::vector<std::pair<std::string, int>> sortedWords = {};
    int wordsAmount = 0;
    fileWriter.writeWordsFrequencyToFile(sortedWords, wordsAmount);
    fileWriter.close();
    std::string expectedContent = "Word, Frequency, Frequency(%)\n";
    std::string actualContent = readFileContent(fileName);
    ASSERT_EQ(actualContent, expectedContent);
}