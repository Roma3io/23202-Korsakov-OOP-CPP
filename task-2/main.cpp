#include "Game.h"
#include <iostream>
#include <sstream>
#include <string>

void printHelp()
{
    std::cout << "Usage:\n"
              << "  game_of_life [options]\n"
              << "Options:\n"
              << "  -i <iterations> | --iterations=<iterations>  Number of iterations\n"
              << "  -o <output> | --output=<output>              Output file\n"
              << "  -f <file> | --file=<file>                    Input file\n"
              << "  -h | --help                                  Print this help message\n";
}

int main(int argc, char *argv[])
{
    std::cout << "Game of Life\n\n"
              << "The Game of Life is a cellular automaton devised by the British mathematician John Horton Conway.\n"
              << "The game is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input.\n"
              << "The universe of the Game of Life is an infinite two-dimensional orthogonal grid of square cells,\n"
              << "each of which is in one of two possible states, live or dead.\n"
              << "Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or diagonally adjacent.\n"
                 ""
              << "At each step in time, the following transitions occur:\n"
              << "1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.\n"
              << "2. Any live cell with two or three live neighbours lives on to the next generation.\n"
              << "3. Any live cell with more than three live neighbours dies, as if by overpopulation.\n"
              << "4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.\n"
              << "\n"
              << "Press any key to start the game...\n";
    std::cin.get();
    if (argc == 1) {
        Game game("Random Universe", "B3/S23", 10, 10);
        game.start();
    } else if (argc == 2) {
        Game game(argv[1]);
        game.start();
    } else if (argc == 4) {
        std::string inputFilename = argv[1];
        int iterations;
        std::istringstream(argv[2]) >> iterations;
        std::string outputFilename = argv[3];
        Universe universe(inputFilename);
        universe.tick(iterations);
        universe.saveToFile(outputFilename);
    } else {
        std::cerr << "Invalid number of arguments" << std::endl;
        printHelp();
        return 1;
    }
    return 0;
}
