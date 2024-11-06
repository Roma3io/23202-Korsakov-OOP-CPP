#include "FileWriter.h"
#include <fstream>
#include <iostream>

void FileWriter::writeFile(const std::string &filename, const std::vector<std::string> &lines)
{
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    for (const auto &line: lines) {
        file << line << std::endl;
    }
    file.close();
}
