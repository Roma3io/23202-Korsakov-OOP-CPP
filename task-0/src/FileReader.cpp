#include "FileReader.h"

FileReader::FileReader(const std::string &fileName)
{
    inputFileName = fileName;
}

void FileReader::open()
{
    inputFile.open(inputFileName, std::ifstream::in);
}

void FileReader::close()
{
    inputFile.close();
}

bool FileReader::isOpen()
{
    return inputFile.is_open();
}

bool FileReader::hasNext()
{
    return inputFile.peek() != EOF;
}

std::string FileReader::next()
{
    std::string line;
    if (getline(inputFile, line)) {
        return line;
    }
    return "";
}

void FileReader::toBeginning()
{
    inputFile.seekg(0, std::ios::beg);
}
