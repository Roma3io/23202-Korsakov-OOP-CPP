#ifndef STATISTIC_H
#define STATISTIC_H

#include "FileReader.h"
#include "Parser.h"
#include <algorithm>
#include <list>
#include <map>
#include <string>
#include <vector>

class Statistic
{
private:
    std::map<std::string, int> wordsFrequency;
    int wordsAmount = 0;
    static bool frequencyComparator(const std::pair<std::string, int> &a,
                                    const std::pair<std::string, int> &b)
    {
        return a.second > b.second;
    }

public:
    void addWord(const std::string &word);
    std::vector<std::pair<std::string, int>> getStatistic() const;
    int getWordsAmount() const;
};

#endif
