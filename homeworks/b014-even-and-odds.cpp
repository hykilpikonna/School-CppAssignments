//
// Created by Hykilpikonna on 11/5/20.
//
#include "iostream"

using namespace std;

int main()
{
    // Setup random
    srand(time(nullptr));

    // Create an array of size 25 that will store integers.
    int array[25];

    // Fill the array with random numbers from 0 to 100 and output them all using a loop.
    for (int& n : array)
    {
        n = rand() % 101;
        cout << n << " ";
    }
    cout << endl;

    // Go through the array using another loop and count the number of even numbers & count the number of odd numbers in the array.
    int oddCount = 0;
    for (int n : array)
    {
        oddCount += n % 2; // n % 2 == 1 for odd numbers
    }

    // Output the total number evens and the total number of odds.
    cout << "The number of even numbers is " << sizeof(array) / sizeof(array[0]) - oddCount << endl;
    cout << "The number of odd numbers is " << oddCount << endl;

    return 0;
}
