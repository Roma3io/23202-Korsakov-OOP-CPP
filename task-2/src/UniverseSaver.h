#ifndef UNIVERSESAVER_H
#define UNIVERSESAVER_H

#include <string>
#include "Universe.h"

class UniverseSaver {
public:
    static void saveUniverse(const Universe &universe, const std::string &filename);

private:
    static void addName(const std::string &name, std::vector<std::string> &outputLines);
    static void addRule(const std::string &rule, std::vector<std::string> &outputLines);
    static void addSize(const Grid &grid, std::vector<std::string> &outputLines);
    static void addCells(const Grid &grid, std::vector<std::string> &outputLines);
};

#endif // UNIVERSESAVER_H
