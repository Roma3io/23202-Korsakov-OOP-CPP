#include "FileReader.h"
#include <fstream>
#include <iostream>

void FileReader::readFile(const std::string& filename, std::vector<std::string>& lines) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
}