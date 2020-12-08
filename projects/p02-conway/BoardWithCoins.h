//
// Created by Hykilpikonna on 12/8/20.
//

#ifndef HOMEWORKS_BOARDWITHCOINS_H
#define HOMEWORKS_BOARDWITHCOINS_H

#include "Board.h"

class BoardWithCoins: Board
{
public:
    List<Long> coins;

    /**
     * Construct a board with coins
     *
     * @param w Width
     * @param h Height
     */
    BoardWithCoins(Int w, Int h): Board(w, h) {}

    /**
     * Get whether the cell at a position is a coin. (Assumes `coins` is sorted)
     *
     * @param x Position X.
     * @param y Position Y.
     * @return Is coin or not.
     */
    bool isCoin(Int x, Int y);

    void print() override;
};


#endif //HOMEWORKS_BOARDWITHCOINS_H
