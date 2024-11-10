#ifndef UNIVERSELOADER_H
#define UNIVERSELOADER_H

#include "Universe.h"
#include <set>
#include <string>

class UniverseLoader
{
public:
    static Universe loadFromFile(const std::string &filename);

private:
    static void processName(const std::string &line, std::string &name);
    static void processRule(const std::string &line, std::string &rule);
    static void processSize(const std::string &line, int &width, int &height, Grid &grid);
    static void processCells(std::set<std::pair<int, int>> &liveCells, const std::string &line, Grid &grid);
    static void handleWarnings(const Grid &grid, bool hasName, bool hasRule);
};

#endif// UNIVERSELOADER_H
