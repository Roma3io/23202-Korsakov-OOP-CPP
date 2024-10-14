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

TEST(FileWriter, write)
{
    std::string fileName = "test_write.txt";
    FileWriter fileWriter(fileName);
    fileWriter.open();
    std::vector<std::string> lines = {
            "Line 1",
            "Line 2",
            "Line 3"};
    fileWriter.write(lines);
    fileWriter.close();
    std::string expected = "Line 1\nLine 2\nLine 3\n";
    std::string actual = readFileContent(fileName);
    ASSERT_EQ(actual, expected);
}