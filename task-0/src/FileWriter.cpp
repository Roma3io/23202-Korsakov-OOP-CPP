#include "FileWriter.h"

FileWriter::FileWriter(const std::string &fileName)
{
    outputFileName = fileName;
}

void FileWriter::open()
{
    outputFile.open(outputFileName, std::ofstream::out);
}

void FileWriter::close()
{
    outputFile.close();
}

bool FileWriter::isOpen(){
    return outputFile.is_open();
}

double FileWriter::calculateFrequencyPercent(int wordFrequency, int wordsAmount)
{
    return ((double) wordFrequency / wordsAmount) * PERCENT;
}

void FileWriter::writeWordsFrequencyToFile(std::vector<std::pair<std::string, int>> sortedWords, int wordsAmount)
{
    outputFile << "Word, Frequency, Frequency(%)" << std::endl;
    for (const auto &pair: sortedWords) {
        double frequencyPercent = calculateFrequencyPercent(pair.second, wordsAmount);
        outputFile << pair.first << "," << pair.second << "," << std::fixed << std::setprecision(2) << frequencyPercent << std::endl;
    }
}
