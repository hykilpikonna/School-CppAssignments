//
// Created by Hykilpikonna on 12/4/20.
//
#include "iostream"
#include "iomanip"
#include "numeric"

using namespace std;

int main()
{
    srand((unsigned) time(nullptr));

    // creates a 2D array that is 10 by 10
    int len = 10;
    int array[len][len];

    // Assign random numbers and output them
    for (int x = 0; x < len; x++)
    {
        for (int y = 0; y < len; y++)
        {
            // fill the array with random numbers from 0-100
            array[x][y] = rand() % 101;

            // output the array
            cout << setw(4) << array[x][y];
        }
        cout << endl;
    }
    cout << endl;

    // Print sums of each row
    cout << "Sums of each row: " << endl;
    for (int x = 0; x < len; x++)
    {
        // calculate the sum of each row
        cout << accumulate(array[x], array[x] + len, 0) << endl;
    }

    return 0;
}