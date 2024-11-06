#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <vector>

class FileReader
{
public:
    static void readFile(const std::string &fileName, std::vector<std::string> &lines);
};


#endif//FILEREADER_H
