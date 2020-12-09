//
// Created by Hykilpikonna on 12/7/20.
//

#include "macros.h"

#ifndef HOMEWORKS_CONWAY_UTILS_H
#define HOMEWORKS_CONWAY_UTILS_H

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
 * Create an empty 2d array
 *
 * @param w
 * @param h
 * @return 2d array of false
 */
List<List<bool>> makeList(Int w, Int h);

#endif //HOMEWORKS_CONWAY_UTILS_H
