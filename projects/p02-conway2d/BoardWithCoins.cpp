//
// Created by Hykilpikonna on 12/8/20.
//

#include "BoardWithCoins.h"

BoardWithCoins::BoardWithCoins(Int w, Int h) : Board(w, h)
{
    coins = makeList(w, h);
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
            result += coins[y][x] ? "()" : "  ";
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

    for (Int y = 0; y < h; y++)
    {
        for (Int x = 0; x < w; x++)
        {
            if (alive[x][y] && coins[x][y])
            {
                sum ++;
                coins[x][y] = false;
            }
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
            coins[x][y] = true;
        }
    }
}
