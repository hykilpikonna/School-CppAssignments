//
// Created by Hykilpikonna on 10/15/20.
//
#include "iostream"

using namespace std;

// Headers
string giveHint(int secret, int guess);

int main()
{
    // Secret will store a random number between 1 and 100
    srand((unsigned) time(nullptr));
    int secret = rand() % 99 + 1;
    int count = -1;
    int guess;

    cout << "Welcome to the guessing game. In this game, you will have to guess a number between 1 and 100 inclusive." << endl;

    // The user will keep inputting a guess until the guess matches the secret
    do
    {
        cout << "Please take a guess between 1 and 100: ";
        cin >> guess;

        // Print hint / complete
        cout << giveHint(secret, guess) << endl;

        // Increment count
        count ++;
    }
    while (guess != secret);

    printf("Thanks for playing! It took you %i tries.\n", count);
    return 0;
}

/**
 * You will write a function called giveHint that is passed 2 integers (i.e. has two parameters)
 * @param secret Secret number
 * @param guess Current guess
 * @return Hint
 */
string giveHint(int secret, int guess)
{
    if (guess < 1) return "Your guess should not be lower than 1.";
    if (guess > 100) return "Your guess should not be greater than 100.";
    if (guess > secret) return "Too high! Try again!";
    if (guess < secret) return "Too low! Try again!";
    return "You got it!";
}