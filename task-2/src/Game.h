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
    void runOffline(int iterations, const std::string &outputFile);

private:
    bool gameActive = false;
    Universe universe;
    CommandHandler* createCommandHandler(const std::string &command);
};

#endif // GAME_H
