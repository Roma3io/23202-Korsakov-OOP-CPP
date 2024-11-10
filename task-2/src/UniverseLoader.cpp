#include "UniverseLoader.h"
#include "FileReader.h"
#include <iostream>
#include <set>
#include <sstream>
#include <windows.h>

Universe UniverseLoader::loadFromFile(const std::string &filename)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::vector<std::string> lines;
    FileReader::readFile(filename, lines);
    std::string name;
    std::string rule;
    int width = 0;
    int height = 0;
    Grid grid(0, 0);
    bool hasName = false;
    bool hasRule = false;
    bool hasSize = false;
    std::set<std::pair<int, int>> liveCells;
    for (const auto &line: lines) {
        if (line.substr(0, 3) == "#N ") {
            processName(line, name);
            hasName = true;
        } else if (line.substr(0, 3) == "#R ") {
            processRule(line, rule);
            hasRule = true;
        } else if (line.substr(0, 3) == "#S ") {
            processSize(line, width, height, grid);
            hasSize = true;
        } else if (line[0] != '#') {
            if (!hasSize)
                break;
            processCells(liveCells, line, grid);
        } else {
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            std::cerr << "Unknown line format: " << line << " To continue press enter" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            std::cin.get();
        }
    }
    if (!hasSize) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        std::cerr << "Error: No size specified in the file. To close this tab press enter" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        std::cin.get();
        exit(0);
    }
    handleWarnings(grid, hasName, hasRule);
    if (!hasName) {
        name = "My_universe";
    }
    if (!hasRule) {
        rule = "B3/S23";
    }
    Universe universe(name, rule, width, height);
    universe.grid = grid;
    universe.setRule(rule);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    return universe;
}

void UniverseLoader::processName(const std::string &line, std::string &name)
{
    name = line.substr(3);
}

void UniverseLoader::processRule(const std::string &line, std::string &rule)
{
    rule = line.substr(3);
}

void UniverseLoader::processSize(const std::string &line, int &width, int &height, Grid &grid)
{
    std::istringstream iss(line.substr(3));
    iss >> width >> height;
    grid = Grid(width, height);
}

void UniverseLoader::processCells(std::set<std::pair<int, int>> &liveCells, const std::string &line, Grid &grid)
{
    std::istringstream iss(line);
    int column, row;
    static int count = 3;
    while (iss >> row >> column) {
        count++;
        if (column >= 0 && column < grid.getWidth() && row >= 0 && row < grid.getHeight()) {
            auto cell = std::make_pair(row, column);
            if (liveCells.contains(cell)) {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                std::cerr << "Warning: Duplicate cell coordinates: (" << row << ", " << column << ") at line: " << count << ". To continue press enter" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                std::cin.get();
            } else {
                grid.setCell(row, column, true);
                liveCells.insert(cell);
            }
        } else {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            std::cerr << "Warning: Cell coordinates out of range: " << '(' << line << "); at line: " << count << ". To continue press enter" << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            std::cin.get();
        }
    }
}

void UniverseLoader::handleWarnings(const Grid &grid, bool hasName, bool hasRule)
{
    if (!hasName) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        std::cerr << "Warning: No name specified in the file." << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        std::cerr << "Universe will be named as: My_universe." << std::endl;
        std::cin.get();
    }
    if (!hasRule) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        std::cerr << "Warning: No rule specified in the file." << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        std::cerr << "Game will start with basic rules: B3/S23" << std::endl;
        std::cin.get();
    }
    if (grid.getWidth() == 0 || grid.getHeight() == 0) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        std::cerr << "Warning: Grid size is zero." << std::endl;
        std::cin.get();
    }
    if (grid.getWidth() > 75 | grid.getHeight() > 75) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        std::cerr << "Warning: Grid size is too big." << std::endl;
        std::cin.get();
    }
}
