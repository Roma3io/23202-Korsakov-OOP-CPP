#include "SoundProcessor.h"
#include "ConsoleParser.h"
#include "HelpGenerator.h"
#include <iostream>

int main(int argc, char *argv[])
{
    try {
        ConsoleParser consoleParser(argc, argv);
        if (consoleParser.isHelpRequested()) {
            HelpGenerator helpGenerator;
            std::cout << helpGenerator.generateHelpMessage() << std::endl;
            return 0;
        }
        std::string configFile = consoleParser.getConfigFile();
        std::string outputFile = consoleParser.getOutputFile();
        std::vector<std::string> inputFiles = consoleParser.getInputFiles();
        SoundProcessor soundProcessor(configFile, outputFile, inputFiles);
        soundProcessor.process();
    } catch (const ExceptionHandler &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 2;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 3;
    }
    return 0;
}
