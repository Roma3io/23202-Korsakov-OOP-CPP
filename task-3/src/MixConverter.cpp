#include "MixConverter.h"
#include <algorithm>

MixConverter::MixConverter(const std::vector<int16_t>& additionalStream, int insertionPoint)
    : additionalStream(additionalStream), insertionPoint(insertionPoint) {}

std::vector<int16_t> MixConverter::process(const std::vector<int16_t>& input) {
    std::vector<int16_t> output = input;
    int sampleRate = 44100;
    int insertionSample = insertionPoint * sampleRate;
    int minSize = std::min(output.size() - insertionSample, additionalStream.size());
    for (int i = 0; i < minSize; ++i) {
        output[insertionSample + i] = (output[insertionSample + i] + additionalStream[i]) / 2;
    }
    return output;
}
