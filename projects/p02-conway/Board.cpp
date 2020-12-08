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
        for (int col = 0; col < min(Int(line.length()), w); col++)
        {
            // Found alive cell
            if (line[col] == aliveChar) alive.emplace_back(pointHash(row, col));
        }
    }

    // Sort new alive list
    sort(alive.begin(), alive.end());

    cout << "Input received!" << endl;
}

void Board::print()
{
    val darkColor = "\x1b[48;5;0m\x1b[38;5;15m";
    val lightColor = "\x1b[48;5;15m\x1b[38;5;0m";
    val borderColor = "\x1b[48;5;11m";
    val reset = "\x1b[0m";

    // Output border row
    cout << borderColor;
    for (int col = 0; col < w + 1; col++) cout << "  ";
    cout << reset << endl;

    // Loop through all elements
    for (int row = 0; row < h; row++)
    {
        cout << borderColor << " ";
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

        // Reset color for the end
        cout << borderColor << " " << reset <<  endl;
    }

    // Output border row
    cout << borderColor;
    for (int col = 0; col < w + 1; col++) cout << "  ";
    cout << reset << endl;
}

bool Board::isAlive(Int x, Int y)
{
    return isAlive(pointHash(x, y));
}

bool Board::isAlive(Long point)
{
    // The alive array must be sorted. Use binary search to optimize.
    return binary_search(alive.begin(), alive.end(), point);
}
