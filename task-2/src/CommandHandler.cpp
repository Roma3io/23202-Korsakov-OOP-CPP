#include "CommandHandler.h"
#include "UniverseSaver.h"

#include <chrono>
#include <conio.h>
#include <iostream>
#include <thread>

CommandHandler::CommandHandler(Universe &universe) : universe(universe) {}

TickCommandHandler::TickCommandHandler(Universe &universe, int iteration)
    : CommandHandler(universe), iteration(iteration) {}

void TickCommandHandler::handle()
{
    for (int i = 0; i < iteration; i++) {
        universe.update();
    }
    universe.print();
    std::cout << "Iteration: " << universe.getGeneration() << std::endl;
    std::cout << "Name: " << universe.getName() << std::endl;
    std::cout << "Rule: " << universe.getRule() << std::endl;
    std::cout << std::endl;
}

AutoCommandHandler::AutoCommandHandler(Universe &universe)
    : CommandHandler(universe) {}

void AutoCommandHandler::handle()
{
    std::cout << "To start the universe's life, press any key..." << std::endl;
    _getch();
    while (true) {
        universe.update();
        universe.print();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if (_kbhit()) {
            break;
        }
    }
    _getch();
    std::cout << "Simulation stopped." << std::endl;
    std::cout << "Iteration: " << universe.getGeneration() << std::endl;
    std::cout << "Name: " << universe.getName() << std::endl;
    std::cout << "Rule: " << universe.getRule() << std::endl;
}

DumpCommandHandler::DumpCommandHandler(Universe &universe, const std::string &filename)
    : CommandHandler(universe), filename(filename) {}

void DumpCommandHandler::handle()
{
    UniverseSaver universeSaver;
    universeSaver.saveUniverse(universe, filename);
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
