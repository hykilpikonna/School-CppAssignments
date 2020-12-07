//
// Created by Hykilpikonna on 11/16/20.
//
#include "iostream"
#include "iomanip"
#include "algorithm"
#include "vector"
#include "map"

using namespace std;

// ANSI color constants
namespace colors
{
    const string RED = "\033[31m";
    const string GREEN = "\033[32m";
    const string YELLOW = "\033[33m";
    const string BLUE = "\033[34m";
    const string PURPLE = "\033[35m";
    const string CYAN = "\033[36m";
    const string BOLD = "\033[1m";
    const string UNDERLINE = "\033[4m";
    const string CLEAR = "\033[0m";
    const string cendl = CLEAR + "\n"; // Clear color first then cendl

    // Clear screen https://stackoverflow.com/questions/37774983/clearing-the-screen-by-printing-a-character
    const string CLEAR_SCREEN = "\033[2J\033[H";
}

using namespace colors;

// Function declarations
vector<int> rollOneTurn();
vector<int> calculatePossibleScores(const vector<int>& keepers, const vector<int>& currentScores);
void printScores(const vector<int>& scores, bool current);
int totalScore(const vector<int>& scores, int bonuses);

int inputInt();
template <typename T> void sort(vector<T>& array);
template <typename T> string join(const vector<T>& array, const string& separator = ", ", const string& pre = "[", const string& post = "]");
int sum(const vector<int>& array);
vector<int> countOccurrences(const vector<int>& array);

bool isNOfAKind(const vector<int>& array, int n, bool strict = false);
bool isNOfAKindWithOccurrences(const vector<int>& occurrences, int n, bool strict = false);
int getMaxStraight(vector<int> array);

bool isThreeOfAKind(const vector<int>& a);
bool isFourOfAKind(const vector<int>& a);
bool isYahtzee(const vector<int>& a);
bool isFullHouse(const vector<int>& a);

bool isSmallStraight(const vector<int>& array);
bool isLargeStraight(const vector<int>& array);

// Scoring names
const string SCORE_NAMES[] = {
        "YAHTZEE Bonus", // 0 (not an actual spot)
        "Upper - Aces", // 1
        "Upper - Twos", // 2
        "Upper - Threes", // 3
        "Upper - Fours", // 4
        "Upper - Fives", // 5
        "Upper - Sixes", // 6
        "Lower - 3-of-a-Kind", // 7
        "Lower - 4-of-a-Kind", // 8
        "Lower - Full House", // 9
        "Lower - Small Straight", // 10
        "Lower - Large Straight", // 11
        "Lower - YAHTZEE", // 12
        "Lower - Chance", // 13
};

// Main
int main()
{
    // Init PRNG seed
    srand((unsigned) time(nullptr)); // NOLINT(cert-msc51-cpp)

    // Create a list storing current grids of scores and init them with -1
    vector<int> scores(14);
    for (int& s : scores) s = -1;
    int bonuses = 0; // YAHTZEE bonus for scoring multiple YAHTZEE

    // Initial clear screen
    cout << CLEAR_SCREEN;

    // While the game hasn't ended (every spot excepts for 0 is -1)
    while (!all_of(scores.begin() + 1, scores.end(), [](int n){ return n != -1; }))
    {
        // Roll one turn
        auto keepers = rollOneTurn();

        // Get possible scores
        auto possibleScores = calculatePossibleScores(keepers, scores);

        // Print possible scores
        cout << PURPLE << "Here are your possible scores: " << cendl;
        printScores(possibleScores, false);

        // Take input
        int input;
        while (true)
        {
            cout << endl << YELLOW << "-> Which spot do you want to fill?" << cendl << "> ";
            input = inputInt();

            // Player trying to cheat
            if (possibleScores[input] == -1)
            {
                cout << RED << "That's not an option, try again." << cendl;
            }
            else break;
        }

        // Register score
        cout << CLEAR_SCREEN;
        if (input == 0)
        {
            bonuses++;
            cout << GREEN << "You scored a bonus of 100!" << cendl;
        }
        else
        {
            scores[input] = possibleScores[input];
            cout << GREEN << "You scored a " << scores[input] << " on " << SCORE_NAMES[input] << "!" << cendl;
        }

        // Print new scoreboard
        cout << PURPLE + BOLD << "Your new scoreboard: " << cendl;
        printScores(scores, true);
        cout << PURPLE << "-- Total: " << totalScore(scores, bonuses) << cendl << endl;

        // Pause
        cout << YELLOW << "-> Press Enter to Continue" << cendl;
        cin.ignore();
        cout << CLEAR_SCREEN;
    }

    cout << CLEAR_SCREEN;
    cout << GREEN + BOLD << "Your final scoreboard: " << cendl;
    printScores(scores, true);
    if (bonuses > 0)
    {
        cout << GREEN + BOLD << " + Bonus! " << bonuses << " * 100" << cendl;
    }
    cout << endl;
    cout << GREEN + BOLD << "Thanks for playing! Your total score is " << totalScore(scores, bonuses) << cendl;

    return 0;
}

