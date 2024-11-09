#ifndef GRID_H
#define GRID_H

#include <vector>

class Grid
{
public:
    Grid();
    Grid(int width, int height);
    bool getCell(int row, int column) const;
    void setCell(int row, int column, bool alive);
    int getWidth() const;
    int getHeight() const;
    const std::vector<std::vector<bool>>& getCells() const;

private:
    int width;
    int height;
    std::vector<std::vector<bool>> cells;
};

#endif // GRID_H
