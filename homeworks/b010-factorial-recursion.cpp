//
// Created by Hykilpikonna on 10/20/20.
//
#include "iostream"

using namespace std;

unsigned long long factorial(int x);

int main()
{
    cout << "Enter in a number you want to take the factorial of: ";
    int x;
    cin >> x;

    printf("%i! = %llu", x, factorial(x));

    return 0;
}

// Using unsigned long long to expand the maximum to 65!
unsigned long long factorial(int x)
{
    if (x == 1) return 1;
    return x * factorial(x - 1);
}