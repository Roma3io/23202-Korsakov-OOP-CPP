#ifndef HELPGENERATOR_H
#define HELPGENERATOR_H

#include <string>
#include <vector>

class HelpGenerator {
public:
    std::string generateHelpMessage();

private:
    std::vector<std::string> getConvertersInfo();
};

#endif // HELPGENERATOR_H
