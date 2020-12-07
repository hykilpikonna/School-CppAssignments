cmake_minimum_required(VERSION 3.17)
project(homeworks)

set(CMAKE_CXX_STANDARD 17)

add_executable(homeworks homeworks/b017-row-sum.cpp projects/p02-conway/conway.cpp)

add_executable(yahtzee projects/p01-yahtzee/yahtzee.cpp)
add_executable(conway projects/p02-conway/conway.cpp)
add_executable(test test.cpp)
#add_executable(randcrack rand/randcrack.cpp)
#add_executable(randgen rand/randgen.cpp)
add_executable(yahtzee-randcrack projects/p01-yahtzee/rand/yahtzee-randcrack.cpp)
add_executable(yahtzee-randgen projects/p01-yahtzee/rand/yahtzee-randgen.cpp)