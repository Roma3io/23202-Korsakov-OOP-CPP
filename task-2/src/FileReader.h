#ifndef FILEREADER_H
#define FILEREADER_H

#include <fstream>
#include <string>

class FileReader
{
private:
    std::ifstream inputFile;
    std::string inputFileName;

public:
    FileReader(const std::string &fileName);
    void open();
    void close();
    bool isOpen();
    bool hasNext();
    std::string next();
    void rewind();
};

#endif
