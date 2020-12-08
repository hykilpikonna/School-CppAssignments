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

    void print() override;
};


#endif //HOMEWORKS_BOARDWITHCOINS_H
