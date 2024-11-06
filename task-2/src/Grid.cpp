#include "Grid.h"
#include <stdexcept>

Grid::Grid(int width, int height) : width(width), height(height)
{
    cells = new bool*[height];
    for (int i = 0; i < height; i++) {
        cells[i] = new bool[width];
        for (int j = 0; j < width; j++) {
            cells[i][j] = false;
        }
    }
}


Grid::~Grid()
{
    for (int i = 0; i < height; i++) {
        delete[] cells[i];
    }
    delete[] cells;
}

void Grid::setCell(int x, int y, bool alive)
{
    if (x >= width || y >= height) {
        throw std::out_of_range("Index out of range");
    }
    cells[y][x] = alive;
}

int Grid::getHeight() const
{
    return height;
}

int Grid::getWidth() const
{
    return width;
}

bool **Grid::getCells() const
{
    if (cells) {
        return cells;
    }
    throw std::runtime_error("Grid is not initialized");
}

bool Grid::getCell(int x, int y) const
{
    if (x >= width || y >= height) {
        throw std::out_of_range("Index out of range");
    }
        return cells[y][x];
}
