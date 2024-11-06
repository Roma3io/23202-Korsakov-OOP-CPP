#ifndef GRID_H
#define GRID_H

class Grid
{
public:
    Grid(int width, int height);
    ~Grid();
    bool getCell(int x, int y) const;
    void setCell(int x, int y, bool alive);
    int getWidth() const;
    int getHeight() const;
    bool** getCells() const;
    void update();
    void print() const;

private:
    int width;
    int height;
    bool **cells;
};

#endif// GRID_H
