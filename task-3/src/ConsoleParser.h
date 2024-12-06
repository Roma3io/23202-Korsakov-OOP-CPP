#ifndef CONSOLEPARSER_H
#define CONSOLEPARSER_H

#include <string>
#include <vector>
#include <iostream>

class ConsoleParser {
public:
    ConsoleParser(int argc, char *argv[]);
    std::string getConfigFile() const;
    std::string getOutputFile() const;
    std::vector<std::string> getInputFiles() const;
    bool isHelpRequested() const;

private:
    std::string configFile;
    std::string outputFile;
    std::vector<std::string> inputFiles;
    bool helpRequested = false;
    void parseArguments(int argc, char *argv[]);
    void printHelpMessage() const;
};

#endif // CONSOLEPARSER_H
