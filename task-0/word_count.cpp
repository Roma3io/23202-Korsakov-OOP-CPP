#include "src/FileReader.h"
#include "src/FileWriter.h"
#include "src/Statistic.h"

int main(int argc, char *argv[])
{
    std::string inputFileName = argv[1];
    Statistic statistic;
    FileReader fileReader(inputFileName);
    fileReader.open();
    statistic.getWordsFrequency(fileReader);
    fileReader.close();
    std::string outputFileName = argv[2];
    FileWriter fileWriter(outputFileName);
    std::vector<std::pair<std::string, int>> sortedWords = statistic.getSortedWordsFrequency();
    int wordsAmount = statistic.getWordsAmount();
    fileWriter.open();
    fileWriter.writeWordsFrequencyToFile(sortedWords, wordsAmount);
    fileWriter.close();
    return 0;
}
