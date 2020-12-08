//
// Created by Hykilpikonna on 12/7/20.
//

#include "conway.h"

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