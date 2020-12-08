//
// Created by Hykilpikonna on 12/7/20.
//

#ifndef HOMEWORKS_BOARD_H
#define HOMEWORKS_BOARD_H

#include "macros.h"

/**
 * A board contains an array of alive points
 */
class Board
{
public:
    vector<Long> alive;
    Int w;
    Int h;

    /**
     * Construct a board
     *
     * @param w Width
     * @param h Height
     */
    Board(Int w, Int h): w(w), h(h) {}

};

#endif //HOMEWORKS_BOARD_H
