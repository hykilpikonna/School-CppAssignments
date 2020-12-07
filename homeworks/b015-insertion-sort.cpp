//
// Created by Hykilpikonna on 11/6/20.
//
#include "iostream"

using namespace std;

// Generic function - applies to all types of arrays, not just int
// Passing in size isn't ideal here, but since all arrays are passed by pointer,
//   calling sizeof(array) would return the size of the pointer, but
//   calling sizeof(array[0]) would return the size of the actual values in the array.
//   So it is impossible to get the size of an array in a function, unless using the array<> class
//   or using the vector<> class.
template <typename T> void insertionSort(T array[], int size);

// Swap function
template <typename T> void swapVars(T& a, T& b);

int main()
{
    // Init array and output unsorted
    int array[20];
    for (int& n : array)
    {
        n = rand() % 101;
        cout << n << " ";
    }
    cout << endl;

    // Sort
    insertionSort(array, sizeof(array) / sizeof(array[0]));

    // Output sorted
    for (int n : array) cout << n << " ";
    cout << endl;

    return 0;
}

// Implementation of insertion sort
template <typename T> void insertionSort(T array[], int size)
{
    // Null safety
    if (size == 0) return;

    // Sort
    for (int i = 0; i < size; i++)
    {
        int j = i;
        while (j > 0 && array[j - 1] > array[j])
        {
            swapVars(array[j], array[j - 1]);

            j--;
        }
    }
}

// Implementation of swap
template <typename T> void swapVars(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}