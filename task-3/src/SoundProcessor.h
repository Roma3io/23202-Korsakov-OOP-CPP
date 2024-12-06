#ifndef SOUNDPROCESSOR_H
#define SOUNDPROCESSOR_H

#include "ConfigParser.h"
#include "ExceptionHandler.h"
#include "WAVReader.h"
#include "WAVWriter.h"
#include "Converters.h"
#include "ConvertersController.h"
#include <iostream>
#include <memory>
#include <vector>

class SoundProcessor {
public:
    SoundProcessor(const std::string& configFile, const std::string& outputFile, const std::vector<std::string>& inputFiles);
    void process();

private:
    std::string configFile;
    std::string outputFile;
    std::vector<std::string> inputFiles;
};

#endif // SOUNDPROCESSOR_H
