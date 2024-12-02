#include "Universe.h"
#include "Windows.h"
#include <algorithm>
#include <chrono>
#include <conio.h>
#include <iostream>
#include <sstream>
#include <thread>
#include <vector>

Universe::Universe() : generation(0)
{
    grid = Grid();
}

Universe::Universe(const std::string &name, const std::string &rule, int width, int height)
    : name(name), rule(rule), grid(width, height), generation(0)
{
    std::srand(std::time(0));
    for (int row = 0; row < grid.getHeight(); row++) {
        for (int column = 0; column < grid.getWidth(); column++) {
            grid.setCell(row, column, std::rand() % 2 == 0);
        }
    }
    setRule(rule);
}

void Universe::print() const
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    std::cout << "+";
    for (int column = 0; column < grid.getWidth(); column++) {
        std::cout << "--";
    }
    std::cout << "+" << std::endl;
    for (int row = 0; row < grid.getHeight(); row++) {
        std::cout << "|";
        for (int column = 0; column < grid.getWidth(); column++) {
            if (grid.getCell(row, column)) {
                SetConsoleTextAttribute(hConsole, 0 | (0 << 4));
            } else {
                SetConsoleTextAttribute(hConsole, 15 | (15 << 4));
            }
            std::cout << "  ";
        }
        SetConsoleTextAttribute(hConsole, 7 | (0 << 4));
        std::cout << "|" << std::endl;
    }
    std::cout << "+";
    for (int column = 0; column < grid.getWidth(); column++) {
        std::cout << "--";
    }
    std::cout << "+" << std::endl;
}

void Universe::update()
{
    bool **newCells = new bool *[grid.getHeight()];
    for (int row = 0; row < grid.getHeight(); row++) {
        newCells[row] = new bool[grid.getWidth()];
    }
    for (int row = 0; row < grid.getHeight(); row++) {
        for (int column = 0; column < grid.getWidth(); column++) {
            int neighbors = countNeighbors(row, column);
            if (grid.getCell(row, column)) {
                newCells[row][column] = std::find(survivalRule.begin(), survivalRule.end(), neighbors) != survivalRule.end();
            } else {
                newCells[row][column] = std::find(birthRule.begin(), birthRule.end(), neighbors) != birthRule.end();
            }
        }
    }
    for (int row = 0; row < grid.getHeight(); row++) {
        for (int column = 0; column < grid.getWidth(); column++) {
            grid.setCell(row, column, newCells[row][column]);
        }
    }
    for (int row = 0; row < grid.getHeight(); row++) {
        delete[] newCells[row];
    }
    generation++;
    delete[] newCells;
}

int Universe::countNeighbors(int row, int column) const
{
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            int nColumn = (column + i + grid.getWidth()) % grid.getWidth();
            int nRow = (row + j + grid.getHeight()) % grid.getHeight();
            if (nColumn >= 0 && nColumn < grid.getWidth() && nRow >= 0 && nRow < grid.getHeight()) {
                if (grid.getCell(nRow, nColumn)) {
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

int Universe::getGeneration() const
{
    return generation;
}

std::string Universe::getName() const
{
    return name;
}

std::string Universe::getRule() const
{
    return rule;
}

