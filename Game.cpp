#include "Game.h"
#include <fstream>
#include <iostream>
using namespace std;

//First constructor used to take in an input file and run the game
Game::Game(string inputFile, int mode){
    ifstream input(inputFile);
    string line;
    if(!input.is_open()){
        cout << "Could not open the file." << inputFile << endl;
        exit(1);
    }
    input >> height;
    input >> width; 
    toggle = 0;

    this->mode = mode;

    Grid[0] = new char*[height];
    Grid[1] = new char*[height];
    //this getline() is to scan off the new line

    getline(input, line);
    for(int i = 0; i < height; ++i){
        Grid[0][i] = new char[width];
        Grid[1][i] = new char[width];
    }
    
    for(int row = 0; row < height; ++row){
        getline(input, line);
        for(int col = 0; col < width; ++col){
            Grid[toggle][row][col] = line[col];
        }
    }
    input.close();
}     

//Second constructor used to randomly generate a grid and run the game
Game::Game(double populationDensity, int userHeight, int userWidth, int mode){
    height = userHeight;
    width = userWidth; 
    toggle = 0;
    this->mode = mode;

    //intializing the two different grids where generations will be outputed to
    Grid[0] = new char*[height];
    Grid[1] = new char*[height];

    //creating each row of the grid
    for(int i = 0; i < height; ++i){
        Grid[0][i] = new char[width];
        Grid[1][i] = new char[width];
    }

    //randomly generating the user defined grid entries
    for(int row = 0; row < height; ++row){
        for(int col = 0; col < width; ++col){
            //generating random number between 0 and 1
            double randGeneration = (double)rand() / RAND_MAX;
            //comparing the random number to the population density
            if(randGeneration < populationDensity){
                Grid[toggle][row][col] = 'X';
            }
            else{
                Grid[toggle][row][col] = '-';
            }
        }
    }

}
    
void Game::printGrid(ostream &output){
    for(int row = 0; row < height; ++row){
        for(int col = 0; col < width; ++col){
            output << Grid[toggle][row][col];
        }
        output << endl;
    }
    output << endl;
}

int Game::classicGetNeighborCount(int row, int col){
    int neighborCount = 0;
    //Checking if all locations off the grid are empty
    for(int i = row - 1; i <= row + 1; ++i){
        for(int j = col - 1; j <= col + 1; ++j){
                if(i < 0 || j < 0 || i == height || j == width){
                    continue;
                } 
                else if(Grid[toggle][i][j] == 'X' && !(i == row && j == col)){
                    neighborCount++;
                }
        }
    }
    return neighborCount;
}

int Game::mirrorGetNeighborCount(int row, int col){
    int neighborCount = 0;
    //if a cell's location is off the grid, this bounces it back onto the grid
    for(int i = row - 1; i <= row + 1; ++i){
        for(int j = col - 1; j <= col + 1; ++j){
                int indexI;
                int indexJ;
                if(i < 0){
                    indexI = 0;
                }
                else if(i == height){
                    indexI = height - 1;
                }
                else{
                    indexI = i;
                }
                if(j < 0){
                    indexJ = 0;
                }
                else if(j == width){
                    indexJ = width - 1;
                }
                else{
                    indexJ = j;
                }
                if(Grid[toggle][indexI][indexJ] == 'X' && !(indexI == row && indexJ == col)){
                    neighborCount++;
                }
        }
    }
    return neighborCount;
}

int Game::doughnutGetNeighborCount(int row, int col){
    int neighborCount = 0;
    //checks if the cell's location is off the grid and wraps around to the opposite side
    for(int i = row - 1; i <= row + 1; ++i){
        for(int j = col - 1; j <= col + 1; ++j){
                int indexI;
                int indexJ;
                if(i < 0){
                    indexI = height - 1;
                }
                else if(i == height){
                    indexI = 0;
                }
                else{
                    indexI = i;
                }
                if(j < 0){
                    indexJ = width - 1;
                }
                else if(j == width){
                    indexJ = 0;
                }
                else{
                    indexJ = j;
                }
                if(Grid[toggle][indexI][indexJ] == 'X' && !(indexI == row && indexJ == col)){
                    neighborCount++;
                }
        }
    }
    return neighborCount;
}

int Game::getNeighborCount(int row, int col){
    int neighborCount = 0;
    //classic mode
    if(mode == 0){
        return classicGetNeighborCount(row, col);
    }
    //doughnut mode
    else if(mode == 1){
        return doughnutGetNeighborCount(row, col);
    }
    //mirror mode
    else if(mode == 2){
        return mirrorGetNeighborCount(row, col);
    }
}
        
void Game::makeGeneration(){
    //nextGen is the next generation of cell locations
    int nextGen = (toggle + 1) % 2;
    for(int row = 0; row < height; ++row){
        for(int col = 0; col < width; ++col){
            int neighborCount = getNeighborCount(row, col);
            if(neighborCount <= 1){
                Grid[nextGen][row][col] = '-';
            }
            else if(neighborCount == 2){
                Grid[nextGen][row][col] = Grid[toggle][row][col];
            }
            else if(neighborCount == 3){
                Grid[nextGen][row][col] = 'X';
            }
            else if(neighborCount >= 4){
                Grid[nextGen][row][col] = '-';
            }
        }
    }
    toggle = nextGen;
}

bool Game::isWorldEmpty(){
    //checks if the grid is empty
    for(int row = 0; row < height; ++row){
        for(int col = 0; col < width; ++col){
            if(Grid[toggle][row][col] == 'X'){
                return false;
            }
        } 
    }
    return true;
}

bool Game::isWorldStable(){
    //checks if the world is stable
    int nextGen = (toggle + 1) % 2;
    for(int row = 0; row < height; ++row){
        for(int col = 0; col < width; ++col){
            if(Grid[toggle][row][col] != Grid[nextGen][row][col]){
                return false;
            }
        } 
    }
    return true;
}