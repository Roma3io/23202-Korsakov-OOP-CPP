#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <vector>
#include <string>
#include <memory>
#include "Converter.h"

class ConfigParser {
public:
    ConfigParser(const std::string& filename, const std::vector<std::vector<int16_t>>& additionalStreams);
    std::vector<Converter*> parse();

private:
    std::string filename;
    std::vector<std::vector<int16_t>> additionalStreams;
};

#endif // CONFIGPARSER_H
