#include "CommandHandler.h"
#include <iostream>
#include <sstream>

CommandHandler::CommandHandler(Universe &universe) : universe(universe) {}

void CommandHandler::handleCommand(const std::string &command)
{
    std::istringstream iss(command);
    std::string cmd;
    iss >> cmd;
    if (cmd == "tick") {
        int n = 1;
        iss >> n;
        universe.tick(n);
        universe.print();
    } else if (cmd == "dump") {
        std::string filename;
        iss >> filename;
        universe.saveToFile(filename);
    } else if (cmd == "exit") {
    } else if (cmd == "help") {
        printHelp();
    } else {
        std::cerr << "Unknown command: " << cmd << std::endl;
    }
}

void CommandHandler::printHelp()
{
    std::cout << "Available commands:" << std::endl;
    std::cout << "  tick <n> - calculate n iterations and print the result" << std::endl;
    std::cout << "  dump <filename> - save the universe to a file" << std::endl;
    std::cout << "  exit - exit the program" << std::endl;
    std::cout << "  help - print this help message" << std::endl;
}
