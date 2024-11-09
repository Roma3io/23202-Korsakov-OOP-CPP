#include "CommandHandler.h"
#include "UniverseSaver.h"
#include <iostream>
#include <sstream>

CommandHandler::CommandHandler(Universe &universe) : universe(universe) {}

void CommandHandler::handleCommand(const std::string &command)
{
    std::istringstream iss(command);
    std::string cmd;
    iss >> cmd;
    if (cmd == "tick") {
        handleTick(command);
    } else if (cmd == "auto") {
        handleAuto();
    } else if (cmd == "dump") {
        handleDump(command);
    } else if (cmd == "help") {
        printHelp();
    } else {
        std::cerr << "Unknown command: " << cmd << std::endl;
    }
}

void CommandHandler::handleTick(const std::string &command) const
{
    std::istringstream iss(command);
    std::string cmd;
    int n = 1;
    iss >> cmd >> n;
    universe.tick(n);
}

void CommandHandler::handleAuto() const
{
    universe.autoRun();
}

void CommandHandler::handleDump(const std::string &command) const
{
    std::istringstream iss(command);
    std::string cmd, filename;
    iss >> cmd >> filename;
    UniverseSaver::saveUniverse(universe, filename);
}

void CommandHandler::printHelp()
{
    std::cout << "Available commands:" << std::endl;
    std::cout << "  tick <n> - calculate n iterations and print the result" << std::endl;
    std::cout << "  dump <filename> - save the universe to a file" << std::endl;
    std::cout << "  exit - exit the program" << std::endl;
    std::cout << "  auto - start simulating life" << std::endl;
    std::cout << "  help - print this help message" << std::endl;
}
