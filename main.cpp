/*
    Shane Rodricks
    2343774
    rodricks@chapman.edu
    CPSC350-Section 2
    Assignment 3
*/
#include "Game.h"
#include <iostream>
#include <fstream>
using namespace std;


int main(int argc, char** argv)
{
    Game *g;
    string input;
    int mode;
    int userChoice;
    double populationDensity;
    int userHeight;
    int userWidth;
    int userOutput;
    string outputFileName;

    //program starts by asking user which mode they would like to play in
    cout << "Enter the number of which mode you would like to play in:\n"
            "- Classic: 0\n"
            "- Doughnut: 1\n"
            "- Mirror: 2" << endl;
    cin >> mode;
    getline(cin, input);
    
    //asks user if they have a file ready or want a randomly generated one
    cout << "To play with a premade file: Type 0\n" 
            "To play with a randomly generated grid: Type 1\n"<< endl;
    cin >> userChoice;
    getline(cin, input);

    //checks if user has a file ready, takes in the input file
    if(userChoice == 0){
        cout << "Enter input file name: " << endl;
        getline(cin, input);
        g = new Game(input, mode);
    }
    //else, creates a randomly generated grid based off user inputed dimensions and population density
    else{
        cout << "Enter the height for the grid: " << endl;
        cin >> userHeight;
        getline(cin, input);
        cout << "Enter the width for the grid: " << endl;
        cin >> userWidth;
        getline(cin, input);
        cout << "Enter the population density (a decimal number between 0 and 1): " << endl;
        cin >> populationDensity;
        getline(cin, input);
        g = new Game(populationDensity, userHeight, userWidth, mode);
    }

    //checks if the user wants grids outputted to console or new output file
    cout << "To play with a brief pause in between generations: Type 0\n"
            "To output each generation to a separate file: Type 1\n" << endl;
    cin >> userOutput;
    getline(cin, input);
    ofstream output;
    //asks user for output file name if they chose to do so
    if(userOutput == 1){
        cout << "Enter output file name: " << endl;
        getline(cin, outputFileName);
        output.open(outputFileName);
        if(!output.is_open()){
            cout << "Could not open the file." << outputFileName << endl;
            exit(1);
        }
        g->printGrid(output);
    }
    //else just prints grid to console
    else{
        g->printGrid(cout);
    }
    //checks if the world is empty or stable, if not make new generation
    while(!(g->isWorldEmpty() || g->isWorldStable())){
        g->makeGeneration();
        if(userOutput == 1){
            g->printGrid(output);
        }
        else{
            cout << "Press 'Enter' to continue: " << endl;
            cin.get();
            g->printGrid(cout);
        }
    }
    if(userOutput == 1){
            output.close();
        }
    return 0;   
}