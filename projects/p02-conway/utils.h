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
 * Input a line
 *
 * @param prompt
 * @return String input
 */
String inputLine(const string& prompt = "");

/**
 * Input int in a way that doesn't break getlines
 *
 * @param prompt
 * @return Int input
 */
int inputInt(const string& prompt = "");

/**
 * Check if a cell should survive
 *
 * @param aliveNeighbors How many neighbors are alive
 * @return It should survive or not
 */
bool shouldSurvive(bool currentAlive, Int aliveNeighbors);

/**
 * Repeat a string how many times
 *
 * @param str String
 * @param times How many times
 * @return Repeated string
 */
String repeat(const String &str, Int times);

/**
 * Find the index through a binary search
 * https://stackoverflow.com/a/46824354/7346633
 *
 * @param v Vector
 * @param data Data
 * @return Index or -1
 */
int binarySearchIndexOf(List<Long> v, Long data);

#endif //HOMEWORKS_CONWAY_UTILS_H
