//
// Created by Hykilpikonna on 12/7/20.
//

#include "Board.h"

void Board::input(char aliveChar)
{
    cout << "Please input the board matrix (use " << aliveChar << " to indicate cells alive): " << endl;

    // Every row
    for (int row = 0; row < h; row++)
    {
        // Every char in a line
        String line = inputLine();
        for (int col = 0; col < line.length(); col++)
        {
            // Found alive cell
            if (line[col] == aliveChar) alive.emplace_back(pointHash(row, col));
        }
    }

    cout << "Input received!" << endl;
}

void Board::print()
{
    const String darkColor = "\x1b[48;5;0m\x1b[38;5;15m";
    const String lightColor = "\x1b[48;5;15m\x1b[38;5;0m";

    // Loop through all elements
    for (int row = 0; row < h; row++)
    {
        bool lastIsDead = true; // Used for coloring
        for (int col = 0; col < w; col++)
        {
            // Alive
            if (isAlive(row, col))
            {
                if (col == 0 || lastIsDead)
                {
                    lastIsDead = false;
                    cout << lightColor;
                }
            }

            // Dead
            else
            {
                if (col == 0 || !lastIsDead)
                {
                    lastIsDead = true;
                    cout << darkColor;
                }
            }

            // Output spaces
            cout << "  ";
        }
    }
}

bool Board::isAlive(Int x, Int y)
{
    // The alive array must be sorted. Use binary search to optimize.
    return binary_search(alive.begin(), alive.end(), pointHash(x, y));
}
