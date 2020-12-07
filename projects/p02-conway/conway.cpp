//
// Created by Hykilpikonna on 12/7/20.
//
#include "iostream"
#include "vector"
#include "algorithm"

using namespace std;

#define Board vector<Point>

/*
 * Design notes:
 * 1. About using an array of points rather than a 2D grid:
 *   An array of alive points is more optimized for large grids
 *   because it doesn't have to check every single position on
 *   the grid when it updates. (A Board is a vector<Point>)
 */

/**
 * 2D Point class
 */
class Point
{
public:
    int x, y;
    Point(): Point(0, 0) {}
    Point(int x, int y) : x(x), y(y) {}
};

// Procedural programming: Functions for steps in a program
void startSim(int width, int height);
void startChallenge();
Board inputBoard();

// Util functions
int inputInt(const string& prompt = "");

/**
 * Main function
 *
 * @return exit code
 */
int main()
{
    // Prompt
    cout << "Welcome to Hykilp's implementation of Conway's Game of Life!\n\n"
         "Launch options:\n"
         "0: Start simulation.\n"
         "1: Try my challenge!\n";

    // Simulation
    if (inputInt() == 0)
    {
        int width = inputInt("Input your board width: ");
        int height = inputInt("Input your board height: ");
        startSim(width, height);
    }

    return 0;
}

/**
 * Start simulation
 *
 * @param width
 * @param height
 */
void startSim(int width, int height)
{

}

/**
 * Input int in a way that doesn't break getlines
 *
 * @return Int input
 */
int inputInt(const string& prompt)
{
    string input;
    getline(cin, input);
    if (input.empty()) return 0;
    return stoi(input);
}
