#include "ConverterFactory.h"
#include "ExceptionHandler.h"

Converter *ConverterFactory::createConverter(const std::string &type, const std::vector<std::string> &params, const std::vector<std::vector<int16_t>> &additionalStreams)
{
    if (type == "mute") {
        if (params.size() != 2) {
            throw InvalidConfigException("Mute converter requires 2 parameters");
        }
        int start = std::stoi(params[0]);
        int end = std::stoi(params[1]);
        return new MuteConverter(start, end);
    } else if (type == "mix") {
        if (params.size() != 2) {
            throw InvalidConfigException("Mix converter requires 2 parameters");
        }
        int streamIndex = std::stoi(params[0].substr(1)) - 1;
        int insertionPoint = std::stoi(params[1]);
        if (streamIndex < 0 || streamIndex > additionalStreams.size()) {
            throw InvalidConfigException("Invalid stream index");
        }
        return new MixConverter(additionalStreams[streamIndex - 1], insertionPoint);
    } else {
        throw InvalidConfigException("Unknown converter type: " + type);
    }
}
