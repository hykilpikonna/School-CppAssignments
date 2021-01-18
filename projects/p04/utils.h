//
// Created by Hykilpikonna on 1/18/21.
//

#ifndef SCHOOL_CPP_UTILS_H
#define SCHOOL_CPP_UTILS_H

/**
 * Convert x-y position to location index
 *
 * @param x
 * @param y
 * @return Location index
 */
int xyToLoc(int x, int y)
{
    return y * rows + x;
}

/**
 * Convert location index to x-y position
 *
 * @param loc Location index
 * @return x-y position
 */
tuple<int, int> locToXy(int loc)
{
    return {loc % rows, loc / rows};
}

#endif //SCHOOL_CPP_UTILS_H
