#include "CommandHandler.h"
#include "UniverseSaver.h"
#include <iostream>
#include <sstream>

CommandHandler::CommandHandler(Universe &universe) : universe(universe) {}

TickCommandHandler::TickCommandHandler(Universe &universe, int n)
    : CommandHandler(universe), n(n) {}

void TickCommandHandler::handle()
{
    universe.tick(n);
}

AutoCommandHandler::AutoCommandHandler(Universe &universe)
    : CommandHandler(universe) {}

void AutoCommandHandler::handle()
{
    universe.autoRun();
}

DumpCommandHandler::DumpCommandHandler(Universe &universe, const std::string &filename)
    : CommandHandler(universe), filename(filename) {}

void DumpCommandHandler::handle()
{
    UniverseSaver::saveUniverse(universe, filename);
}

HelpCommandHandler::HelpCommandHandler(Universe &universe)
    : CommandHandler(universe) {}

void HelpCommandHandler::handle()
{
    std::cout << "Available commands:" << std::endl;
    std::cout << "  tick <n> - calculate n iterations and print the result" << std::endl;
    std::cout << "  dump <filename> - save the universe to a file" << std::endl;
    std::cout << "  exit - exit the program" << std::endl;
    std::cout << "  auto - start simulating life" << std::endl;
    std::cout << "  help - print this help message" << std::endl;
}

ExitCommandHandler::ExitCommandHandler(Universe &universe, bool &gameActive)
    : CommandHandler(universe), gameActive(gameActive) {}

void ExitCommandHandler::handle()
{
    std::cout << "Exiting the program." << std::endl;
    gameActive = false;
}
