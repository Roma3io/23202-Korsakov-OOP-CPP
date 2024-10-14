#include "src/FileReader.h"
#include "src/FileWriter.h"
#include "src/Statistic.h"

int main(int argc, char *argv[])
{
    std::string inputFileName = argv[1];
    Statistic statistic;
    FileReader fileReader(inputFileName);
    fileReader.open();
    while (fileReader.hasNext()) {
        std::string line = fileReader.next();
        std::list<std::string> words = Parser::splitIntoWords(line);
        for (const std::string &word: words) {
            statistic.addWord(word);
        }
    }
    fileReader.close();
    std::string outputFileName = argv[2];
    FileWriter fileWriter(outputFileName);
    std::vector<std::pair<std::string, int>> sortedWords = statistic.getStatistic();
    std::vector<std::string> lines;
    lines.push_back("Word, Frequency, Frequency(%)");
    for (const auto &pair: sortedWords) {
        double frequencyPercent = (pair.second / static_cast<double>(statistic.getWordsAmount())) * 100;
        std::ostringstream oss;
        oss << pair.first << "," << pair.second << "," << std::fixed << std::setprecision(2) << frequencyPercent;
        lines.push_back(oss.str());
    }
    fileWriter.open();
    fileWriter.write(lines);
    fileWriter.close();
    return 0;
}