/**
 * Roll one turn (max 3 rolls)
 *
 * @return The keepers that the player chosen
 */
vector<int> rollOneTurn()
{
    vector<int> keepers;

    // The player has three rolls each turn
    for (int rolls = 0; rolls < 3; rolls++)
    {
        // Init array with 5 elements
        vector<int> tableDices(5 - keepers.size());

        // Fill array with random numbers from 1 to 6
        cout << BOLD + CYAN << "*Rolls dice*" << cendl;
        for (int& i : tableDices)
            i = rand() % 6 + 1; // NOLINT(cert-msc50-cpp)

        // Sort array
        sort(tableDices);

        // Print sorted random array
        cout << "Your keepers are: " << BOLD + GREEN << join(keepers) << cendl;
        cout << "You have rolled:  " << BOLD + CYAN << join(tableDices) << cendl;

        // End of three rolls, must keep every dice
        if (rolls == 2)
        {
            for (int i : tableDices) keepers.push_back(i);
            cout << CLEAR_SCREEN;
            cout << BOLD + PURPLE << "Your three rolls are finished." << cendl;

            // I know it's a "bad practice" to use goto, but using breaks here is less clear.
            goto end;
        }

        // Ask player which one to keep
        while (true)
        {
            cout << endl << YELLOW << "-> Do you want to keep any dice?" <<
                CLEAR << " (Input the dice result you want to keep / 10 to keep all / 0 to continue) " << cendl << "> ";
            int input = inputInt();

            // Continue
            if (input == 0) break;

            // Keep all
            if (input == 10)
            {
                for (int i : tableDices) keepers.push_back(i);
                break;
            }

            // Find the index of the input
            auto indexPos = find(tableDices.begin(), tableDices.end(), input);

            // Element is not found
            if (indexPos == tableDices.end())
            {
                cout << RED << "The dice of " << input << " is not on the table." << cendl;
                continue;
            }

            // Move the number from randoms to keepers
            int n = tableDices[indexPos - tableDices.begin()];
            keepers.push_back(n);
            tableDices.erase(indexPos);

            // Sort
            sort(keepers);

            // Print keep message
            cout << CLEAR_SCREEN;
            cout << GREEN << "You kept " << n << CLEAR << " | Now your keepers are: " << BOLD + GREEN << join(keepers) << cendl;

            // No dices left on the table
            if (tableDices.empty())
            {
                cout << CLEAR_SCREEN;
                cout << BOLD + PURPLE << "You have no dices left on the table." << cendl;

                goto end;
            }

            // Print dices left
            cout << "Your remaining dices on the table: " << BOLD + CYAN << join(tableDices) << cendl;
        }

        // Not the end of three rolls but already kept all the dices
        if (keepers.size() == 5)
        {
            cout << CLEAR_SCREEN;
            cout << BOLD + PURPLE << "You ended your turn on your roll #" << rolls + 1 << cendl;

            goto end;
        }

        cout << CLEAR_SCREEN;
    }

    end:

    // Print final keepers
    sort(keepers);
    cout << BOLD + GREEN << "Your final keepers: " << join(keepers) << cendl << endl;

    return keepers;
}

/**
 * Get a map of possible scores
 *
 * @param keepers The keepers that the player rolled and chose
 * @param currentScores Current scores (to avoid duplicates)
 * @return Map of possible, non-duplicate scores
 */
vector<int> calculatePossibleScores(const vector<int>& keepers, const vector<int>& currentScores)
{
    // Create result scores
    vector<int> results(14);
    for (int& s : results) s = 0;
    results[0] = -1;

    // Calculate occurrences
    auto occurrences = countOccurrences(keepers);

    // Upper section
    for (int i = 1; i <= 6; i++) results[i] = occurrences[i] * i;

    // Lower section not-affected by joker rules
    results[13] = sum(keepers); // Chance
    if (isYahtzee(keepers)) results[12] = 50;

    // JOKER RULES! WHY DO YOU EXIST??!
    bool joker = currentScores[12] == 0 && results[12] == 50;

    // Lower section affected by joker rules
    if (joker || isLargeStraight(keepers)) results[11] = 40;
    if (joker || isSmallStraight(keepers)) results[10] = 30;
    if (joker || isFullHouse(keepers)) results[9] = 25;
    if (joker || isFourOfAKind(keepers)) results[8] = results[13];
    if (joker || isThreeOfAKind(keepers)) results[7] = results[13];

    // Bonus
    if (currentScores[12] == 50 && results[12] == 50)
    {
        results[0] = 100;
    }

    // Remove duplicates
    for (int i = 1; i < results.size(); i++)
    {
        if (currentScores[i] != -1) results[i] = -1;
    }

    return results;
}

