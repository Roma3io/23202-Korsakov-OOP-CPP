#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

class FileWriter
{
private:
    std::string outputFileName;
    std::ofstream outputFile;
    static constexpr double PERCENT = 100;

    static double calculateFrequencyPercent(int wordFrequency, int wordsAmount);

public:
    FileWriter(const std::string &fileName);
    void open();
    void close();
    bool isOpen();
    void writeWordsFrequencyToFile(std::vector<std::pair<std::string, int>> sortedWords, int wordsAmount);
};

#endif
