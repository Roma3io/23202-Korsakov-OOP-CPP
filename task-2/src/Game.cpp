#include "Game.h"
#include "UniverseLoader.h"
#include "UniverseSaver.h"
#include <iostream>
#include <memory>
#include <sstream>

Game::Game(const std::string &name, const std::string &rule, int width, int height)
    : universe(name, rule, width, height) {}

Game::Game(const std::string &filename)
{
    UniverseLoader universeLoader;
    universe = universeLoader.loadFromFile(filename);
}

void Game::start()
{
    gameActive = true;
    universe.print();
    while (gameActive) {
        std::string command;
        std::getline(std::cin, command);
        CommandHandler *handler = createCommandHandler(command);
        if (handler) {
            handler->handle();
            delete handler;
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
    UniverseSaver universeSaver;
    universeSaver.saveUniverse(universe, outputFile);
}

CommandHandler *Game::createCommandHandler(const std::string &command)
{
    std::istringstream iss(command);
    std::string cmd;
    iss >> cmd;
    if (cmd == "tick") {
        int n = 1;
        iss >> n;
        return new TickCommandHandler(universe, n);
    }
    if (cmd == "auto") {
        return new AutoCommandHandler(universe);
    }
    if (cmd == "dump") {
        std::string filename;
        iss >> filename;
        return new DumpCommandHandler(universe, filename);
    }
    if (cmd == "help") {
        return new HelpCommandHandler(universe);
    }
    if (cmd == "exit") {
        return new ExitCommandHandler(universe, gameActive);
    }
    return nullptr;
}
