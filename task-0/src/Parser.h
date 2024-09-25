#ifndef PARSER_H
#define PARSER_H

#include <algorithm>
#include <cctype>
#include <list>
#include <sstream>
#include <string>

class Parser
{
private:
    static unsigned char toLowerChar(unsigned char c) { return tolower(c); }
    static std::string toLower(const std::string &str);
    static std::string removePunctuation(const std::string &str);

public:
    static std::list<std::string> splitIntoWords(const std::string &str);
};

#endif// PARSER_H
