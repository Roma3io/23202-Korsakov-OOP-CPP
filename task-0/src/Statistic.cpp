#include "Statistic.h"

void Statistic::addWord(const std::string &word) {
    wordsAmount++;
    wordsFrequency[word]++;
}

void Statistic::addWordsFromString(const std::string &str) {
    std::list<std::string> words = Parser::splitIntoWords(str);
    for (const std::string &word : words) {
        addWord(word);
    }
}

void Statistic::getWordsFrequency(FileReader &fileReader) {
    while (fileReader.hasNext()) {
        std::string line = fileReader.next();
        addWordsFromString(line);
    }
}

std::vector<std::pair<std::string, int>> Statistic::getSortedWordsFrequency() const {
    std::vector<std::pair<std::string, int>> sortedWords(wordsFrequency.begin(),
                                                         wordsFrequency.end());
    std::sort(sortedWords.begin(), sortedWords.end(), frequencyComparator);
    return sortedWords;
}

int Statistic::getWordsAmount() const {
    return wordsAmount;
}
