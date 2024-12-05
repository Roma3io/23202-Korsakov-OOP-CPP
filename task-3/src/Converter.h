#ifndef CONVERTER_H
#define CONVERTER_H

#include <vector>
#include <cstdint>

class Converter
{
public:
    virtual ~Converter() = default;
    virtual std::vector<int16_t> process(const std::vector<int16_t> &input) = 0;
};

#endif // CONVERTER_H
