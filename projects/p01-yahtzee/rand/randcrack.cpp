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

int main()
{
    cout << "Welcome to " algorithm_str " cracker!" << endl << endl;

    // Set seed range
    cout << "What do you think is the most probable seed? (Default: current time(nullptr))" << endl << "> ";
    string inputSeed;
    getline(cin, inputSeed);
    ull base = inputSeed.empty() ? (unsigned) time(nullptr) : stoull(inputSeed);
    cout << "- Center set to " << base << endl;

    cout << "What range do you want to search in? (Default: 1000 * 60 * 60)" << endl << "> ";
    string inputRange;
    getline(cin, inputRange);
    ull range = inputRange.empty() ? 1000 * 60 * 60 : stoi(inputRange);
    ull start = base - range;
    ull end = base + range;
    cout << "- Range set to [" << start << ", " << end << "]" << endl;

    // Find seed
    ull seed = 0;
    vector<int> rands;
    string line;
    while (true)
    {
        cout << "Input data: ";
        if (!getline(cin, line)) break;

        // Add input
        if (!line.empty()) rands.emplace_back(stoi(line));

        // Search through seeds
        ull seedsFound = 0;
        for (ull possibleSeed = start; possibleSeed < end; possibleSeed++)
        {
            srand(possibleSeed);
            for (int r : rands)
            {
                if (algorithm != r) goto end;
            }

            // Found!
            seed = possibleSeed;
            seedsFound ++;

            end:continue;
        }

        // Seed not found / not yet found
        if (seedsFound == 0)
        {
            cout << "ERROR! NO SEEDS FOUND!" << endl;
            return 1;
        }
        if (seedsFound > 1)
        {
            cout << seedsFound << " seeds found, try adding some more data!" << endl;
            continue;
        }

        // Seed found
        cout << "Seed found! Seed: " << seed << endl;
        break;
    }

    // Set seed
    srand(seed);

    // Roll the ones that are already rolled.
    for (int _ : rands) algorithm;

    // Prediction controls
    vector<int> predictions;
    while (true)
    {
        cout << "> ";
        if (!getline(cin, line)) break;
        if (line == "exit") break;
        if (line.empty()) continue;

        if (line.rfind("next", 0) == 0)
        {
            // No arguments
            if (line.length() <= 4) cout << algorithm << endl;

            // Specified count
            else
            {
                int count = stoi(line.substr(4));
                cout << count;
                for (int i = 0; i < count; i++) cout << algorithm << " ";
                cout << endl;
            }
        }
    }

    return 0;
}