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

}