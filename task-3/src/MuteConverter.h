#ifndef MUTECONVERTER_H
#define MUTECONVERTER_H

#include "Converter.h"

class MuteConverter : public Converter
{
public:
    MuteConverter(int start, int end);
    std::vector<int16_t> process(const std::vector<int16_t> &input) override;

private:
    int start;
    int end;
};

#endif // MUTECONVERTER_H
