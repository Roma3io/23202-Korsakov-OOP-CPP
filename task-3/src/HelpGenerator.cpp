#include "HelpGenerator.h"
#include <iostream>

std::string HelpGenerator::generateHelpMessage()
{
    std::string helpText =
            "Usage: sound_processor [-h] [-c config.txt output.wav input1.wav [input2.wav ...]]\n";
    helpText += "Supported converters:\n";
    std::vector<Converter *> converters = {
            new Muter(),
            new Mixer(),
            new VolumeConverter()
    };
    for (const auto &converter: converters) {
        helpText += converter->getName() + "<" + converter->getParameters() +
                ">: " + converter->getDescription() + "\n";
    }
    for (auto &converter: converters) { delete converter; }
    return helpText;
}
