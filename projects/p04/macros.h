//
// Created by Hykilpikonna on 12/7/20.
// This header contains all the external imports and macros.
//
#ifndef HOMEWORKS_MACROS_H
#define HOMEWORKS_MACROS_H

#include "cstdint"
#include "iostream"
#include "vector"
#include "map"
#include "unordered_map"
#include "algorithm"
#include "tuple"
#include "string"
#include "set"
#include "thread"
#include "iomanip"
#include "array"

using namespace std;

// Kotlin habit ;-;
#define Int uint32_t // int is only 16-bits on LP32
#define Long uint64_t
#define var auto
#define let auto
#define val const auto

#define Bool bool
#define Set set
#define List vector
#define Map unordered_map
#define String string

// Convenient things
#define log(msg)(cout << msg << endl)
#define str(x)(to_string(x))

// Colors
val darkColor = "\x1b[48;5;0m\x1b[38;5;11m";
val lightColor = "\x1b[48;5;15m\x1b[38;5;11m";
val reset = "\x1b[0m";
val yellow = "\x1b[38;5;11m";
val yellowBackground = "\x1b[48;5;11m\x1b[38;5;0m";
val clearScreen = "\033[2J\033[H\n";

#endif //HOMEWORKS_MACROS_H
