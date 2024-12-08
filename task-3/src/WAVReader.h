#ifndef WAVREADER_H
#define WAVREADER_H

#include <string>
#include <vector>
#include <cstdint>
#include <stdexcept>

struct WAVHeader
{
    char chunkID[4];
    uint32_t chunkSize;
    char format[4];
    char subchunk1ID[4];
    uint32_t subchunk1Size;
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
    char subchunk2ID[4];
    uint32_t subchunk2Size;
};

class WAVReader
{
public:
    explicit WAVReader(const std::string &filename);
    ~WAVReader();
    const WAVHeader &getHeader() const;
    const std::vector<int16_t> &getSamples() const;

private:
    std::string filename;
    WAVHeader header;
    std::vector<int16_t> samples;
    void readWAVFile();
};

#endif
