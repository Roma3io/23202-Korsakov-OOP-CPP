#include "HelpGenerator.h"
#include "MixConverter.h"
#include "MuteConverter.h"

std::string HelpGenerator::generateHelpMessage()
{
    std::string helpText = "Usage: sound_processor [-h] [-c config.txt output.wav input1.wav [input2.wav …]]\n";
    helpText += "Supported converters:\n";
    for (const auto &info: getConvertersInfo()) {
        helpText += info + "\n";
    }
    return helpText;
}

std::vector<std::string> HelpGenerator::getConvertersInfo()
{
    return {
            "mute <start> <end>: Mute the audio from <start> to <end> seconds.",
            "mix <stream_index> <insertion_point>: Mix the additional stream starting at <insertion_point> seconds.",
    };
}
