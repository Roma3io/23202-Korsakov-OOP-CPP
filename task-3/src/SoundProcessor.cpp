#include "SoundProcessor.h"

SoundProcessor::SoundProcessor(const std::string& configFile, const std::string& outputFile, const std::vector<std::string>& inputFiles)
    : configFile(configFile), outputFile(outputFile), inputFiles(inputFiles) {}

void SoundProcessor::process() {
    try {
        std::vector<std::vector<int16_t>> additionalStreams;
        WAVReader mainReader(inputFiles[0]);
        std::vector<int16_t> mainSamples = mainReader.getSamples();
        for (size_t i = 1; i < inputFiles.size(); ++i) {
            WAVReader additionalReader(inputFiles[i]);
            additionalStreams.push_back(additionalReader.getSamples());
        }
        ConfigParser parser(configFile, additionalStreams);
        std::vector<std::pair<std::string, std::vector<std::string>>> converterConfigs = parser.parse();
        ConvertersController convertersController(converterConfigs, additionalStreams);
        std::vector<Converter*> converters = convertersController.getConverters();

        for (const auto& converter : converters) {
            mainSamples = converter->process(mainSamples);
        }

        WAVWriter writer(outputFile);
        WAVHeader header = mainReader.getHeader();
        header.subchunk2Size = mainSamples.size() * sizeof(int16_t);
        writer.writeWAVFile(header, mainSamples);
    } catch (const ExceptionHandler& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        exit(2);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        exit(3);
    }
}
