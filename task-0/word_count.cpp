#include <algorithm>
#include <fstream>
#include <iomanip>
#include <list>
#include <map>
#include <string>
#include <vector>

using std::list;
using std::string;

class Parser
{
private:
    static unsigned char toLowerChar(unsigned char c) { return tolower(c); }

public:
    static string toLower(const string &str)
    {
        string result = str;
        transform(result.begin(), result.end(), result.begin(), toLowerChar);
        return result;
    }

    static string removePunctuation(const string &str)
    {
        string result = str;
        result.erase(remove_if(result.begin(), result.end(), ::ispunct),
                     result.end());
        return result;
    }

    static list<string> splitIntoWords(const string &str)
    {
        list<string> words;
        std::istringstream iss(str);
        string word;
        while (iss >> word) {
            word = removePunctuation(word);
            word = toLower(word);
            if (!word.empty()) {
                words.push_back(word);
            }
        }
        return words;
    }
};

class FileReader
{
private:
    std::ifstream inputFile;
    string inputFileName;

public:
    FileReader(const string &fileName)
    {
        inputFileName = fileName;
    }

    void open()
    {
        inputFile.open(inputFileName, std::ifstream::in);
    }

    void close()
    {
        inputFile.close();
    }

    bool hasNext()
    {
        return !inputFile.eof();
    }

    string next()
    {
        string line;
        if (getline(inputFile, line)) {
            return line;
        }
        return "";
    }
    void toBeginning()
    {
        inputFile.seekg(0, std::ios::beg);
    }
};

class Statistic
{
private:
    std::map<string, int> wordsFrequency;
    int wordsAmount = 0;
    static bool frequencyComparator(const std::pair<string, int> &a,
                                    const std::pair<string, int> &b)
    {
        return a.second > b.second;
    }

public:
    void addWord(const string &word)
    {
        wordsAmount++;
        wordsFrequency[word]++;
    }
    void addWordsFromString(const string &str)
    {
        list<string> words = Parser::splitIntoWords(str);
        for (const string &word: words) {
            addWord(word);
        }
    }
    void getWordsFrequency(FileReader &fileReader)
    {
        while (fileReader.hasNext()) {
            string line = fileReader.next();
            addWordsFromString(line);
        }
    }
    std::vector<std::pair<string, int>> getSortedWordsFrequency() const
    {
        std::vector<std::pair<string, int>> sortedWords(wordsFrequency.begin(),
                                                        wordsFrequency.end());
        sort(sortedWords.begin(), sortedWords.end(), frequencyComparator);
        return sortedWords;
    }
    int getWordsAmount() const { return wordsAmount; }
};

class FileWriter
{
private:
    string outputFileName;
    std::ofstream outputFile;
    static constexpr double PERCENT = 100;
    static double calculateFrequencyPercent(int wordFrequency,
                                            int wordsAmount)
    {
        return ((double) wordFrequency / wordsAmount) * PERCENT;
    }

public:
    FileWriter(const string &fileName)
    {
        outputFileName = fileName;
    }
    void open()
    {
        outputFile.open(outputFileName, std::ofstream::out);
    }
    void close()
    {
        outputFile.close();
    }
    void writeWordsFrequencyToFile(const Statistic &statistic)
    {
        outputFile << "Word, Frequency, Frequency(%)" << std::endl;
        std::vector<std::pair<string, int>> sortedWords =
                statistic.getSortedWordsFrequency();
        for (const auto &pair: sortedWords) {
            double frequencyPercent =
                    calculateFrequencyPercent(pair.second, statistic.getWordsAmount());
            outputFile << pair.first << "," << pair.second << "," << std::fixed
                       << std::setprecision(2) << frequencyPercent << std::endl;
        }
        outputFile.close();
    }
};

int main(int argc, char *argv[])
{
    string inputFileName = argv[1];
    Statistic statistic;
    FileReader fileReader(inputFileName);
    fileReader.open();
    statistic.getWordsFrequency(fileReader);
    fileReader.close();
    string outputFileName = argv[2];
    FileWriter fileWriter(outputFileName);
    fileWriter.open();
    fileWriter.writeWordsFrequencyToFile(statistic);
    fileWriter.close();
    return 0;
}
