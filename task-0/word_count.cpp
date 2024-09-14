#include <algorithm>
#include <fstream>
#include <iomanip>
#include <list>
#include <map>
#include <string>
#include <vector>

using std::list;
using std::string;

class StringProcessor
{
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

private:
    static unsigned char toLowerChar(unsigned char c) { return tolower(c); }
};

class FileProcessor
{
public:
    static list<string> readLinesFromFile(const string &file_name)
    {
        list<string> lines;
        std::ifstream input_file(file_name);
        string line;
        while (getline(input_file, line)) {
            lines.push_back(line);
        }
        input_file.close();
        return lines;
    }

    static void writeWordsFrequencyToFile(
            const string &file_name,
            const std::vector<std::pair<string, int>> &sorted_words,
            int words_amount)
    {
        std::ofstream output_file(file_name);
        output_file << "Word, Frequency, Frequency(%)" << std::endl;
        for (const auto &pair: sorted_words) {
            double frequency_percent =
                    calculateFrequencyPercent(pair.second, words_amount);
            output_file << pair.first << "," << pair.second << "," << std::fixed
                        << std::setprecision(2) << frequency_percent << std::endl;
        }
        output_file.close();
    }

private:
    static double calculateFrequencyPercent(int word_frequency,
                                            int words_amount)
    {
        return ((double) word_frequency / words_amount) * 100;
    }
};

class WordFrequencyCounter
{
public:
    void countWordsFrequency(const string &input_file_name)
    {
        list<string> lines = FileProcessor::readLinesFromFile(input_file_name);
        for (const auto &line: lines) {
            list<string> words = StringProcessor::splitIntoWords(line);
            for (const auto &word: words) {
                words_amount++;
                words_frequency[word]++;
            }
        }
    }
    std::vector<std::pair<string, int>> getSortedWordsFrequency() const
    {
        std::vector<std::pair<string, int>> sorted_words(words_frequency.begin(),
                                                         words_frequency.end());
        sort(sorted_words.begin(), sorted_words.end(), frequencyComparator);
        return sorted_words;
    }

    int getWordsAmount() const { return words_amount; }

private:
    std::map<string, int> words_frequency;
    int words_amount = 0;

    static bool frequencyComparator(const std::pair<string, int> &a,
                                    const std::pair<string, int> &b)
    {
        return a.second > b.second;
    }
};

int main(int argc, char *argv[])
{
    string input_file_name = argv[1];
    string output_file_name = argv[2];
    WordFrequencyCounter words_counter;
    words_counter.countWordsFrequency(input_file_name);
    std::vector<std::pair<string, int>> sorted_words =
            words_counter.getSortedWordsFrequency();
    FileProcessor::writeWordsFrequencyToFile(output_file_name, sorted_words,
                                             words_counter.getWordsAmount());
    return 0;
}
