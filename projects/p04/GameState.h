//
// Created by Hykilpikonna on 1/18/21.
//

#ifndef SCHOOL_CPP_GAMESTATE_H
#define SCHOOL_CPP_GAMESTATE_H

#include "constants.h"
#include "macros.h"
#include "utils.h"

// Winning combos
List<List<Int>> combos = {
        // Horizontal
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        // Vertical
        {0, 3, 6}, {1, 4, 7}, {2, 6, 8},
        // Diagonal
        {0, 4, 8}, {2, 4, 6}
};
val NO_CELL = -50;

/**
 * Player interface
 */
class Player
{
    virtual int move() = 0;
};

/**
 * Class storing the current game state
 */
class GameState
{
public:
    array<int, rows * rows> grid{};
    int currentPlayer = 0;

    /**
     * Constructor
     */
    GameState()
    {
        // Init grid (-1: No one placed anything here yet)
        for (int& n : grid) { n = NO_CELL; }
    }

    /**
     * Make a move for the current player
     *
     * @param x
     * @param y
     */
    void movePlayer(int x, int y)
    {
        // Set grid state
        grid[xyToLoc(x, y)] = currentPlayer;

        // To next player
        currentPlayer = (currentPlayer + 1) % 2;
    }

    /**
     * Check who won, or draw
     *
     * @return Game result [-1: there's no result yet, 0: player 1 wins, 1: payer 2 wins, 2: draw)
     */
    int checkResult()
    {
        // Check winning combos
        for (List<Int> combo : combos)
        {
            val sum = grid[combo[0]] + grid[combo[1]] + grid[combo[2]];
            if (sum == 0) return 0; // Player 1 wins
            if (sum == 3) return 1; // Player 2 wins
        }

        // Check if all grid cells are filled TODO: Predict draws
        for (int n : grid)
        {
            if (n == NO_CELL) return -1; // No results yet
        }
        return 2; // Draws
    }
};

#endif //SCHOOL_CPP_GAMESTATE_H
