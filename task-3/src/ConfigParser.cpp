#include "ConfigParser.h"
#include "ConverterFactory.h"
#include "ExceptionHandler.h"
#include <fstream>
#include <sstream>

ConfigParser::ConfigParser(const std::string& filename, const std::vector<std::vector<int16_t>>& additionalStreams)
    : filename(filename), additionalStreams(additionalStreams) {}

std::vector<Converter*> ConfigParser::parse() {
    std::vector<Converter*> converters;
    std::ifstream file(filename);
    if (!file) {
        throw FileNotFoundException("Cannot open config file: " + filename);
    }
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }
        std::istringstream iss(line);
        std::string type;
        iss >> type;
        std::vector<std::string> params;
        std::string param;
        while (iss >> param) {
            params.push_back(param);
        }
        converters.push_back(ConverterFactory::createConverter(type, params, additionalStreams));
    }
    return converters;
}
