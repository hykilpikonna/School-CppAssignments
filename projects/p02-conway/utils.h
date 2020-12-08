//
// Created by Hykilpikonna on 12/7/20.
//

#include "macros.h"

#ifndef HOMEWORKS_CONWAY_UTILS_H
#define HOMEWORKS_CONWAY_UTILS_H

/**
 * Convert a position into one long number, with the first 32
 * bits being the bits from the first int32, and the next 32
 * bits being the bits from the second int32.
 *
 * @param x Position X (Positive).
 * @param y Position Y (Positive).
 * @return Long number.
 */
Long pointHash(Int x, Int y);

/**
 * Convert the long number back to the position.
 *
 * @param hash Long number
 * @return Position X and Y
 */
tuple<Int, Int> pointUnhash(Long hash);

/**
 * Input int in a way that doesn't break getlines
 *
 * @return Int input
 */
int inputInt(const string& prompt);

#endif //HOMEWORKS_CONWAY_UTILS_H
