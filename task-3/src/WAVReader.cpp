#include "WAVReader.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>

WAVReader::WAVReader(const std::string &filename) : filename(filename) { readWAVFile(); }

WAVReader::~WAVReader() {}

const WAVHeader &WAVReader::getHeader() const { return header; }

const std::vector<int16_t> &WAVReader::getSamples() const { return samples; }

void WAVReader::readWAVFile()
{
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) { throw std::runtime_error("Cannot open WAV file: " + filename); }
    file.read(reinterpret_cast<char *>(&header.chunkID), 4);
    file.read(reinterpret_cast<char *>(&header.chunkSize), 4);
    file.read(reinterpret_cast<char *>(&header.format), 4);
    if (std::strncmp(header.chunkID, "RIFF", 4) != 0 ||
        std::strncmp(header.format, "WAVE", 4) != 0) { throw std::runtime_error("Invalid WAV file format: " + filename); }
    file.read(reinterpret_cast<char *>(&header.subchunk1ID), 4);
    file.read(reinterpret_cast<char *>(&header.subchunk1Size), 4);
    file.read(reinterpret_cast<char *>(&header.audioFormat), 2);
    file.read(reinterpret_cast<char *>(&header.numChannels), 2);
    file.read(reinterpret_cast<char *>(&header.sampleRate), 4);
    file.read(reinterpret_cast<char *>(&header.byteRate), 4);
    file.read(reinterpret_cast<char *>(&header.blockAlign), 2);
    file.read(reinterpret_cast<char *>(&header.bitsPerSample), 2);
    if (std::strncmp(header.subchunk1ID, "fmt ", 4) != 0 || header.audioFormat != 1) { throw std::runtime_error("Unsupported WAV format: " + filename); }
    char subchunkID[4];
    uint32_t subchunkSize;
    while (true) {
        file.read(subchunkID, 4);
        file.read(reinterpret_cast<char *>(&subchunkSize), 4);
        if (std::strncmp(subchunkID, "data", 4) == 0) {
            header.subchunk2ID[0] = subchunkID[0];
            header.subchunk2ID[1] = subchunkID[1];
            header.subchunk2ID[2] = subchunkID[2];
            header.subchunk2ID[3] = subchunkID[3];
            header.subchunk2Size = subchunkSize;
            break;
        }
        file.seekg(subchunkSize, std::ios::cur);
    }
    int numSamples = header.subchunk2Size / (header.bitsPerSample / 8);
    samples.resize(numSamples);
    file.read(reinterpret_cast<char *>(samples.data()), header.subchunk2Size);
    if (!file) { throw std::runtime_error("Failed to read WAV data from file: " + filename); }
}
