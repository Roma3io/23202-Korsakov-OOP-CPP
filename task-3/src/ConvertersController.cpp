#include "ConvertersController.h"
#include "Converters.h"
#include <stdexcept>

ConvertersController::ConvertersController(const std::vector<std::pair<std::string, std::vector<std::string>>>& converterConfigs,
                                            const std::vector<std::vector<int16_t>>& additionalStreams)
    : additionalStreams(additionalStreams) {
    for (const auto& config : converterConfigs) {
        const std::string& type = config.first;
        const std::vector<std::string>& params = config.second;
        if (type == "mute") {
            if (params.size() != 2) {
                throw InvalidConfigException("Invalid number of parameters for mute converter");
            }
            int start = std::stoi(params[0]);
            int end = std::stoi(params[1]);
            MuterFactory muterFactory;
            converters.push_back(muterFactory.createConverter());
        } else if (type == "mix") {
            if (params.size() != 2) {
                throw InvalidConfigException("Invalid number of parameters for mix converter");
            }
            int streamIndex = std::stoi(params[0]);
            int insertionPoint = std::stoi(params[1]);
            if (streamIndex < 0 || streamIndex >= additionalStreams.size()) {
                throw InvalidConfigException("Invalid stream index for mix converter");
            }
            MixerFactory mixerFactory;
            converters.push_back(mixerFactory.createConverter());
        } else if (type == "volume") {
            if (params.size() != 1) {
                throw InvalidConfigException("Invalid number of parameters for volume converter");
            }
            float volume = std::stof(params[0]);
            VolumeFactory volumeFactory;
            converters.push_back(volumeFactory.createConverter());
        } else {
            throw InvalidConfigException("Unknown converter type: " + type);
        }
    }
}

ConvertersController::~ConvertersController() {
    for (auto& converter : converters) {
        delete converter;
    }
}

std::vector<Converter*> ConvertersController::getConverters() {
    return converters;
}
