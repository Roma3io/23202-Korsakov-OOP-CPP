#include "ConfigParser.h"
#include "ExceptionHandler.h"
#include "HelpGenerator.h"
#include "WAVReader.h"
#include "WAVWriter.h"
#include <iostream>
#include <memory>
#include <vector>

void printHelpMessage(const std::string& message)
{
    std::cout << message << std::endl;
}

int main(int argc, char *argv[])
{
    HelpGenerator helpGenerator;
    std::string helpMessage = helpGenerator.generateHelpMessage();
    if (argc < 2) {
        printHelpMessage(helpMessage);
        return 1;
    }
    std::string configFile;
    std::string outputFile;
    std::vector<std::string> inputFiles;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-h") {
            printHelpMessage(helpMessage);
            return 0;
        } else if (arg == "-c") {
            if (i + 3 < argc) {
                configFile = argv[++i];
                outputFile = argv[++i];
                for (int j = i + 1; j < argc; ++j) {
                    inputFiles.push_back(argv[j]);
                }
            } else {
                std::cerr << "Error: Invalid arguments" << std::endl;
                return 1;
            }
        }
    }
    try {
        std::vector<std::vector<int16_t>> additionalStreams;
        WAVReader mainReader(inputFiles[0]);
        std::vector<int16_t> mainSamples = mainReader.getSamples();
        for (size_t i = 1; i < inputFiles.size(); ++i) {
            WAVReader additionalReader(inputFiles[i]);
            additionalStreams.push_back(additionalReader.getSamples());
        }
        ConfigParser parser(configFile, additionalStreams);
        std::vector<Converter *> converters = parser.parse();
        for (const auto &converter: converters) {
            mainSamples = converter->process(mainSamples);
        }
        WAVWriter writer(outputFile);
        WAVHeader header = mainReader.getHeader();
        header.subchunk2Size = mainSamples.size() * sizeof(int16_t);
        writer.writeWAVFile(header, mainSamples);
    } catch (const ExceptionHandler &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 2;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 3;
    }
    return 0;
}
