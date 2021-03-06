//
// Created by Hykilpikonna on 12/7/20.
//

#include "conway.h"
#include "crack.h"

using namespace std::chrono;

int orderX[] = {0,0,1,1,0,1,2,2,2,0,1,2,3,3,3,3,0,1,2,3,4,4,4,4,4,0,1,2,3,4,5,5,5,5,5,5,0,1,2,3,4,5,6,6,6,6,6,6,6,0,1,2,3,4,5,6,7,7,7,7,7,7,7,7};
int orderY[] = {0,1,0,1,2,2,0,1,2,3,3,3,0,1,2,3,4,4,4,4,0,1,2,3,4,5,5,5,5,5,0,1,2,3,4,5,6,6,6,6,6,6,0,1,2,3,4,5,6,7,7,7,7,7,7,7,0,1,2,3,4,5,6,7};

int main(int argc, char* argv[])
{
    // Check params
    if (argc > 1)
    {
        // Run tests
        if (string(argv[1]) == "test")
        {
            runTests();
            return 0;
        }

        // Print crack
        if (string(argv[1]) == "print")
        {
            var n = stoull(argv[2]);

            // Create challenge board
            var b2 = BoardWithCoins(50, 50);
            b2.fillCoins(0, 16, 50, 50, 2);
            b2.fillCoins(16, 0, 50, 50, 2);

            // Fill combination
            for (int b = 0; b < 63; b++)
            {
//                if (isBit(n, b)) b2.alive[15 - orderX[b]][15 - orderY[b]] = true;
                int row = b / 8;
                int col = b % 8;

                if (isBit(n, b)) b2.alive[15 - row][15 - col] = true;
            }
            b2.print();

            for (int i = 0; i < 16; i++)
            {
                for (int j = 0; j < 16; j++)
                {
                    cout << (b2.alive[i][j] ? "1" : "0");
                }
                cout << endl;
            }
            return 0;
        }
    }

    // Prompt
    cout << "Welcome to Hykilp's implementation of Conway's Game of Life!\n\n"
            "Launch options:\n"
            "0: Start simulation.\n"
            "1: Try my challenge!\n";

    switch (inputInt())
    {
        case 0: startSim(); break;
        case 1: startChallenge(); break;
        default: cout << "What?" << endl; break;
    }

    return 0;
}

void runTests()
{
    // Border cases
//    var b0 = Board(3, 4);
//    for (val x : {0, 1, 2})
//        for (val y : {0, 1, 2, 3})
//            b0.alive[x][y] = true;
//    assert(!b0.isAlive(0, -1));
//    assert(!b0.isAlive(-1, -1));
//    assert(!b0.isAlive(-1, 0));
//    assert(!b0.isAlive(3, 3));
//    assert(!b0.isAlive(2, 4));
//    for (val x : {0, 1, 2})
//        for (val y : {0, 1, 2, 3})
//            assert(b0.isAlive(x, y));

//    var board = Board(50, 50);
//    unsigned int x, y, init_length;
//
//    // Get seed; random if 0
//    Long seed = (unsigned) time(nullptr);
//
//    // Randomly initialise cell map with ~50% on pixels
//    cout << "Initializing" << endl;
//
//    srand(seed);
//    init_length = (50 * 50) / 2;
//    do
//    {
//        x = rand() % (50 - 1);
//        y = rand() % (50 - 1);
//        board.alive[x][y] = true;
//    } while (--init_length);
//
//    Long start = system_clock::now().time_since_epoch().count() / 1000;
//
//    int generation = 10001;
//    for (int i = 0; i <= generation; i++)
//    {
//        board.tick();
//    }
//    Long end = system_clock::now().time_since_epoch().count() / 1000;
//
//    cout << "Total Generations: " << generation
//         << "\nSeed: " << seed << endl
//         << "Time: " << (end - start) << "ms" << endl;


    // Done!
    cout << "All Tests Passed!" << endl;

    crack();
}

void startSim()
{
    val width = inputInt("Input your board width: ");
    val height = inputInt("Input your board height: ");
    var board = Board(width, height);
    board.input();
    board.print();

    while (true)
    {
        this_thread::sleep_for(0.1s);
        board.tick();
        board.print();
        cout << "Press Ctrl+C to stop." << endl;

        if (board.alive.empty()) break;
    }
}

void startChallenge()
{
    cout << "Your challenge is, try to get as many coins as you can! \n"
            "But you can only control this 16x16 grid in a 50x50 world. \n";

    var board = BoardWithCoins(50, 50);
    board.input(0, 0, 16, 16);

    // Fill coins everywhere besides the 16x16
    board.fillCoins(2, 16, 48, 48, 2);
    board.fillCoins(16, 2, 48, 48, 2);

    board.print();

    // Count coins collected
    var coins = 0;

    while (true)
    {
        this_thread::sleep_for(0.05s);
        coins += board.tickWithCoins();
        board.print();
        cout << yellow << "You have " << coins << " coins!" << reset << endl;
        cout << "Press Ctrl+C to stop." << endl;

        // Win! \(^o^)/~
        if (coins >= 50 * 50 - 16 * 16)
        {
            cout << yellow << "Yay! You've got all the points!" << reset << endl;
            break;
        }

        if (board.alive.empty()) break;
    }
}
