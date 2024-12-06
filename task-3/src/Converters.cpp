#include "converters.h"
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include "ExceptionHandler.h"

Muter::Muter(int start, int end) : start(start), end(end) {}

std::vector<int16_t> Muter::process(const std::vector<int16_t> &input)
{
    std::vector<int16_t> output = input;
    int sampleRate = 44100;
    int startSample = start * sampleRate;
    int endSample = end * sampleRate;
    for (int i = startSample; i < endSample && i < output.size(); ++i) {
        output[i] = 0;
    }
    return output;
}

std::string Muter::getName() const { return "Muter"; }

std::string Muter::getDescription() const { return "Mutes the audio."; }

std::string Muter::getParameters() const
{
    return "start: Start time in seconds, end: End time in seconds.";
}

Mixer::Mixer(const std::vector<int16_t> &additionalStream, int insertionPoint)
    : additionalStream(additionalStream), insertionPoint(insertionPoint) {}

std::vector<int16_t> Mixer::process(const std::vector<int16_t> &input)
{
    std::vector<int16_t> output = input;
    int sampleRate = 44100;
    int insertionSample = insertionPoint * sampleRate;
    int minSize = std::min(output.size() - insertionSample,
                           additionalStream.size());
    for (int i = 0; i < minSize; ++i) {
        output[insertionSample + i] =
                (output[insertionSample + i] + additionalStream[i]) / 2;
    }
    return output;
}

std::string Mixer::getName() const { return "Mixer"; }

std::string Mixer::getDescription() const { return "Mixes the audio."; }

std::string Mixer::getParameters() const
{
    return
            "insertion_point: Insertion point in seconds, stream_index: Index of the additional stream.";
}

VolumeConverter::VolumeConverter(float volume) : volume(volume) {}

std::vector<int16_t> VolumeConverter::process(const std::vector<int16_t> &input)
{
    std::vector<int16_t> output(input.size());
    for (size_t i = 0; i < input.size(); ++i) {
        output[i] = static_cast<int16_t>(input[i] * (volume / 100));
    }
    return output;
}

std::string VolumeConverter::getName() const { return "VolumeConverter"; }

std::string VolumeConverter::getDescription() const
{
    return "Adjusts the volume of the audio.";
}

std::string VolumeConverter::getParameters() const
{
    return "volume: Volume adjustment factor.";
}

Converter *MuterFactory::createConverter() const { return new Muter(0, 0); }

Converter *MixerFactory::createConverter() const
{
    return new Mixer(std::vector<int16_t>(), 0);
}

Converter *VolumeFactory::createConverter() const
{
    return new VolumeConverter(100.0);
}
