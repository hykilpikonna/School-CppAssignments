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

using namespace std;

// Terrible C stuff: int is only 16-bits on LP32
#define Int uint32_t
#define Long uint64_t

// Kotlin habit ;-;
#define HashMap unordered_map
#define String string

#endif //HOMEWORKS_MACROS_H
