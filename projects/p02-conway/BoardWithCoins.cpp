//
// Created by Hykilpikonna on 12/8/20.
//

#include "BoardWithCoins.h"

int BoardWithCoins::findCoin(Long hash) const
{
    return binarySearchIndexOf(coins, hash);
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

            // Output spaces or coins
            cout << (findCoin(pointHash(col, row)) != -1 ? "()" : "  ");
        }

        // Reset color for the end
        cout << borderColor << " " << reset <<  endl;
    }

    // Output border row
    cout << borderColor << repeat("  ", w + 1) << reset << endl;
}
