//
// Created by Hykilpikonna on 12/7/20.
//

#include "utils.h"

Long pointHash(Int x, Int y)
{
    return ((Long) x << 32u) + y;
}

tuple<Int, Int> pointUnhash(Long hash)
{
    return {hash >> 32u, hash & 0xFFFFFFFF};
}

String inputLine(const String &prompt)
{
    cout << prompt;
    String input;
    getline(cin, input);
    return input;
}

int inputInt(const String &prompt)
{
    val input = inputLine(prompt);
    if (input.empty()) return 0;
    return stoi(input);
}