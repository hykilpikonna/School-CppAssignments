//
// Created by Hykilpikonna on 9/28/20.
//
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    // Input
    printf("Enter weight of package in kilograms: ");
    double weight;
    cin >> weight;

    printf("Enter length of package in meters: ");
    double length;
    cin >> length;

    printf("Enter width of package in meters: ");
    double width;
    cin >> width;

    printf("Enter height of package in meters: ");
    double height;
    cin >> height;

    // Create a list of statements
    vector<string> statements;
    if (weight < 0) statements.emplace_back("weight cannot be negative");
    else if (weight > 27) statements.emplace_back("too heavy");
    if (length < 0) statements.emplace_back("length cannot be negative");
    if (width < 0) statements.emplace_back("width cannot be negative");
    if (height < 0) statements.emplace_back("height cannot be negative");
    if (length * width * height > 0.1) statements.emplace_back("too large");

    // Meet requirements
    if (statements.empty())
    {
        printf("Accepted.");
    }
    else
    {
        // Print those statements
        printf("Rejected: ");
        for (int i = 0; i < statements.size(); i++)
        {
            // If there are multiple statements, add "and" before the last one
            if (i == statements.size() - 1 && statements.size() > 1) printf("and ");
            // Print statement/

            cout << statements[i];
            // Print comma after statement
            if (i < statements.size() - 1) printf(", ");
        }
        cout << endl;
    }

    return 0;
}