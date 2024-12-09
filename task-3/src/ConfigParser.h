#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <sstream>
#include "ExceptionHandler.h"
#include <stdint.h>

class ConfigParser
{
public:
    ConfigParser(const std::string &filename,
                 const std::vector<std::vector<int16_t>> &additionalStreams);
    std::vector<std::pair<std::string, std::vector<std::string>>> parse();

private:
    std::string filename;
    std::vector<std::vector<int16_t>> additionalStreams;
};

#endif // CONFIGPARSER_H
