//
// Created by Hykilpikonna on 10/21/20.
//
#include "iostream"
#include <cstdint>
#include <iomanip>
#define long int64_t

using namespace std;

long elder_age(long m, long n, long l, long t)
{
    long sum = 0;
    for (long row = 1; row < m; row++)
    {
        for (long col = 0; col < row; col++)
        {
            long val = (row ^ col);
            if (val != 1) val = val * 4 - 2;
            val -= l;
            val = val > 0 ? val : 0;
            std::cout << val << ",";
            sum = (sum + val) % t;
        }
        std::cout << std::endl;
    }
    return sum;
}

int main()
{
    elder_age(256, 256, 0, 1u << sizeof(long));
}
