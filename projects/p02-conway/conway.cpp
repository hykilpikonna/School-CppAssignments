//
// Created by Hykilpikonna on 12/7/20.
//

#include "conway.h"

int main(int argc, char* argv[])
{
    // Check params
    if (argc > 1)
    {
        // Run tests
        if (string(argv[1]) == "test")
        {
            runTests();
            return 0;
        }
    }

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

void runTests()
{
    // Point: Hash and unhash
    assert(pointHash(5, 1) == 21474836481);
    auto [x, y] = pointUnhash(21474836481);
    assert(x == 5 && y == 1);
}

void startSim(int width, int height)
{

}