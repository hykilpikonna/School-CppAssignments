//
// Created by Hykilpikonna on 10/5/20.
//

#include <vector>
#include "iostream"

using namespace std;

// Headers
vector<int> genRow();
void printRow(vector<int> row, bool center);

/**
 * Main function
 */
int main()
{
    auto tokens = 100;

    // Keep going unless token is depleted
    while (tokens > 0)
    {
        // Prompt and take input
        printf("You have %i tokens. Pull? ", tokens);
        string input;
        getline(cin, input);

        // To lower case
        transform(input.begin(), input.end(), input.begin(), [](unsigned char c){ return tolower(c); });

        // If user doesn't want to continue.
        if (input != "y" && input != "yes" && input != "true") break;

        // Generate output
        auto dataRow = genRow();

        // Print generation results
        printf("###_###_###_###\n");
        printRow(genRow(), false);
        printRow(dataRow, true);
        printRow(genRow(), false);
        printf("###_###_###_###\n");

        // Process outcomes for 111, 222, 333
        auto oldTokens = tokens;
        for (int i = 1; i <= 3; ++i)
        {
            if (count(dataRow.begin(), dataRow.end(), i) == 3)
            {
                tokens += 4 * i;
                printf("You won %i tokens!\n\n", 4 * i);
                break;
            }
        }

        // If not incremented, say you lost.
        if (oldTokens == tokens) printf("You lost.\n\n");

        // Decrement tokens
        tokens --;
    }

    // End
    printf("Thanks for playing!");

    return 0;
}

/**
 * Generate a row of 3 integers
 * @return A list of 3 random integers from 1 to 3
 */
vector<int> genRow()
{
    vector<int> result(3);

    // Add random numbers
    for (int i = 0; i < 3; ++i)
        result[i] = rand() % 3 + 1;

    return result;
}

/**
 * Print out a row
 * @param row Data of the row
 * @param center Is it the center row?
 */
void printRow(vector<int> row, bool center)
{
    if (center)
    {
        printf("#=[%i]=[%i]=[%i]=#\n", row[0], row[1], row[2]);
    }
    else
    {
        printf("#-|%i|-|%i|-|%i|-#\n", row[0], row[1], row[2]);
    }
}