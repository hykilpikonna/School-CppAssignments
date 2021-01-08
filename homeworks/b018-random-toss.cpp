//
// Created by Hykilpikonna on 1/4/21.
//
#include "iostream"

using namespace std;

#define val const auto

// Configuration
#define text(b) (b ? "💰 " : "-- ")
val w = 5;
val h = 5;
val moneyBags = 3;

// Main function
int main()
{
    // Init grid
    srand(time(nullptr)); // NOLINT(cert-msc51-cpp)
    bool grid[w][h] = {false};

    // Throw money bags
    for (int i = 0; i < moneyBags; i++)
    {
        val x = (int) rand() % w;
        val y = (int) rand() % h;

        // Already exists, roll again
        if (grid[x][y])
        {
            i--;
            continue;
        }

        // Throw it
        grid[x][y] = true;
    }

    // Print outputs
    for (val & row : grid)
    {
        for (bool value : row)
        {
            cout << text(value);
        }
        cout << endl;
    }

    return 0;
}