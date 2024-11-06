#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <string>
#include <vector>
#include "Grid.h"

class Universe {
public:
    Universe(const std::string& name, const std::string& rule, int width, int height);
    Universe(const std::string& filename);
    void print() const;
    void tick(int n = 1);
    void saveToFile(const std::string& filename) const;

private:
    std::string name;
    std::string rule;
    Grid grid;
    std::vector<int> birthRule;
    std::vector<int> survivalRule;
    void parseFile(const std::string& filename);
    void update();
    int countNeighbors(int x, int y) const;
    void setRule(const std::string& rule);
};

#endif // UNIVERSE_H
