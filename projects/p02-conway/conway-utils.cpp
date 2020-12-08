//
// Created by Hykilpikonna on 12/7/20.
//

#include "conway-utils.h"

Long pointHash(Int x, Int y)
{
    return ((Long) x << 32u) + y;
}

tuple<Int, Int> pointUnhash(Long hash)
{
    return {hash >> 32u, hash & 0xFFFFFFFF};
}

int inputInt(const string& prompt)
{
    string input;
    getline(cin, input);
    if (input.empty()) return 0;
    return stoi(input);
}