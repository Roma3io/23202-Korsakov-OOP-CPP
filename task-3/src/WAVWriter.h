#ifndef WAVWRITER_H
#define WAVWRITER_H

#include "WAVReader.h"
#include <string>

class WAVWriter
{
public:
    WAVWriter(const std::string &filename);
    ~WAVWriter();

    void writeWAVFile(const WAVHeader &header,
                      const std::vector<int16_t> &samples);

private:
    std::string filename;
};

#endif // WAVWRITER_H
