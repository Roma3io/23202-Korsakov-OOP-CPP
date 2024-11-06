#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <string>
#include <vector>

class FileWriter
{
public:
    static void writeFile(const std::string &fileName, const std::vector<std::string> &lines);
};


#endif//FILEWRITER_H
