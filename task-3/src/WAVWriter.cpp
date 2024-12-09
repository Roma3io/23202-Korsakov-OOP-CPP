#include "WAVWriter.h"

#include "ExceptionHandler.h"

#include <fstream>
#include <stdexcept>

WAVWriter::WAVWriter(const std::string &filename) : filename(filename) {}

WAVWriter::~WAVWriter() {}

void WAVWriter::writeWAVFile(const WAVHeader &header,
                             const std::vector<int16_t> &samples)
{
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw FileNotFoundException("Cannot open output file: " + filename);
    }
    file.write(header.chunkID, 4);
    file.write(reinterpret_cast<const char *>(&header.chunkSize), 4);
    file.write(header.format, 4);
    file.write(header.subchunk1ID, 4);
    file.write(reinterpret_cast<const char *>(&header.subchunk1Size), 4);
    file.write(reinterpret_cast<const char *>(&header.audioFormat), 2);
    file.write(reinterpret_cast<const char *>(&header.numChannels), 2);
    file.write(reinterpret_cast<const char *>(&header.sampleRate), 4);
    file.write(reinterpret_cast<const char *>(&header.byteRate), 4);
    file.write(reinterpret_cast<const char *>(&header.blockAlign), 2);
    file.write(reinterpret_cast<const char *>(&header.bitsPerSample), 2);
    file.write(header.subchunk2ID, 4);
    file.write(reinterpret_cast<const char *>(&header.subchunk2Size), 4);
    file.write(reinterpret_cast<const char *>(samples.data()),
               header.subchunk2Size);
    if (!file) {
        throw FileNotFoundException(
                "Failed to write WAV data to file: " + filename);
    }
}