/**
 * Print scoreboard
 *
 * @param scores Scoreboard to output
 * @param current Whether it is for current scores or possible scores
 */
void printScores(const vector<int>& scores, bool current)
{
    // Get max score
    int max = *max_element(scores.begin(), scores.end());

    // Does the array not have anything more than a 0
    bool print0 = !any_of(scores.begin(), scores.end(), [](int n){ return n > 0; });

    // Print scores
    for (int i = 0; i < scores.size(); i++)
    {
        int score = scores[i];
        if (score == 0 && !print0) continue;

        // Empty
        if (score == -1)
        {
            if (i == 0) continue;
            if (current)
            {
                cout << RED << left << setw(26) <<  SCORE_NAMES[i] << right << setw(6) << "EMPTY" << cendl;
            }
            continue;
        }

        if (!current)
        {
            if (score == 0) cout << RED;
            if (score == max) cout << GREEN;
            cout << i << ": ";
        }

        cout << left << setw(24) <<  SCORE_NAMES[i] << right << setw(6) << score << cendl;
    }
}

/**
 * Calculate total score
 *
 * @param scores Scoreboard
 * @param bonuses How many bonuses
 * @return Total score
 */
int totalScore(const vector<int>& scores, int bonuses)
{
    int sum = 0;

    for (int n : scores)
    {
        if (n != -1) sum += n;
    }

    return sum + bonuses * 100;
}

/**
 * Test cases for detection functions
 */
int testsMain()
{
    assert(isThreeOfAKind({1, 3, 3, 3, 4}));
    assert(isThreeOfAKind({1, 1, 1, 3, 4}));
    assert(isThreeOfAKind({1, 1, 4, 4, 4}));
    assert(isThreeOfAKind({1, 3, 3, 3, 3}));
    assert(!isThreeOfAKind({1, 1, 3, 4, 4}));

    assert(isFourOfAKind({1, 3, 3, 3, 3}));
    assert(isFourOfAKind({1, 1, 1, 1, 3}));
    assert(isFourOfAKind({1, 1, 1, 1, 1}));
    assert(!isFourOfAKind({1, 1, 2, 3, 3}));
    assert(!isFourOfAKind({1, 1, 1, 3, 3}));

    assert(isYahtzee({1, 1, 1, 1, 1}));
    assert(isYahtzee({6, 6, 6, 6, 6}));
    assert(!isYahtzee({5, 6, 6, 6, 6}));
    assert(!isYahtzee({5, 5, 5, 5, 6}));
    assert(!isYahtzee({1, 2, 3, 4, 5}));

    assert(isFullHouse({1, 1, 1, 2, 2}));
    assert(isFullHouse({1, 1, 6, 6, 6}));
    assert(!isFullHouse({1, 1, 5, 6, 6}));

    assert(isLargeStraight({1, 2, 3, 4, 5}));
    assert(isLargeStraight({2, 3, 4, 5, 6}));
    assert(!isLargeStraight({2, 2, 3, 4, 5}));
    assert(!isLargeStraight({2, 3, 4, 5, 5}));

    assert(isSmallStraight({2, 3, 4, 5, 5}));
    assert(isSmallStraight({2, 3, 4, 5, 5}));
    assert(isSmallStraight({2, 3, 4, 5, 6}));
    assert(isSmallStraight({2, 3, 4, 4, 5}));
    assert(!isSmallStraight({2, 3, 4, 4, 4}));

    assert(sum({2, 3, 4, 4, 4}) == 17);

    return 0;
}

/**
 * Input int in a way that doesn't break getlines
 *
 * @return Int input
 */
int inputInt()
{
    string input;
    getline(cin, input);
    if (input.empty()) return 0;
    return stoi(input);
}

/**
 * Sort an array (vector)
 *
 * @tparam T Type of the array elements
 * @param array The array to be sorted (vector)
 */
