//
// Created by Hykilpikonna on 11/17/20.
//
#include "iostream"
#include "iomanip"
#include "algorithm"
#include "vector"
#include "map"

// Macros
#define ull unsigned long long

// Configure the algorithm here!
#define algorithm rand() % 6 + 1
#define algorithm_str "rand() % 6 + 1"

using namespace std;

/**
 * Split string https://stackoverflow.com/a/46931770/7346633
 */
vector<string> split (const string& s, const string& delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos)
    {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

/**
 * Main function
 */
int main()
{
    cout << "Welcome to " algorithm_str " cracker!" << endl << endl;

    // Set seed range
    cout << "What do you think is the number nearest to the seed? (Default: current time(nullptr))" << endl << "> ";
    string inputSeed;
    getline(cin, inputSeed);
    ull base = inputSeed.empty() ? (unsigned) time(nullptr) : stoull(inputSeed);
    cout << "- Center set to " << base << endl << endl;

    cout << "What range do you want to search in? (Default: 1000 * 60 * 60)" << endl << "> ";
    string inputRange;
    getline(cin, inputRange);
    ull range = inputRange.empty() ? 1000 * 60 * 60 : stoi(inputRange);
    ull start = base - range;
    ull end = base + range;
    cout << "- Range set to [" << start << ", " << end << "]" << endl << endl;

    // Find seed
    ull seed = 0;
    vector<vector<int>> randSets;
    string line;
    while (true)
    {
        cout << "Input data: ";
        if (!getline(cin, line)) continue;
        if (line.empty()) continue;

        // Add input
        {
            vector<int> randSet;
            for (char c : line)
            {
                randSet.emplace_back(c - 48);
            }
            randSets.emplace_back(randSet);
        }

        // Search through seeds
        ull seedsFound = 0;
        for (ull possibleSeed = start; possibleSeed < end; possibleSeed++)
        {
            srand(possibleSeed);

            // Loop through sets
            for (const vector<int>& set : randSets)
            {
                auto size = set.size();

                // Generate sorted randoms
                vector<int> gen(size);
                for (int& n : gen) n = algorithm;
                sort(gen.begin(), gen.end());

                if (!equal(gen.begin(), gen.end(), set.begin())) goto end;
            }

            // Found!
            seed = possibleSeed;
            seedsFound ++;

            end:continue;
        }

        // Seed not found / not yet found
        if (seedsFound == 0)
        {
            cout << "ERROR! NO SEEDS FOUND!" << endl << endl;
            return 1;
        }
        if (seedsFound > 1)
        {
            cout << seedsFound << " seeds found, try adding some more data!" << endl << endl;
            continue;
        }

        // Seed found
        cout << "Seed found! Seed: " << seed << endl << endl;
        break;
    }

    // Set seed
    srand(seed);

    // Roll the ones that are already rolled.
    cout << "Rolling back..." << endl;
    for (const vector<int>& _ : randSets) for (int a : _) cout << algorithm << " ";
    cout << "Done." << endl << endl;

    cout << "Command line activated." << endl;
    cout << "exit            Exit the program" << endl;
    cout << "store n         Store the next n numbers (Must do this before other actions)" << endl;
    cout << "next n          Display the next n numbers" << endl;
    cout << "prev n          Rollback n numbers" << endl;
    cout << "ign n           Roll n numbers without outputting them" << endl;
    cout << endl;
    cout << "You should start with 'store 100000' or something!" << endl;

    // Prediction controls
    vector<int> pred;
    int predIndex = 0;

    auto next = [&pred, &predIndex](){ return pred[predIndex++]; };
    auto prev = [&pred, &predIndex](){ return pred[predIndex--]; };

    while (true)
    {
        cout << endl << "> ";
        if (!getline(cin, line)) break;
        if (line.empty()) continue;

        // Parse command
        auto args = split(line, " ");
        auto command = args[0];
        args.erase(args.begin());

        // ////////////////////////////////////////////
        // Commands that doesn't require params
        // ////////

        if (command == "exit") break;

        // Print next
        if (line.rfind("next", 0) == 0)
        {
            // No arguments
            if (line.length() <= 4) cout << next() << endl;

            // Specified count
            else
            {
                int size = stoi(line.substr(4));

                vector<int> gen(size);
                cout << "Raw:    ";
                for (int& n : gen) cout << (n = next()) << " ";
                cout << endl << "Sorted: ";
                sort(gen.begin(), gen.end());
                for (int n : gen) cout << n << " ";
                cout << endl;
            }
        }

        // ////////////////////////////////////////////
        // Commands that require 1 int param
        // ////////

        // Check param
        if (args.empty())
        {
            cout << "Missing parameters!" << endl;
            continue;
        }
        int n = stoi(args[0]);

        // Store numbers
        if (command == "store")
        {
            cout << "Storing " << n << " rands... ";
            for (int i = 0; i < n; i++) pred.emplace_back(algorithm);
            cout << "Done." << endl;
        }

        // Ignore
        if (command == "ign")
        {
            predIndex += n;
            cout << "Ignored " << n << " rands, now the index is at " << predIndex << endl;
        }

        // Rollback
        if (command == "prev")
        {
            cout << "Rolling back..." << endl;
            for (int i = 0; i < n; i++) cout << prev() << " ";
            cout << "Done." << endl;
            cout << "Rolled back " << n << " rands, now the index is at " << predIndex << endl;
        }
    }

    return 0;
}