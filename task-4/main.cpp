#include "CSVParser.h"
#include "TuplePrinter.h"
#include <fstream>
#include <iostream>
#include <string>

int main()
{
    try {
        std::ifstream file("test.csv");
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file");
        }
        CSVParser<int, std::string> parser(file, 0);
        for (std::tuple<int, std::string> rs: parser) {
            std::cout << rs << std::endl;
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 3;
    }
    return 0;
}
