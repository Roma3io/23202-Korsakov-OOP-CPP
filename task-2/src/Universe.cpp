#include "Universe.h"
#include "FileReader.h"
#include "FileWriter.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>
#include <vector>

Universe::Universe(const std::string &name, const std::string &rule, int width, int height)
    : name(name), rule(rule), grid(width, height)
{
    std::srand(std::time(0));
    for (int y = 0; y < grid.getHeight(); y++) {
        for (int x = 0; x < grid.getWidth(); x++) {
            grid.setCell(x, y, std::rand() % 2 == 0);
        }
    }
    setRule(rule);
}

Universe::Universe(const std::string &filename) : grid(0, 0)
{
    parseFile(filename);
}

void Universe::print() const
{
    for (int y = 0; y < grid.getHeight(); y++) {
        for (int x = 0; x < grid.getWidth(); x++) {
            std::cout << (grid.getCell(x, y) ? '*' : ' ');
        }
        std::cout << std::endl;
    }
}

void Universe::tick(int n)
{
    for (int i = 0; i < n; i++) {
        update();
        std::cout << "Iteration: " << i + 1 << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Rule: " << rule << std::endl;
        print();
        std::cout << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void Universe::saveToFile(const std::string &filename) const
{
    std::vector<std::string> outputLines;
    outputLines.push_back("#N " + name);
    outputLines.push_back("#R " + rule);
    outputLines.push_back("#P " + std::to_string(grid.getWidth()) + " " + std::to_string(grid.getHeight()));
    for (int y = 0; y < grid.getHeight(); ++y) {
        for (int x = 0; x < grid.getWidth(); ++x) {
            if (grid.getCell(x, y)) {
                outputLines.push_back(std::to_string(x) + " " + std::to_string(y));
            }
        }
    }
    FileWriter::writeFile(filename, outputLines);
}

void Universe::parseFile(const std::string &filename)
{
    std::vector<std::string> lines;
    FileReader::readFile(filename, lines);
    for (const auto &line: lines) {
        if (line.substr(0, 3) == "#N ") {
            name = line.substr(3);
        } else if (line.substr(0, 3) == "#R ") {
            rule = line.substr(3);
        } else if (line.substr(0, 2) == "#P") {
            std::istringstream iss(line.substr(2));
            int width, height;
            iss >> width >> height;
            grid = Grid(width, height);
        } else if (line[0] != '#') {
            std::istringstream iss(line);
            int x, y;
            while (iss >> x >> y) {
                if (x >= 0 && x < grid.getWidth() && y >= 0 && y < grid.getHeight()) {
                    grid.setCell(x, y, true);
                }
            }
        }
    }
    setRule(rule);
}

void Universe::update()
{
    bool **newCells = new bool *[grid.getHeight()];
    for (int i = 0; i < grid.getHeight(); i++) {
        newCells[i] = new bool[grid.getWidth()];
    }
    for (int i = 0; i < grid.getHeight(); i++) {
        for (int j = 0; j < grid.getWidth(); j++) {
            int neighbors = countNeighbors(i, j);
            if (grid.getCell(i, j)) {
                newCells[i][j] = std::find(survivalRule.begin(), survivalRule.end(), neighbors) != survivalRule.end();
            } else {
                newCells[i][j] = std::find(birthRule.begin(), birthRule.end(), neighbors) != birthRule.end();
            }
        }
    }
    for (int i = 0; i < grid.getHeight(); i++) {
        for (int j = 0; j < grid.getWidth(); j++) {
            grid.setCell(i, j, newCells[i][j]);
        }
    }
    for (int i = 0; i < grid.getWidth(); i++) {
        delete[] newCells[i];
    }
    delete[] newCells;
}

int Universe::countNeighbors(int x, int y) const
{
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            int nx = (x + i + grid.getWidth()) % grid.getWidth();
            int ny = (y + j + grid.getHeight()) % grid.getHeight();
            if (nx >= 0 && nx < grid.getWidth() && ny >= 0 && ny < grid.getHeight()) {
                if (grid.getCell(nx, ny)) {
                    count++;
                }
            }
        }
    }
    return count;
}

void Universe::setRule(const std::string &rule)
{
    std::istringstream iss(rule);
    std::string token;
    while (std::getline(iss, token, '/')) {
        if (token[0] == 'B') {
            for (char ch: token.substr(1)) {
                birthRule.push_back(ch - '0');
            }
        } else if (token[0] == 'S') {
            for (char ch: token.substr(1)) {
                survivalRule.push_back(ch - '0');
            }
        }
    }
}
