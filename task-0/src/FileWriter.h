#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

class FileWriter
{
private:
    std::string outputFileName;
    std::ofstream outputFile;

public:
    FileWriter(const std::string &fileName);
    void open();
    void close();
    bool isOpen();
    void write(std::vector <std::string>);
};

#endif
