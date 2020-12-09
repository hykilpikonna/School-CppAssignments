//
// Created by Hykilpikonna on 12/8/20.
//

#include "crack.h"

bool isBit(Long n, Long k)
{
    return (n & (1ull << k)) != 0;
}

void crack()
{
    var maxCoins = 0;

    // Loop through all combinations in 8x8
    for (Long i = 0; i < 1ull << 63u; i++)
    {
        // Create challenge board
        var board = BoardWithCoins(50, 50);
        board.fillCoins(0, 16, 50, 50, 2);
        board.fillCoins(16, 0, 50, 50, 2);

        // Fill combination
        for (int b = 0; b < 63; b++)
        {
            int row = b / 8;
            int col = b % 8;

            if (isBit(i, b)) board.alive[15 - row][15 - col] = true;
        }

        // Test board
        var coins = 0;
        var coinsDidntChange = 0;
        while (true)
        {
            val get = board.tickWithCoins();
            coins += get;

            if (get == 0) coinsDidntChange++;
            else coinsDidntChange = 0;

            if (coinsDidntChange > 15) break;
            if (board.alive.empty()) break;
        }

        if (coins > maxCoins)
        {
            maxCoins = coins;
            cout << "New max found! " << maxCoins << " coins - " << i << endl;
        }
    }
}