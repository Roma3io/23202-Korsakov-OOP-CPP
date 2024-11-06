#ifndef GAME_H
#define GAME_H

#include "CommandHandler.h"
#include "Universe.h"

class Game
{
public:
    Game(const std::string &name, const std::string &rule, int width, int height);
    Game(const std::string &filename);
    void start();

private:
    Universe universe;
    CommandHandler commandHandler;
};

#endif // GAME_H
