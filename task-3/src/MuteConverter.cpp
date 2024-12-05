#include "MuteConverter.h"

MuteConverter::MuteConverter(int start, int end) : start(start), end(end) {}

std::vector<int16_t> MuteConverter::process(const std::vector<int16_t>& input) {
    std::vector<int16_t> output = input;
    int sampleRate = 44100;
    int startSample = start * sampleRate;
    int endSample = end * sampleRate;
    for (int i = startSample; i < endSample && i < output.size(); ++i) {
        output[i] = 0;
    }
    return output;
}
