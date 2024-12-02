#ifndef UNIVERSELOADER_H
#define UNIVERSELOADER_H

#include "Universe.h"
#include <set>
#include <string>

class UniverseLoader
{
public:
    Universe loadFromFile(const std::string &filename);

private:
    void processName(const std::string &line, std::string &name);
    void processRule(const std::string &line, std::string &rule);
    void processSize(const std::string &line, int &width, int &height, Grid &grid);
    void processCells(std::set<std::pair<int, int>> &liveCells, const std::string &line, Grid &grid);
    void handleWarnings(const Grid &grid, bool hasName, bool hasRule);
};

#endif// UNIVERSELOADER_H
