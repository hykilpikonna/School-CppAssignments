//
// Created by Hykilpikonna on 12/7/20.
//

#include "conway.h"

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
    }

    // Prompt
    cout << "Welcome to Hykilp's implementation of Conway's Game of Life!\n\n"
            "Launch options:\n"
            "1: Start simulation.\n"
            "2: Try my challenge!\n";

    // Simulation
    if (inputInt() == 1)
    {
        val width = inputInt("Input your board width: ");
        val height = inputInt("Input your board height: ");
        var board = Board(width, height);
        board.input();
        board.print();
        startSim(board);
    }

    return 0;
}

void runTests()
{
    // Point: Hash and unhash
    assert(pointHash(5, 1) == 21474836481);
    val [x, y] = pointUnhash(21474836481);
    assert(x == 5 && y == 1);

    // Border cases
    var board = Board(3, 4);
    for (val x : {0, 1, 2})
        for (val y : {0, 1, 2, 3})
            board.alive.emplace_back(pointHash(x, y));
    sort(board.alive.begin(), board.alive.end());
    assert(!board.isAlive(0, -1));
    assert(!board.isAlive(-1, -1));
    assert(!board.isAlive(-1, 0));
    assert(!board.isAlive(3, 3));
    assert(!board.isAlive(2, 4));
    for (val x : {0, 1, 2})
        for (val y : {0, 1, 2, 3})
            assert(board.isAlive(x, y));

    // Done!
    cout << "All Tests Passed!" << endl;
}

void startSim(Board board)
{
    while (true)
    {
        cout << "Press any key to continue or Ctrl+C to break..." << endl;
        cin.ignore();
        board.tick();
        board.print();
    }
}