#ifndef MIXCONVERTER_H
#define MIXCONVERTER_H

#include "Converter.h"
#include <vector>

class MixConverter : public Converter {
public:
    MixConverter(const std::vector<int16_t>& additionalStream, int insertionPoint);
    std::vector<int16_t> process(const std::vector<int16_t>& input) override;

private:
    std::vector<int16_t> additionalStream;
    int insertionPoint;
};

#endif // MIXCONVERTER_H
