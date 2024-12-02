#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include "Universe.h"
#include <string>

class CommandHandler
{
public:
    CommandHandler(Universe &universe);
    virtual void handle() = 0;

protected:
    Universe &universe;
};

class TickCommandHandler : public CommandHandler
{
public:
    TickCommandHandler(Universe &universe, int iteration);
    void handle() override;

private:
    int iteration;
};

class AutoCommandHandler : public CommandHandler
{
public:
    AutoCommandHandler(Universe &universe);
    void handle() override;
};

class DumpCommandHandler : public CommandHandler
{
public:
    DumpCommandHandler(Universe &universe, const std::string &filename);
    void handle() override;

private:
    std::string filename;
};

class HelpCommandHandler : public CommandHandler
{
public:
    HelpCommandHandler(Universe &universe);
    void handle() override;
};

class ExitCommandHandler : public CommandHandler
{
public:
    ExitCommandHandler(Universe &universe, bool &gameActive);
    void handle() override;

private:
    bool &gameActive;
};

#endif// COMMANDHANDLER_H
