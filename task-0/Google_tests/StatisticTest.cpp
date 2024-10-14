#include "../src/Statistic.h"
#include "gtest/gtest.h"

TEST(Statistic, addWord)
{
    Statistic statistic;
    statistic.addWord("word");
    ASSERT_EQ(statistic.getWordsAmount(), 1);
}

TEST(Statistic, addMultipleSameWords)
{
    Statistic statistic;
    statistic.addWord("word");
    statistic.addWord("word");
    statistic.addWord("word");
    ASSERT_EQ(statistic.getWordsAmount(), 3);
}

TEST(Statistic, getStatistic)
{
    Statistic statistic;
    statistic.addWord("word");
    statistic.addWord("word");
    statistic.addWord("another");
    statistic.addWord("word");
    statistic.addWord("another");
    statistic.addWord("test");
    std::vector<std::pair<std::string, int>> sortedWords = statistic.getStatistic();
    ASSERT_EQ(sortedWords.size(), 3);
    ASSERT_EQ(sortedWords[0].first, "word");
    ASSERT_EQ(sortedWords[0].second, 3);
    ASSERT_EQ(sortedWords[1].first, "another");
    ASSERT_EQ(sortedWords[1].second, 2);
    ASSERT_EQ(sortedWords[2].first, "test");
    ASSERT_EQ(sortedWords[2].second, 1);
}
