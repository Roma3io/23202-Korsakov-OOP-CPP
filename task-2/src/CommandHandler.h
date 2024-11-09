#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include "Universe.h"
#include <string>

class CommandHandler
{
public:
    CommandHandler(Universe &universe);
    void handleCommand(const std::string &command);
    static void printHelp();

private:
    Universe &universe;
    void handleTick(const std::string &command) const;
    void handleAuto() const;
    void handleDump(const std::string &command) const;
};

#endif // COMMANDHANDLER_H
