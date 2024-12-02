#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "Grid.h"
#include <string>
#include <vector>

class Universe
{
public:
    Universe();
    Universe(const std::string &name, const std::string &rule, int width, int height);
    void print() const;
    void update();
    int getGeneration() const;
    std::string getName() const;
    std::string getRule() const;

private:
    std::string name;
    std::string rule;
    Grid grid;
    std::vector<int> birthRule;
    std::vector<int> survivalRule;
    int generation;
    int countNeighbors(int row, int column) const;
    void setRule(const std::string &rule);
    friend class UniverseLoader;
    friend class UniverseSaver;
    friend class UniverseTest;
};

#endif// UNIVERSE_H
