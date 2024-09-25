#ifndef STATISTIC_H
#define STATISTIC_H

#include <string>
#include <map>
#include <vector>
#include <list>
#include <algorithm>
#include "FileReader.h"
#include "Parser.h"

class Statistic {
private:
    std::map<std::string, int> wordsFrequency;
    int wordsAmount = 0;
    static bool frequencyComparator(const std::pair<std::string, int> &a,
                                    const std::pair<std::string, int> &b) {
        return a.second > b.second;
    }

public:
    void addWord(const std::string &word);
    void addWordsFromString(const std::string &str);
    void getWordsFrequency(FileReader &fileReader);
    std::vector<std::pair<std::string, int>> getSortedWordsFrequency() const;
    int getWordsAmount() const;
};

#endif
