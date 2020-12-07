//
// Created by Hykilpikonna on 10/1/20.
//
#include <iostream>

using namespace std;

int main()
{
    while (true)
    {
        // Input
        printf("Enter your model number (0 for done): ");
        int input;
        cin >> input;

        // Process input
        switch (input)
        {
            case 0:
                printf("Program complete.\n");
                return 0;
            case 119: case 179: case 189 ... 195: case 221: case 780:
                printf("Your car is defective. Please have it fixed.\n");
                break;
            default:
                printf("Your car is 0K\n");
                break;
        }
    }
}