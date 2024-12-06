#include "SoundProcessor.h"
#include "ConsoleParser.h"
#include "HelpGenerator.h"
#include <iostream>

int main(int argc, char *argv[])
{
    ConsoleParser consoleParser(argc, argv);
    if (consoleParser.isHelpRequested()) {
        HelpGenerator helpGenerator;
        std::cout << helpGenerator.generateHelpMessage() << std::endl;
        return 0;
    }
    SoundProcessor soundProcessor(consoleParser.getConfigFile(),
                                  consoleParser.getOutputFile(),
                                  consoleParser.getInputFiles());
    soundProcessor.process();
    return 0;
}
