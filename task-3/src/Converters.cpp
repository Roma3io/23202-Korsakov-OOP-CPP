#include "ExceptionHandler.h"
#include "converters.h"
#include <stdexcept>
#include <algorithm>

Muter::Muter(const std::vector<std::string> &params) : Converter()
{
    start = std::stoi(params[0]);
    end = std::stoi(params[1]);
}

std::vector<int16_t> Muter::process(const std::vector<int16_t> &input)
{
    std::vector<int16_t> output = input;
    int startSample = start * sampleRate;
    int endSample = end * sampleRate;
    for (int i = startSample; i < endSample && i < output.size(); ++i) {
        output[i] = 0;
    }
    return output;
}

Mixer::Mixer(const std::vector<std::string> &params,
             const std::vector<std::vector<int16_t>> &additionalStreams) :
    Converter()
{
    streamIndex = std::stoi(params[0].substr(1)) - 1;
    insertionPoint = std::stoi(params[1]);
    if (streamIndex < 0 || streamIndex > additionalStreams.size()) {
        throw InvalidConfigException("Invalid stream index for Mixer");
    }
    additionalStream = additionalStreams[streamIndex - 1];
}

std::vector<int16_t> Mixer::process(const std::vector<int16_t> &input)
{
    std::vector<int16_t> output = input;
    int insertionSample = insertionPoint * sampleRate;
    int minSize = std::min(output.size() - insertionSample,
                           additionalStream.size());
    for (int i = 0; i < minSize; ++i) {
        output[insertionSample + i] =
                (output[insertionSample + i] + additionalStream[i]) / 2;
    }
    return output;
}

VolumeConverter::VolumeConverter(
        const std::vector<std::string> &params) : Converter()
{
    volume = std::stof(params[0]);
}

std::vector<int16_t> VolumeConverter::process(const std::vector<int16_t> &input)
{
    std::vector<int16_t> output(input.size());
    for (size_t i = 0; i < input.size(); ++i) {
        output[i] = static_cast<int16_t>(input[i] * (volume / 100));
    }
    return output;
}

Converter *MuterFactory::createConverter(const std::vector<std::string> &params,
                                         const std::vector<std::vector<int16_t>>
                                         &additionalStreams) const
{
    return new Muter(params);
}

Converter *MixerFactory::createConverter(const std::vector<std::string> &params,
                                         const std::vector<std::vector<int16_t>>
                                         &additionalStreams) const
{
    return new Mixer(params, additionalStreams);
}

Converter *VolumeFactory::createConverter(
        const std::vector<std::string> &params,
        const std::vector<std::vector<int16_t>> &additionalStreams) const
{
    return new VolumeConverter(params);
}
