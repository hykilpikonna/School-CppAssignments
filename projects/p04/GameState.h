//
// Created by Hykilpikonna on 1/18/21.
//

#ifndef SCHOOL_CPP_GAMESTATE_H
#define SCHOOL_CPP_GAMESTATE_H

#include "constants.h"
#include "macros.h"
#include "utils.h"

#define Grid array<int, rows * rows>

// Winning combos
List<List<Int>> combos = {
        // Horizontal
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        // Vertical
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        // Diagonal
        {0, 4, 8}, {2, 4, 6}
};
val NO_CELL = -50;

/**
 * Class storing the current game state
 */
class GameState
{
public:
    Grid grid{};
    int currentPlayer = 0;
    bool aiMode;
    int aiDifficulty;
    int aiPlayer;

    /**
     * Constructor
     */
    explicit GameState(bool aiMode = false, int aiDifficulty = 0, int aiPlayer = 1): aiMode(aiMode), aiDifficulty(aiDifficulty), aiPlayer(aiPlayer)
    {
        // Init grid (-1: No one placed anything here yet)
        for (int& n : grid) { n = NO_CELL; }

        // AI initial move
        if (aiMode && aiPlayer == 0)
        {
            aiMove(aiDifficulty);
        }
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

        // Move AI if game hasn't ended
        if (get<0>(checkResult()) == -1 && aiMode) aiMove(aiDifficulty);
    }

    /**
     * Check who won, or draw
     *
     * @return Game result [-1: there's no result yet, 0: player 1 wins, 1: payer 2 wins, 2: draw)
     *         And the combo
     */
    tuple<int, List<Int>> checkResult()
    {
        // Check winning combos
        for (List<Int> combo : combos)
        {
            val sum = grid[combo[0]] + grid[combo[1]] + grid[combo[2]];
            if (sum == 0) return {0, combo}; // Player 1 wins
            if (sum == 3) return {1, combo}; // Player 2 wins
        }

        // TODO: Predict draws
        return {isFilled() ? 2 : -1, {}};
    }

    /**
     * Check if all grid cells are filled
     */
    bool isFilled()
    {
        return all_of(grid.begin(), grid.end(), [](int cell){ return cell != NO_CELL; });
    }

    /**
     * Let AI make a move
     *
     * @param difficulty Difficulty of the AI
     * @return AI move location
     */
    int aiMove(int difficulty)
    {
        // Prevent endless loops
        if (isFilled()) return -1;

        var move = -1;
        if (difficulty == 0) move = aiMove0(grid);
        if (difficulty == 1)
        {
            move = aiMove1(grid, aiPlayer);
            if (move == -1) move = aiMove0(grid);
        }

        // Make the move
        grid[move] = currentPlayer;
        currentPlayer = (currentPlayer + 1) % 2;
        return move;
    }

    /**
     * "Ponkotsu AI"
     *
     * @return A random move
     */
    static int aiMove0(Grid grid)
    {
        log("[AI] Random move.");
        while (true)
        {
            val loc = rand() % (rows * rows);
            if (grid[loc] == NO_CELL) return loc;
        }
    }

    /**
     * Normal AI: Blocks opponent wins and go for winning moves
     *
     * @returns Blocking move or winning move, or otherwise returns -1
     */
    static int aiMove1(Grid grid, int aiPlayer)
    {
        // If the AI Player is 0 (X), then two 1s (O) would be dangerous
        // Two 1s have a value of 2, so the total sum would be 2 + NO_CELL, which is -48.
        // If the AI Player is 1 (O), then two 0s (X) would be dangerous
        // Two 0s have a value of 0, so the total sum would be NO_CELL, which is -50.
        val dangerousSum = aiPlayer == 0 ? 2 + NO_CELL : NO_CELL;
        val winningSum = aiPlayer == 0 ? NO_CELL : 2 + NO_CELL;

        // Temp variables
        var blockingMove = -1;
        var winningMove = -1;

        // Find blocking/winning combos
        for (List<Int> combo : combos)
        {
            val sum = grid[combo[0]] + grid[combo[1]] + grid[combo[2]];

            // Found dangerous/winning combo
            if (sum == dangerousSum || sum == winningSum)
            {
                // Find the empty spot
                for (int loc : combo)
                {
                    if (grid[loc] == NO_CELL)
                    {
                        if (sum == dangerousSum) blockingMove = loc;
                        else winningMove = loc;
                        break;
                    }
                }
            }
        }

        // Winning move first, then blocking move
        if (winningMove != -1)
        {
            log("[AI] Winning move.");
            return winningMove;
        }
        if (blockingMove != -1)
        {
            log("[AI] Blocking move.");
            return blockingMove;
        }

        // No combo found
        return -1;
    }
};

#endif //SCHOOL_CPP_GAMESTATE_H
