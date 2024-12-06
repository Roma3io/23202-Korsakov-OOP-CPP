#include "Grid.h"
#include <stdexcept>

Grid::Grid() : width(0), height(0) {}

Grid::Grid(int width, int height) : width(width), height(height), cells(height, std::vector<bool>(width, false)) {}

void Grid::setCell(const int row, const int column, bool alive)
{
    cells[row][column] = alive;
}

int Grid::getHeight() const
{
    return height;
}

int Grid::getWidth() const
{
    return width;
}

const std::vector<std::vector<bool>> &Grid::getCells() const
{
    return cells;
}

bool Grid::getCell(const int row, const int column) const
{
    return cells[row][column];
}
