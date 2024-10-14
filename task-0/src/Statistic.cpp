#include "Statistic.h"

void Statistic::addWord(const std::string &word)
{
    wordsAmount++;
    wordsFrequency[word]++;
}

std::vector<std::pair<std::string, int>> Statistic::getStatistic() const
{
    std::vector<std::pair<std::string, int>> sortedWords(wordsFrequency.begin(),
                                                         wordsFrequency.end());
    std::sort(sortedWords.begin(), sortedWords.end(), frequencyComparator);
    return sortedWords;
}

int Statistic::getWordsAmount() const
{
    return wordsAmount;
}
