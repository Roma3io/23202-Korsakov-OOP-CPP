#include "ConvertersController.h"
#include "ExceptionHandler.h"
#include <stdexcept>

ConvertersController::ConvertersController(
        const std::vector<std::pair<std::string, std::vector<std::string>>> &
        converterConfigs,
        const std::vector<std::vector<int16_t>> &additionalStreams)
    : converterConfigs(converterConfigs), additionalStreams(additionalStreams)
{
    for (const auto &config: converterConfigs) {
        const std::string &type = config.first;
        if (type == "mute") {
            converterFactories.push_back(new MuterFactory());
        } else if (type == "mix") {
            converterFactories.push_back(new MixerFactory());
        } else if (type == "volume") {
            converterFactories.push_back(new VolumeFactory());
        } else { throw ExceptionHandler("Unknown converter type: " + type); }
    }
}

ConvertersController::~ConvertersController()
{
    for (auto &converterFactory: converterFactories) {
        delete converterFactory;
    }
}

std::vector<Converter *> ConvertersController::createConverters()
{
    std::vector<Converter *> converters;
    for (size_t i = 0; i < converterConfigs.size(); ++i) {
        const std::vector<std::string> &params = converterConfigs[i].second;
        ConverterFactory *factory = converterFactories[i];
        converters.push_back(
                factory->createConverter(params, additionalStreams));
    }
    return converters;
}
