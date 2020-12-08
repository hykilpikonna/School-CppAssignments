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
