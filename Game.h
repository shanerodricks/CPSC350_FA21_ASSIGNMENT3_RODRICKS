/*
    Shane Rodricks
    2343774
    rodricks@chapman.edu
    CPSC350-Section 2
    Assignment 3
*/
#ifndef GAME_H
#define GAME_H
#include <string>
using namespace std;

class Game{
    private:
        char** Grid[2];
        int toggle;
        int height;
        int width;
        int mode;
        int getNeighborCount(int row, int col);
        int classicGetNeighborCount(int row, int col);
        int mirrorGetNeighborCount(int row, int col);
        int doughnutGetNeighborCount(int row, int col);
    public:
        Game(string inputFile, int mode);
        Game(double populationDensity, int userHeight, int userWidth, int mode);
        void printGrid(ostream &output);
        void makeGeneration();
        bool isWorldEmpty();
        bool isWorldStable();
};

#endif