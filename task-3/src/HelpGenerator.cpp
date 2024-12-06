#include "HelpGenerator.h"
#include <iostream>

std::string HelpGenerator::generateHelpMessage()
{
    std::string helpText =
            "Usage: sound_processor [-h] [-c config.txt output.wav input1.wav [input2.wav ...]]\n";
    helpText += "Supported converters:\n";
    std::vector<Converter *> converters = {
            new Muter(0, 0),
            new Mixer(std::vector<int16_t>(), 0),
            new VolumeConverter(100.0)
    };
    for (const auto &converter: converters) {
        helpText += converter->getName() + ": " + converter->getDescription() +
                "\n";
        helpText += "Parameters: " + converter->getParameters() + "\n";
    }
    for (auto &converter: converters) { delete converter; }
    return helpText;
}
