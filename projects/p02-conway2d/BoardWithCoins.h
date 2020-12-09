//
// Created by Hykilpikonna on 12/8/20.
//

#ifndef HOMEWORKS_BOARDWITHCOINS_H
#define HOMEWORKS_BOARDWITHCOINS_H

#include "Board.h"

class BoardWithCoins: public Board
{
public:
    List<List<bool>> coins;

    /**
     * Construct a board with coins
     *
     * @param w Width
     * @param h Height
     */
    BoardWithCoins(Int w, Int h);

    /**
     * Print with coins
     */
    void print() override;

    /**
     * Tick
     *
     * @return How many coins are gained from this tick
     */
    Int tickWithCoins();

    /**
     * Fill coins
     *
     * @param x
     * @param y
     * @param xEnd
     * @param yEnd
     */
    void fillCoins(Int x, Int y, Int xEnd, Int yEnd, Int step = 1);
};


#endif //HOMEWORKS_BOARDWITHCOINS_H
