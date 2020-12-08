//
// Created by Hykilpikonna on 12/7/20.
//
#include "iostream"
#include "vector"
#include "map"
#include "unordered_map"
#include "algorithm"
#include "cstdint"
#include "tuple"

using namespace std;

// Terrible C stuff: int is only 16-bits on LP32
#define Int uint32_t
#define Long uint64_t

/*
 * Design notes:
 * 1. About using an array of points rather than a 2D grid:
 *   An array of alive points is more optimized for large grids
 *   because it doesn't have to check every single position on
 *   the grid when it updates.
 */

/**
 * Convert a position into one long number, with the first 32
 * bits being the bits from the first int32, and the next 32
 * bits being the bits from the second int32.
 *
 * @param x Position X (Positive).
 * @param y Position Y (Positive).
 * @return Long number.
 */
Long pointHash(Int x, Int y)
{
    return ((Long) x << 32u) + y;
}

/**
 * Convert the long number back to the position.
 *
 * @param hash Long number
 * @return Position X and Y
 */
tuple<Int, Int> pointUnhash(Long hash)
{
    return {hash >> 32u, hash & 0xFFFFFFFF};
}

/**
 * A board contains an array of alive points
 */
class Board
{
public:
    vector<Long> alive;


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