template <typename T> void sort(vector<T>& array)
{
    // Sort: For this one, I could have just copied my sort function from the
    //   insertion sort assignment, but in the real world, no programmer should
    //   reinvent the wheel or roll their own implementation because they are most
    //   likely less efficient than the well-tested implementations or have bugs
    //   that are not yet found. So I'm using the standard sort function here.
    sort(array.begin(), array.end());
}

/**
 * Join array to string
 *
 * @tparam T Type of the array elements
 * @param array Array (vector)
 * @param separator Separator between elements
 * @param pre Prefix
 * @param post Postfix
 * @return String of every element in the array
 */
template <typename T> string join(const vector<T>& array, const string& separator, const string& pre, const string& post)
{
    string result;

    for (int i = 0; i < array.size(); i++)
    {
        result += to_string(array[i]);
        if (i != array.size() - 1)
            result += separator;
    }

    return pre + result + post;
}

/**
 * Sum
 *
 * @param array Array to be summed
 * @return Sum of all the elements in the array
 */
int sum(const vector<int>& array)
{
    int result = 0;
    for (int n : array) result += n;
    return result;
}

/**
 * Count the occurrence of each value in the array
 *
 * @param array Array of numbers, Eg. [2, 2, 4, 5, 6]
 * @return Array of occurrences starting from 0, Eg. [0, 0, 2, 0, 1, 1, 1]
 */
vector<int> countOccurrences(const vector<int>& array)
{
    vector<int> occurrences(7);

    // Count the occurrences of each number
    for (int i = 1; i < occurrences.size(); i++)
    {
        occurrences[i] = 0;

        for (int n : array)
            if (n == i) occurrences[i] ++;
    }

    return occurrences;
}

/**
 * Determine whether an array has n of the same numbers.
 *
 * @param array Array to be determined (vector)
 * @param n How many of the same numbers does it need?
 * @param strict Is it strictly n-of-a-kind or does more than n also count.
 * @return N-of-a-kind or not
 */
bool isNOfAKind(const vector<int>& array, int n, bool strict)
{
    return isNOfAKindWithOccurrences(countOccurrences(array), n, strict);
}

/**
 * Determine whether an array has MORE THAN n of the same numbers.
 * This function exists to avoid calling countOccurrences more times than necessary.
 *
 * @param occurrences Array of occurrences.
 * @param n How many of the same numbers does it need?
 * @param strict Is it strictly n-of-a-kind or does more than n also count.
 * @return N-of-a-kind or not
 */
bool isNOfAKindWithOccurrences(const vector<int>& occurrences, int n, bool strict)
{
    // any_of returns true if at least one element in the array matches a lambda condition.
    return any_of(occurrences.begin(), occurrences.end(), [&n, &strict](int o){ return strict ? o == n : o >= n; });
}

/**
 * Determine the max sequence of numbers.
 *
 * Example Cases:
 * [1, 2, 3, 4, 6] -> 4
 * [2, 3, 4, 5, 5] -> 4
 * [2, 3, 4, 5, 6] -> 5
 * [3, 4, 5, 6, 6] -> 4
 * [1, 1, 1, 4, 6] -> 1
 *
 * @param array SORTED Array to be determined
 * @return The max length of a sequence
 */
int getMaxStraight(vector<int> array)
{
    // Remove duplicates (https://stackoverflow.com/a/1041939/7346633)
    array.erase(unique(array.begin(), array.end()), array.end());

    int maxSequence = 1;
    int currentSequence = 1;
    for (int i = 1; i < array.size(); i++)
    {
        // If the current two numbers are connected
        if (array[i] == array[i - 1] + 1)
        {
            currentSequence ++;
        }
            // The sequence ended
        else
        {
            maxSequence = max(maxSequence, currentSequence);
            currentSequence = 1;
        }
    }
    return max(maxSequence, currentSequence);
}

// Useless Encapsulations that only high-homeworks courses would require :|
bool isThreeOfAKind(const vector<int>& a) { return isNOfAKind(a, 3); }
bool isFourOfAKind(const vector<int>& a) { return isNOfAKind(a, 4); }
bool isYahtzee(const vector<int>& a) { return isNOfAKind(a, 5); }

// Full house is just a strictly 3-of-a-kind and a strictly 2-of-a-kind together
bool isFullHouse(const vector<int>& a) { return isNOfAKind(a, 3, true) && isNOfAKind(a, 2, true); }

bool isSmallStraight(const vector<int>& array) { return getMaxStraight(array) >= 4; }
bool isLargeStraight(const vector<int>& array) { return getMaxStraight(array) == 5; }
