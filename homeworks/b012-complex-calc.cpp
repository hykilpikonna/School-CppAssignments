//
// Created by Hykilpikonna on 10/23/20.
//
#include "iostream"
#include "cmath"

using namespace std;

void println(const string& text);
void takeInput(double& inputReal, double& inputImag);
void printComplex(const double& real, const double& imag);
void add(double& a, double& b, const double& c, const double& d);
void subtract(double& a, double& b, const double& c, const double& d);
void multiply(double& a, double& b, const double& c, const double& d);
void divide(double& a, double& b, const double& c, const double& d);
double calculateMagnitude(const double& a, const double& b);

int main()
{
    double a = 0; // keeps track of the current real value
    double b = 0; // keeps track of the current imaginary value
    double c = 0; // the real value to +, -, *, or /
    double d = 0; // the imaginary value to +, -, *, or /

    cout << "Welcome to the Complex Number Calculator!" << endl;
    cout << "Here are your options: " << endl;
    cout << "+ (addition)" << endl;
    cout << "- (subtraction)" << endl;
    cout << "* (multiplication)" << endl;
    cout << "/ (division)" << endl;
    cout << "l (length)" << endl;
    cout << "i (new input)" << endl;
    cout << "q (quit)" << endl << endl;

    while(true)
    {
        printf("Enter what you want to do: ");
        char choice;
        cin >> choice;

        switch(choice)
        {
            case 'i': // New input (reset current value)
            {
                a = b = 0;
                break;
            }
            case '+': // Add
            {
                takeInput(c, d);
                add(a, b, c, d);
                break;
            }
            case '-': // Subtract
            {
                takeInput(c, d);
                subtract(a, b, c, d); // Adding a negative is subtracting
                break;
            }
            case '*':
            {
                takeInput(c, d);
                multiply(a, b, c, d);
                break;
            }
            case '/':
            {
                takeInput(c, d);
                divide(a, b, c, d);
                break;
            }
            case 'l':
            {
                printf("The length is %.2f\n", calculateMagnitude(a, b));
                break;
            }
            case 'q':
            {
                println("Thanks for using our calculator!");
                return 0;
            }
            default:
            {
                println("Not a valid choice!");
                break;
            }
        }

        printComplex(a, b);
    }
}

// Just for the sake of I can't stand using cout << endl.
void println(const string& text)
{
    cout << text << endl;
}

/**
 * Take a complex number input
 * @param inputReal
 * @param inputImag
 */
void takeInput(double& inputReal, double& inputImag)
{
    printf("Enter real part: ");
    cin >> inputReal;
    printf("Enter imaginary part: ");
    cin >> inputImag;
}

/**
 * Print out an imaginary number
 * @param real
 * @param imag
 */
void printComplex(const double& real, const double& imag)
{
    printf("- Current value: %.2f + %.2fi\n\n", real, imag);
}

/**
 * Add two complex numbers and store the result in the first complex number
 * @param a Real part of the first complex
 * @param b Imag part of the first complex
 * @param c Real part of the second complex
 * @param d Imag part of the second complex
 */
void add(double& a, double& b, const double& c, const double& d)
{
    a += c;
    b += d;
}
void subtract(double& a, double& b, const double& c, const double& d)
{ add(a, b, -c, -d); }

/**
 * Multiply two complex numbers and store the result in the first complex number
 * @param a Real part of the first complex
 * @param b Imag part of the first complex
 * @param c Real part of the second complex
 * @param d Imag part of the second complex
 */
void multiply(double& a, double& b, const double& c, const double& d)
{
    auto newA = a * c - b * d;
    b = b * c + a * d;
    a = newA;
}

/**
 * Divide the first complex number by the second and store the result in the first complex number
 * @param a Real part of the first complex
 * @param b Imag part of the first complex
 * @param c Real part of the second complex
 * @param d Imag part of the second complex
 */
void divide(double& a, double& b, const double& c, const double& d)
{
    auto divider = (c * c + d * d);
    auto newA = (a * c + b * d) / divider;
    b = (b * c - a * d) / divider;
    a = newA;
}

/**
 * Calculate the magnitude of the complex number
 * @param a Real part
 * @param b Imag part
 * @return Magnitude
 */
double calculateMagnitude(const double& a, const double& b)
{
    return sqrt(a * a + b * b);
}