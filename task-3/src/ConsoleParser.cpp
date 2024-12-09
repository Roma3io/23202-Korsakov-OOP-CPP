#include "ConsoleParser.h"
#include "HelpGenerator.h"
#include "ExceptionHandler.h"

ConsoleParser::ConsoleParser(int argc, char *argv[])
{
    parseArguments(argc, argv);
}

void ConsoleParser::parseArguments(int argc, char *argv[])
{
    if (argc < 2) {
        printHelpMessage();
        exit(1);
    }
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-h") {
            helpRequested = true;
            return;
        } else if (arg == "-c") {
            if (i + 3 < argc) {
                configFile = argv[++i];
                outputFile = argv[++i];
                for (int j = i + 1; j < argc; ++j) {
                    inputFiles.push_back(argv[j]);
                }
            } else { throw InvalidFormatException("Error: Invalid arguments"); }
        }
    }
}

void ConsoleParser::printHelpMessage() const
{
    HelpGenerator helpGenerator;
    std::cout << helpGenerator.generateHelpMessage() << std::endl;
}

std::string ConsoleParser::getConfigFile() const { return configFile; }

std::string ConsoleParser::getOutputFile() const { return outputFile; }

std::vector<std::string> ConsoleParser::getInputFiles() const
{
    return inputFiles;
}

bool ConsoleParser::isHelpRequested() const { return helpRequested; }
