#include "Parser.h"

std::string Parser::toLower(const std::string &str)
{
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), toLowerChar);
    return result;
}

std::string Parser::removePunctuation(const std::string &str)
{
    std::string result = str;
    result.erase(std::remove_if(result.begin(), result.end(), ::ispunct), result.end());
    return result;
}

std::list<std::string> Parser::splitIntoWords(const std::string &str)
{
    std::list<std::string> words;
    std::istringstream iss(str);
    std::string word;
    while (iss >> word) {
        word = removePunctuation(word);
        word = toLower(word);
        if (!word.empty()) {
            words.push_back(word);
        }
    }
    return words;
}
