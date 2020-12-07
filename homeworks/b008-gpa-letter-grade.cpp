//
// Created by Hykilpikonna on 10/2/20.
//
#include "iostream"

using namespace std;

// Headers
string toLetter(double gpa);

// Main
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
        double gpa = sum / count;
        printf("Your class average is %.3f\n", gpa);
        cout << "Your letter grade is a " << toLetter(gpa) << endl;
    }

    return 0;
}

/**
 * Convert numeric grade to letter grade
 * @param gpa Numeric average
 * @return Letter grade
 */
string toLetter(double gpa)
{
    // This grading scale is restored according to St. John's Prep's algorithm
    double minGrades[] =           {96.5, 92.5, 89.5, 86.5, 82.5, 79.5, 76.5, 72.5, 70.5, 69.5};
    string correspondingLetter[] = {"A+", "A",  "A-", "B+", "B",  "B-", "C+", "C",  "C-", "D" };

    for (int i = 0; i < sizeof(minGrades) / sizeof(double); i++)
    {
        if (gpa >= minGrades[i]) return correspondingLetter[i];
    }
    return "F";
}
