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
    String result = "\033[2J\033[H\n";

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
            if (isAlive(x, y))
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
            result += (findCoin(pointHash(x, y)) != -1 ? "()" : "  ");
        }

        // Reset color for the end
        result += borderColor + String(" ") + reset + "\n";
    }

    // Output border row
    result += borderColor + repeat("  ", w + 1) + reset + "\n";

    cout << result;
}

Int BoardWithCoins::tickWithCoins()
{
    var sum = 0;
    tick();

    for (val a : alive)
    {
        val i = findCoin(a);
        if (i != -1)
        {
            sum ++;

            // Remove coin: `coins` will remain sorted.
            coins.erase(coins.begin() + i);
        }
    }

    return sum;
}

void BoardWithCoins::fillCoins(Int xs, Int ys, Int xEnd, Int yEnd, Int step)
{
    for (Int x = xs; x < xEnd; x += step)
    {
        for (Int y = ys; y < yEnd; y += step)
        {
            coins.emplace_back(pointHash(x, y));
        }
    }
    sort(coins.begin(), coins.end());
}
