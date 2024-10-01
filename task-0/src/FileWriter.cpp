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

bool FileWriter::isOpen()
{
    return outputFile.is_open();
}

void FileWriter::write(std::vector<std::string> lines)
{
    for (const auto &line: lines) {
        outputFile << line << std::endl;
    }
}
