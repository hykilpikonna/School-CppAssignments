//
// Created by Hykilpikonna on 10/21/20.
//
#include "iostream"

using namespace std;

// Headers
void doubleAndHalf(double input, double& doubled, double& halved);

int main()
{
    double n, doubled, halved;

    // Take input
    cout << "Enter a number: ";
    cin >> n;

    // Call pass-by-reference function
    doubleAndHalf(n, doubled, halved);

    // Output
    printf("Your number doubled is %.2f\nYour number halved is %.2f\n", doubled, halved);

    return 0;
}

// Pass-by-reference function
void doubleAndHalf(double input, double & doubled, double & halved)
{
    doubled = input * 2;
    halved = input / 2;
}