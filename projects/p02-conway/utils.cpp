//
// Created by Hykilpikonna on 12/7/20.
//

#include "utils.h"

Long pointHash(Int x, Int y)
{
    return ((Long) x << 32u) + y;
}

tuple<Int, Int> pointUnhash(Long hash)
{
    return {hash >> 32u, hash & 0xFFFFFFFF};
}

String inputLine(const String &prompt)
{
    cout << prompt;
    String input;
    getline(cin, input);
    return input;
}

int inputInt(const String &prompt)
{
    val input = inputLine(prompt);
    if (input.empty()) return 0;
    return stoi(input);
}

bool shouldSurvive(bool currentAlive, Int aliveNeighbors)
{
    if (currentAlive)
    {
        // 1. Any live cell with fewer than two live neighbours dies,
        //   as if by underpopulation

        // 2. Any live cell with two or three live neighbours lives
        //   on to the next generation.
        if (aliveNeighbors == 2 || aliveNeighbors == 3) return true;

        // 3. Any live cell with more than three live neighbours dies,
        //   as if by overpopulation.
    }
    else
    {
        // 4. Any dead cell with exactly three live neighbours becomes
        //   a live cell, as if by reproduction.
        if (aliveNeighbors == 3) return true;
    }

    return false;
}