#include "../src/FileReader.h"
#include "gtest/gtest.h"
#include <fstream>

void createTempFile(const std::string &fileName, const std::string &content)
{
    std::ofstream file(fileName);
    file << content;
    file.close();
}

TEST(FileReader, open)
{
    std::string fileName = "test_open.txt";
    createTempFile(fileName, "Hello, World!");
    FileReader fileReader(fileName);
    fileReader.open();
    ASSERT_TRUE(fileReader.isOpen());
    fileReader.close();
}

TEST(FileReader, next)
{
    std::string fileName = "test_next.txt";
    createTempFile(fileName, "Line1\nLine2\nLine3");
    FileReader fileReader(fileName);
    fileReader.open();
    ASSERT_EQ(fileReader.next(), "Line1");
    ASSERT_EQ(fileReader.next(), "Line2");
    ASSERT_EQ(fileReader.next(), "Line3");
    ASSERT_FALSE(fileReader.hasNext());
    fileReader.close();
}

TEST(FileReader, nextEmptyFile)
{
    std::string fileName = "test_next_empty.txt";
    createTempFile(fileName, "");
    FileReader fileReader(fileName);
    fileReader.open();
    ASSERT_FALSE(fileReader.hasNext());
    ASSERT_EQ(fileReader.next(), "");
    fileReader.close();
}

TEST(FileReader, rewind)
{
    std::string fileName = "test_to_beginning.txt";
    createTempFile(fileName, "Line1\nLine2\nLine3");
    FileReader fileReader(fileName);
    fileReader.open();
    ASSERT_EQ(fileReader.next(), "Line1");
    ASSERT_EQ(fileReader.next(), "Line2");
    fileReader.rewind();
    ASSERT_EQ(fileReader.next(), "Line1");
    ASSERT_EQ(fileReader.next(), "Line2");
    ASSERT_EQ(fileReader.next(), "Line3");
    ASSERT_FALSE(fileReader.hasNext());
    fileReader.close();
}
