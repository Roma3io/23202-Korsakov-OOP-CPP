#include "UniverseSaver.h"
#include "FileWriter.h"
#include <sstream>
#include <vector>

void UniverseSaver::saveUniverse(const Universe &universe, const std::string &filename)
{
    std::vector<std::string> outputLines;
    UniverseSaver universeSaver;
    universeSaver.addName(universe.name, outputLines);
    universeSaver.addRule(universe.rule, outputLines);
    universeSaver.addSize(universe.grid, outputLines);
    universeSaver.addCells(universe.grid, outputLines);
    FileWriter fileWriter;
    fileWriter.writeFile(filename, outputLines);
}

void UniverseSaver::addName(const std::string &name, std::vector<std::string> &outputLines)
{
    outputLines.push_back("#N " + name);
}

void UniverseSaver::addRule(const std::string &rule, std::vector<std::string> &outputLines)
{
    outputLines.push_back("#R " + rule);
}

void UniverseSaver::addSize(const Grid &grid, std::vector<std::string> &outputLines)
{
    outputLines.push_back("#S " + std::to_string(grid.getWidth()) + " " + std::to_string(grid.getHeight()));
}

void UniverseSaver::addCells(const Grid &grid, std::vector<std::string> &outputLines)
{
    for (int row = 0; row < grid.getHeight(); ++row) {
        for (int column = 0; column < grid.getWidth(); ++column) {
            if (grid.getCell(row, column)) {
                outputLines.push_back(std::to_string(row) + " " + std::to_string(column));
            }
        }
    }
}
