#include "Game.h"
#include <iostream>

Game::Game(const std::string &name, const std::string &rule, int width, int height)
    : universe(name, rule, width, height), commandHandler(universe) {}

Game::Game(const std::string &filename)
    : universe(filename), commandHandler(universe) {}

void Game::start()
{
    bool gameActive = true;
    universe.print();
    while (gameActive) {
        std::string command;
        std::cin >> command;
        if (command == "tick") {
            int n = 1;
            std::cin >> n;
            universe.tick(n);
        } else if (command == "dump") {
            std::string filename;
            std::cin >> filename;
            universe.saveToFile(filename);
        } else if (command == "exit") {
            gameActive = false;
        } else if (command == "help") {
            commandHandler.printHelp();
        } else {
            std::cerr << "Unknown command: " << command << std::endl;
        }
    }
}
