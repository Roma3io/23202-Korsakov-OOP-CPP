#ifndef CONVERTERSCONTROLLER_H
#define CONVERTERSCONTROLLER_H

#include "Converters.h"
#include "ExceptionHandler.h"
#include <vector>
#include <memory>

class ConvertersController {
public:
    ConvertersController(const std::vector<std::pair<std::string, std::vector<std::string>>>& converterConfigs,
                         const std::vector<std::vector<int16_t>>& additionalStreams);
    ~ConvertersController();
    std::vector<Converter*> getConverters();

private:
    std::vector<Converter*> converters;
    std::vector<std::vector<int16_t>> additionalStreams;
};

#endif // CONVERTERSCONTROLLER_H
