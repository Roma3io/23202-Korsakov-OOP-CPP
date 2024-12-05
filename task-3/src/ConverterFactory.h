#ifndef CONVERTERFACTORY_H
#define CONVERTERFACTORY_H

#include <memory>
#include <string>
#include <vector>
#include "Converter.h"
#include "MuteConverter.h"
#include "MixConverter.h"

class ConverterFactory {
public:
    static Converter* createConverter(const std::string& type, const std::vector<std::string>& params, const std::vector<std::vector<int16_t>>& additionalStreams);
};

#endif // CONVERTERFACTORY_H
