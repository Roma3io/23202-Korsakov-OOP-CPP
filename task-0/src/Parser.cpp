#include "Parser.h"

std::string Parser::toLower(const std::string &str)
{
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), toLowerChar);
    return result;
}

std::list<std::string> Parser::splitIntoWords(const std::string &str)
{
    std::list<std::string> words;
    std::string word;
    for (char ch: str) {
        if (isDelim(ch)) {
            if (!word.empty()) {
                word = toLower(word);
                words.push_back(word);
                word.clear();
            }
        } else {
            word += ch;
        }
    }
    if (!word.empty()) {
        word = toLower(word);
        words.push_back(word);
    }
    return words;
}

bool Parser::isDelim(char ch)
{
    return !(('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ('0' <= ch && ch <= '9'));
}
