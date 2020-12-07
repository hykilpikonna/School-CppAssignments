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
    unsigned long long seed = (unsigned) time(nullptr);
    srand(seed);

    for (int i = 0; i < 10; i++)
    {
        vector<int> rands(5);
        for (int& n : rands) n = rand() % 6 + 1;
        sort(rands.begin(), rands.end());
        for (int n : rands) cout << n;
        cout << endl;
    }

    return 0;
}