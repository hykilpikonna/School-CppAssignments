//
// Created by HyDEV on 9/22/20.
//
#include <iostream>

using namespace std;

int main()
{
    printf("Enter the width: ");
    double width;
    cin >> width;

    printf("Enter the height: ");
    double height;
    cin >> height;

    printf("Is this class too easy? ");
    string easy;
    cin >> easy;
    // To lower case
    transform(easy.begin(), easy.end(), easy.begin(), [](unsigned char c){ return tolower(c); });
    // Include most truthy values
    if (easy == "yes" || easy == "true" || easy == "1")
    {
        printf("Thank you, and I agree.\n");
    }

    printf("\n");

    // Actual program *facepalm*
    printf("The area is      %.2f\n", width * height);
    printf("The perimeter is %.2f\n", (width + height) * 2);

    return 0;
}

