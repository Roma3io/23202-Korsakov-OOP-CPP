#include "../src/Game.h"
#include "gtest/gtest.h"
#include <fstream>

TEST(Game, FieldIsToroidal)
{
    std::ofstream outfile("Blinker.txt");
    outfile << "#N Blinker\n";
    outfile << "#R B3/S23\n";
    outfile << "#S 10 10\n";
    outfile << "0 0\n";
    outfile << "1 0\n";
    outfile << "2 0\n";
    outfile.close();
    Game game("Blinker.txt");
    game.runOffline(1, "OnePeriod.txt");
    std::ifstream infile("OnePeriod.txt");
    std::string line;
    std::vector<std::pair<int, int>> liveCells;
    while (std::getline(infile, line)) {
        if (line[0] == '#') {
            continue;
        }
        int row, col;
        std::istringstream iss(line);
        iss >> row >> col;
        liveCells.push_back(std::make_pair(row, col));
    }
    infile.close();
    EXPECT_TRUE(std::find(liveCells.begin(), liveCells.end(), std::make_pair(1, 9)) != liveCells.end());
    EXPECT_TRUE(std::find(liveCells.begin(), liveCells.end(), std::make_pair(1, 0)) != liveCells.end());
    EXPECT_TRUE(std::find(liveCells.begin(), liveCells.end(), std::make_pair(1, 1)) != liveCells.end());
}

TEST(Game, RulesOfLife)
{
    std::ofstream outfile("RulesOfLife.txt");
    outfile << "#N Rules of Life\n";
    outfile << "#R B3/S23\n";
    outfile << "#S 10 10\n";
    outfile << "1 1\n";
    outfile << "1 2\n";
    outfile << "1 3\n";
    outfile << "2 2\n";
    outfile << "3 1\n";
    outfile << "3 2\n";
    outfile << "3 3\n";
    outfile.close();
    Game game("RulesOfLife.txt");
    game.runOffline(1, "RulesOfLifeUpdated.txt");
    std::ifstream infile("RulesOfLifeUpdated.txt");
    std::string line;
    std::vector<std::pair<int, int>> liveCells;
    while (std::getline(infile, line)) {
        if (line[0] == '#') {
            continue;
        }
        int row, col;
        std::istringstream iss(line);
        iss >> row >> col;
        liveCells.push_back(std::make_pair(row, col));
    }
    infile.close();
    EXPECT_TRUE(std::find(liveCells.begin(), liveCells.end(), std::make_pair(1, 1)) != liveCells.end());
    EXPECT_TRUE(std::find(liveCells.begin(), liveCells.end(), std::make_pair(1, 2)) != liveCells.end());
    EXPECT_TRUE(std::find(liveCells.begin(), liveCells.end(), std::make_pair(1, 3)) != liveCells.end());
    EXPECT_TRUE(std::find(liveCells.begin(), liveCells.end(), std::make_pair(0, 2)) != liveCells.end());
    EXPECT_TRUE(std::find(liveCells.begin(), liveCells.end(), std::make_pair(3, 1)) != liveCells.end());
    EXPECT_TRUE(std::find(liveCells.begin(), liveCells.end(), std::make_pair(3, 2)) != liveCells.end());
    EXPECT_TRUE(std::find(liveCells.begin(), liveCells.end(), std::make_pair(3, 3)) != liveCells.end());
    EXPECT_TRUE(std::find(liveCells.begin(), liveCells.end(), std::make_pair(4, 2)) != liveCells.end());
}


TEST(Game, ImmortalCells)
{
    std::ofstream outfile("ImmortalCells.txt");
    outfile << "#N Immortal Cells\n";
    outfile << "#R B3/S012345678\n";
    outfile << "#S 10 10\n";
    outfile << "1 1\n";
    outfile << "1 2\n";
    outfile << "1 3\n";
    outfile << "2 2\n";
    outfile << "3 1\n";
    outfile << "3 2\n";
    outfile << "3 3\n";
    outfile.close();
    Game game("ImmortalCells.txt");
    game.runOffline(1, "ImmortalCellsUpdated.txt");
    std::ifstream infile("ImmortalCellsUpdated.txt");
    std::string line;
    std::vector<std::pair<int, int>> liveCells;
    while (std::getline(infile, line)) {
        if (line[0] == '#') {
            continue;
        }
        int row, col;
        std::istringstream iss(line);
        iss >> row >> col;
        liveCells.push_back(std::make_pair(row, col));
    }
    infile.close();
    EXPECT_TRUE(std::find(liveCells.begin(), liveCells.end(), std::make_pair(0, 2)) != liveCells.end());
    EXPECT_TRUE(std::find(liveCells.begin(), liveCells.end(), std::make_pair(1, 1)) != liveCells.end());
    EXPECT_TRUE(std::find(liveCells.begin(), liveCells.end(), std::make_pair(1, 2)) != liveCells.end());
    EXPECT_TRUE(std::find(liveCells.begin(), liveCells.end(), std::make_pair(1, 3)) != liveCells.end());
    EXPECT_TRUE(std::find(liveCells.begin(), liveCells.end(), std::make_pair(2, 2)) != liveCells.end());
    EXPECT_TRUE(std::find(liveCells.begin(), liveCells.end(), std::make_pair(3, 1)) != liveCells.end());
    EXPECT_TRUE(std::find(liveCells.begin(), liveCells.end(), std::make_pair(3, 2)) != liveCells.end());
    EXPECT_TRUE(std::find(liveCells.begin(), liveCells.end(), std::make_pair(3, 3)) != liveCells.end());
    EXPECT_TRUE(std::find(liveCells.begin(), liveCells.end(), std::make_pair(4, 2)) != liveCells.end());
}
