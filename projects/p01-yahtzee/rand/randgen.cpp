//
// Created by Hykilpikonna on 11/17/20.
//
#include "iostream"
#include "iomanip"
#include "algorithm"
#include "vector"
#include "map"

using namespace std;

int main()
{
    unsigned long long seed = 1605645479;
    srand(seed);

    for (int i = 0; i < 100; i++)
    {
        cout << rand() % 6 + 1 << endl;
    }

    return 0;
}