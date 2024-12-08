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
    Converter() = default;
    virtual ~Converter() = default;
    virtual std::vector<int16_t> process(const std::vector<int16_t> &input) = 0;
    virtual std::string getName() const = 0;
    virtual std::string getDescription() const = 0;
    virtual std::string getParameters() const = 0;
};

class Muter : public Converter
{
public:
    Muter() : Converter() {}
    Muter(const std::vector<std::string> &params);
    std::vector<int16_t> process(const std::vector<int16_t> &input) override;
    std::string getName() const override { return "Muter"; }

    std::string getDescription() const override
    {
        return "Mute the audio from <start> to <end>";
    }

    std::string getParameters() const override { return "start, end"; };

private:
    int start;
    int end;
};

class Mixer : public Converter
{
public:
    Mixer() : Converter() {}
    Mixer(const std::vector<std::string> &params,
          const std::vector<std::vector<int16_t>> &additionalStreams);

    std::vector<int16_t> process(const std::vector<int16_t> &input) override;
    std::string getName() const override { return "Mixer"; }

    std::string getDescription() const override
    {
        return
                "Mix the audio with index:<stream_index> starting from <insertion_point>";
    }

    std::string getParameters() const override
    {
        return "stream_index, insertion_point(seconds)";
    };

private:
    std::vector<int16_t> additionalStream;
    int insertionPoint;
    int streamIndex;
};

class VolumeConverter : public Converter
{
public:
    VolumeConverter() : Converter() {}
    VolumeConverter(const std::vector<std::string> &params);
    std::vector<int16_t> process(const std::vector<int16_t> &input) override;
    std::string getName() const override { return "VolumeConverter"; }

    std::string getDescription() const override
    {
        return "Set <percentage> of the audio volume";
    }

    std::string getParameters() const override { return "percentage"; };

private:
    float volume;
};

class ConverterFactory
{
public:
    virtual Converter *createConverter(const std::vector<std::string> &params,
                                       const std::vector<std::vector<int16_t>> &
                                       additionalStreams) const = 0;
    virtual ~ConverterFactory() = default;
};

class MuterFactory : public ConverterFactory
{
public:
    Converter *createConverter(const std::vector<std::string> &params,
                               const std::vector<std::vector<int16_t>> &
                               additionalStreams) const override;
};

class MixerFactory : public ConverterFactory
{
public:
    Converter *createConverter(const std::vector<std::string> &params,
                               const std::vector<std::vector<int16_t>> &
                               additionalStreams) const override;
};

class VolumeFactory : public ConverterFactory
{
public:
    Converter *createConverter(const std::vector<std::string> &params,
                               const std::vector<std::vector<int16_t>> &
                               additionalStreams) const override;
};

#endif // CONVERTERS_H
