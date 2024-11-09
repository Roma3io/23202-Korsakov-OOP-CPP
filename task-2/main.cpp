#include "Game.h"
#include <iostream>
#include <sstream>
#include <string>

void printHelp()
{
    std::cout << "Options:\n"
              << "  -i <iterations> | --iterations=<iterations>  Number of iterations\n"
              << "  -o <output> | --output=<output>              Output file\n"
              << "  -h | --help                                  Print this help message\n";
}

int main(int argc, char *argv[])
{
    if (argc == 1) {
        Game game("Random Universe", "B3/S23", 20, 20);
        game.start();
    } else if (argc == 2) {
        Game game(argv[1]);
        game.start();
    } else if (argc == 6) {
        std::string inputFile, outputFile;
        int iterations = 0;
        inputFile = argv[1];
        for (int i = 2; i < argc; i++) {
            std::string arg = argv[i];
            if (arg == "-i" || arg.substr(0, 13) == "--iterations=") {
                if (arg.substr(0, 13) == "--iterations=") {
                    iterations = std::stoi(arg.substr(13));
                } else {
                    iterations = std::stoi(argv[++i]);
                }
            } else if (arg == "-o" || arg.substr(0, 9) == "--output=") {
                if (arg.substr(0, 9) == "--output=") {
                    outputFile = arg.substr(9);
                } else {
                    outputFile = argv[++i];
                }
            } else {
                std::cerr << "Invalid argument: " << arg << std::endl;
                printHelp();
                return 1;
            }
        }
        if (inputFile.empty() || outputFile.empty() || iterations <= 0) {
            std::cerr << "Invalid arguments" << std::endl;
            printHelp();
            return 1;
        }
        Game game(inputFile);
        game.runOffline(iterations, outputFile);
    } else {
        std::cerr << "Invalid number of arguments" << std::endl;
        printHelp();
        return 1;
    }
}
