#ifndef CONVERTERS_H
#define CONVERTERS_H

#include <string>
#include <vector>
#include <memory>

class Converter
{
protected:
    const int sampleRate = 44100;

public:
    virtual ~Converter() = default;
    virtual std::vector<int16_t> process(const std::vector<int16_t> &input) = 0;
    virtual std::string getName() const = 0;
    virtual std::string getDescription() const = 0;
    virtual std::string getParameters() const = 0;
};

class Muter : public Converter
{
public:
    Muter(int start, int end);
    std::vector<int16_t> process(const std::vector<int16_t> &input) override;
    std::string getName() const override;
    std::string getDescription() const override;
    std::string getParameters() const override;

private:
    int start;
    int end;
};

class Mixer : public Converter
{
public:
    Mixer(const std::vector<int16_t> &additionalStream, int insertionPoint);
    std::vector<int16_t> process(const std::vector<int16_t> &input) override;
    std::string getName() const override;
    std::string getDescription() const override;
    std::string getParameters() const override;

private:
    std::vector<int16_t> additionalStream;
    int insertionPoint;
};

class VolumeConverter : public Converter
{
public:
    VolumeConverter(float volume);
    std::vector<int16_t> process(const std::vector<int16_t> &input) override;
    std::string getName() const override;
    std::string getDescription() const override;
    std::string getParameters() const override;

private:
    float volume;
};

class ConverterFactory
{
public:
    virtual Converter *createConverter() const = 0;
    virtual ~ConverterFactory() = default;
};

class MuterFactory : public ConverterFactory
{
public:
    Converter *createConverter() const override;
};

class MixerFactory : public ConverterFactory
{
public:
    Converter *createConverter() const override;
};

class VolumeFactory : public ConverterFactory
{
public:
    Converter *createConverter() const override;
};

#endif // CONVERTERS_H
