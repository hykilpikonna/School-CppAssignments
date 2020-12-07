//
// Created by Hykilpikonna on 12/7/20.
//
#include "iostream"
#include "vector"
#include "algorithm"

using namespace std;

// Procedural programming: Functions for steps in a program
void startSim(int width, int height);
void startChallenge();

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
