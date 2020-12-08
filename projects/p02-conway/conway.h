//
// Created by Hykilpikonna on 12/7/20.
//

#ifndef HOMEWORKS_CONWAY_H
#define HOMEWORKS_CONWAY_H

/*
 * Design notes:
 * 1. About using an array of points rather than a 2D grid:
 *   An array of alive points is more optimized for large grids
 *   because it doesn't have to check every single position on
 *   the grid when it updates.
 */

// Custom macros
#include "macros.h"
#include "utils.h"
#include "Board.h"

/**
 * Where magic happens
 *
 * @return Exit code
 */
int main();

/**
 * Start simulation
 *
 * @param width
 * @param height
 */
void startSim(int width, int height);

void startChallenge();

Board inputBoard(int width, int height);

#endif //HOMEWORKS_CONWAY_H
