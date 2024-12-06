#ifndef UNIVERSESAVER_H
#define UNIVERSESAVER_H

#include "Universe.h"
#include <string>

class UniverseSaver
{
public:
    void saveUniverse(const Universe &universe, const std::string &filename);

private:
    void addName(const std::string &name, std::vector<std::string> &outputLines);
    void addRule(const std::string &rule, std::vector<std::string> &outputLines);
    void addSize(const Grid &grid, std::vector<std::string> &outputLines);
    void addCells(const Grid &grid, std::vector<std::string> &outputLines);
};

#endif// UNIVERSESAVER_H
