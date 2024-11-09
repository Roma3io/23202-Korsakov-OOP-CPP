#include "Game.h"
#include "UniverseLoader.h"
#include "UniverseSaver.h"
#include <iostream>

Game::Game(const std::string &name, const std::string &rule, int width, int height)
    : universe(name, rule, width, height), commandHandler(universe) {}

Game::Game(const std::string &filename)
    : universe(UniverseLoader::loadFromFile(filename)), commandHandler(universe) {}

void Game::start()
{
    gameActive = true;
    universe.print();
    while (gameActive) {
        std::string command;
        std::getline(std::cin, command);
        if (command == "exit") {
            gameActive = false;
        } else if (command != "exit") {
            commandHandler.handleCommand(command);
        } else {
            std::cerr << "Unknown command: " << command << std::endl;
        }
    }
}

void Game::runOffline(int iterations, const std::string &outputFile)
{
    for (int i = 0; i < iterations; ++i) {
        universe.update();
    }
    UniverseSaver::saveUniverse(universe, outputFile);
}
