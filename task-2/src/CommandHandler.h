#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include "Universe.h"

class CommandHandler
{
public:
    CommandHandler(Universe &universe);
    void handleCommand(const std::string &command);
    void printHelp();

private:
    Universe &universe;
};

#endif// COMMANDHANDLER_H
