#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

template<typename T>
T ParseToken(const std::string &token, int line, int column)
{
    std::stringstream ss(token);
    T value;
    ss >> value;
    if (ss.fail() || !ss.eof()) {
        throw std::runtime_error("invalid data type at line " +
                                 std::to_string(line) + ", column " +
                                 std::to_string(column));
    }
    return value;
}

template<>
std::string ParseToken<std::string>(const std::string &token, int line,
                                    int column)
{
    return token;
}

template<typename... Args>
class CSVParser
{
    std::istream &is;
    int skipLines;
    char rowDelimiter;
    char colDelimiter;
    char escapeChar;
    int currentLine;
    bool isEOF;

public:
    CSVParser(std::istream &is, int skipLines = 0, char rowDelimiter = '\n',
              char colDelimiter = ',', char escapeChar = '"')
        : is(is), skipLines(skipLines), rowDelimiter(rowDelimiter),
          colDelimiter(colDelimiter), escapeChar(escapeChar), currentLine(0),
          isEOF(false)
    {
        for (int i = 0; i < skipLines; i++) {
            std::string line;
            std::getline(is, line);
            currentLine++;
        }
    }

    class Iterator
        : public std::iterator<std::input_iterator_tag, std::tuple<Args...>>
    {
        CSVParser &parser;
        bool end;
        std::tuple<Args...> current;

    public:
        Iterator(CSVParser &parser, bool end = false) : parser(parser), end(end)
        {
            if (!end) { ++(*this); }
        }
        Iterator &operator++()
        {
            if (!end) {
                if (parser.is.eof()) { parser.isEOF = true; }
                if (!parser.isEOF) {
                    current = parser.getTuple();
                } else {
                    parser.isEOF = true;
                    end = true;
                }
            }
            return *this;
        }

        std::tuple<Args...> &operator*() { return current; }

        bool operator==(const Iterator &other) const
        {
            return end == other.end;
        }

        bool operator!=(const Iterator &other) const
        {
            return !(*this == other);
        }
    };
    Iterator begin() { return Iterator(*this); }

    Iterator end() { return Iterator(*this, true); }

    std::tuple<Args...> getTuple()
    {
        std::string line;
        if (!std::getline(is, line)) {
            isEOF = true;
            throw std::runtime_error("unexpected end of file");
        }
        std::vector<std::string> tokens;
        bool inEscapeChar = false;
        std::string currentToken;
        int columnCount = 1;
        currentLine++;
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == escapeChar) {
                inEscapeChar = !inEscapeChar;
            } else if (line[i] == colDelimiter && !inEscapeChar) {
                tokens.push_back(currentToken);
                currentToken.clear();
                columnCount++;
                while (line[i + 1] == ' ') { i++; }
            } else {
                currentToken += line[i];
            }
        }
        tokens.push_back(currentToken);
        if (tokens.size() != sizeof...(Args)) {
            throw std::runtime_error("incorrect number of columns at line: " +
                                     std::to_string(currentLine));
        }
        return parseTokens<Args...>(tokens, std::index_sequence_for<Args...>{});
    }

    template<typename... T, std::size_t... I>
    std::tuple<Args...> parseTokens(const std::vector<std::string> &tokens,
                                    std::index_sequence<I...>)
    {
        return std::make_tuple(ParseToken<typename std::tuple_element<
                                       I, std::tuple<Args...>>::type>(
                tokens[I], currentLine, I + 1)...);
    }
};

#endif// CSVPARSER_H
