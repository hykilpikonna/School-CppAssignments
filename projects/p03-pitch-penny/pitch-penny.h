//
// Created by Hykilpikonna on 1/7/21.
//

#ifndef HOMEWORKS_PITCHPENNY_H
#define HOMEWORKS_PITCHPENNY_H

#include "macros.h"

// Constants
val w = 5, h = 5;
val len = w * h;
val pennyCount = 10;

int main();

/**
 * A board contains both a prize grid and a penny grid
 */
class PitchPennyBoard
{
public:
    List<String> prizeNames;
    List<String> prizeGrid;
    List<Bool> pennyGrid;

    /**
     * Create a board with prizeNames
     * @param prizeNames Prize names
     */
    explicit PitchPennyBoard(List<String>& prizeNames);

    /**
     * Toss coin (TODO: Can a coin be tossed to a location that already has a coin?
     *
     * @return Location of the coin tossed and what prize is at that location.
     */
    tuple<Int, String> tossCoin();

    /**
     * Print the board
     */
    void printBoard();
};

#endif //HOMEWORKS_PITCHPENNY_H
