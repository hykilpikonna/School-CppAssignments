//
// Created by Hykilpikonna on 12/7/20.
//

#include "Board.h"

Board::Board(Int w, Int h) : w(w), h(h)
{
    alive = makeList(w, h);
}

void Board::input(char aliveChar)
{
    input(0, 0, w, h, aliveChar);
}

void Board::input(Int xStart, Int yStart, Int xEnd, Int yEnd, char aliveChar)
{
    // Ask user which input method to use
    val option = inputInt("Select your input method:\n"
                          "0. Input matrix\n"
                          "1. Input alive cells\n"
                          "> ");

    switch (option)
    {
        case 0: _inputMatrix(xStart, yStart, xEnd, yEnd, aliveChar); break;
        case 1: _inputAliveLoc(xStart, yStart, xEnd, yEnd); break;
        default: cout << "What?" << endl; break;
    }

    cout << "Input received!" << endl;
}

void Board::_inputMatrix(Int xStart, Int yStart, Int xEnd, Int yEnd, char aliveChar)
{
    cout << "Please input the board matrix (use " << aliveChar << " to indicate cells alive): " << endl;

    // Every row
    for (int row = yStart; row < yEnd; row++)
    {
        // Every char in a line
        String line = inputLine();
        for (int col = xStart; col < min(Int(line.length()), xEnd); col++)
        {
            // Found alive cell
            if (line[col] == aliveChar) alive[row][col] = true;
        }
    }
}

void Board::_inputAliveLoc(Int xStart, Int yStart, Int xEnd, Int yEnd)
{
    while (true)
    {
        // Take and parse input
        val s = inputLine("Input alive location in x,y format (or empty line to end): ");
        if (s.empty()) break;
        val i = s.find(',');
        val x = stoi(s.substr(0, i));
        val y = stoi(s.substr(i + 1));

        // Validate input
        if (x < xStart || x >= xEnd || y < yStart || y >= yEnd)
        {
            cout << "Please don't go out of range :(" << endl;
            continue;
        }

        // Add input
        alive[x][y] = true;
    }
}

void Board::print()
{
    String result;

    // Output border row
    result += borderColor + repeat("  ", w + 1) + reset + "\n";

    // Loop through all elements
    for (Int y = 0; y < h; y++)
    {
        result += borderColor;
        result += " ";
        bool lastIsDead = true; // Used for coloring
        for (Int x = 0; x < w; x++)
        {
            // Alive
            if (isAlive(y, x))
            {
                if (x == 0 || lastIsDead)
                {
                    lastIsDead = false;
                    result += lightColor;
                }
            }

            // Dead
            else
            {
                if (x == 0 || !lastIsDead)
                {
                    lastIsDead = true;
                    result += darkColor;
                }
            }

            // Output spaces or coins
            result += "  ";
        }

        // Reset color for the end
        result += borderColor + String(" ") + reset + "\n";
    }

    // Output border row
    result += borderColor + repeat("  ", w + 1) + reset + "\n";

    cout << result;
}

bool Board::isAlive(Int x, Int y)
{
    if (x < 0 || x >= w) return false;
    if (y < 0 || y >= h) return false;

    // The alive array must be sorted. Use binary search to optimize.
    return alive[x][y];
}

void Board::tick() // TODO: Optimize
{
    // Create new lists
    var newAlive = makeList(w, h);

    // Add all alive points and their neighbors to check
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            // Count how many points in 9x9 are alive
            var sum = 0;
            for (var dx : {-1, 0, 1})
                for (var dy : {-1, 0, 1})
                    if (!(dx == 0 && dy == 0) && isAlive(x + dx, y + dy))
                        sum ++;

            newAlive[x][y] = shouldSurvive(isAlive(x, y), sum);
        }
    }

    // Update list
    alive = newAlive;
}
