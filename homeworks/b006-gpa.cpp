//
// Created by Hykilpikonna on 10/2/20.
//
#include "iostream"

using namespace std;

int main()
{
    double sum = 0;
    int count = 0;

    while (true)
    {
        // Take input (Using 101 as end of input is a terrible idea,
        //   because 101 could be an actual grade if extra credit is given)
        printf("Enter your grade or enter 'done' or '101' to finish: ");
        string input;
        cin >> input;

        // To lower case
        transform(input.begin(), input.end(), input.begin(),
                  [](unsigned char c){ return tolower(c); });

        // Check input
        if (input == "done" || input == "101") break;

        // Parse input to double
        double grade = strtod(input.c_str(), nullptr);

        // Add to sum
        sum += grade;
        count ++;
    }

    if (count == 0)
    {
        // NaN case
        printf("What? Your class average is 0, get out of here!");
    }
    else
    {
        // Print average
        printf("Your class average is %.3f", sum / count);
    }

    return 0;
}


