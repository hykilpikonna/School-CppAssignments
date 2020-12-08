//
// Created by Hykilpikonna on 12/8/20.
//

#ifndef HOMEWORKS_BOARDWITHCOINS_H
#define HOMEWORKS_BOARDWITHCOINS_H

#include "Board.h"

class BoardWithCoins: public Board
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
     * @param hash Point hash.
     * @return Index of the coin or -1
     */
    [[nodiscard]] int findCoin(Long hash) const;

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
    void fillCoins(Int x, Int y, Int xEnd, Int yEnd);
};


#endif //HOMEWORKS_BOARDWITHCOINS_H
