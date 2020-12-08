//
// Created by Hykilpikonna on 12/8/20.
//

#include "BoardWithCoins.h"

bool BoardWithCoins::isCoin(Int x, Int y)
{
    if (x < 0 || x > w) return false;
    if (y < 0 || y > h) return false;
    return binary_search(coins.begin(), coins.end(), pointHash(x, y));
}

void BoardWithCoins::print()
{
    // Output border row
    cout << borderColor << repeat("  ", w + 1) << reset << endl;

    // Loop through all elements
    for (Int row = 0; row < h; row++)
    {
        cout << borderColor << " ";
        bool lastIsDead = true; // Used for coloring
        for (Int col = 0; col < w; col++)
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
            cout << (isCoin(col, row) ? "()" : "  ");
        }

        // Reset color for the end
        cout << borderColor << " " << reset <<  endl;
    }

    // Output border row
    cout << borderColor << repeat("  ", w + 1) << reset << endl;
}
