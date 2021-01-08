cmake_minimum_required(VERSION 3.17)
project(homeworks)

set(CMAKE_CXX_STANDARD 17)
find_package(ArrayFire)
add_executable(arrayfire projects/p02-conway-arrayfire/conwayaf.cpp)

# To use Unified backend, do the following.
# Unified backend lets you choose the backend at runtime
target_link_libraries(arrayfire ArrayFire::af)

add_executable(homeworks homeworks/b018-random-toss.cpp)
add_executable(conway projects/p02-conway2d/macros.h projects/p02-conway2d/utils.cpp projects/p02-conway2d/utils.h projects/p02-conway2d/conway.cpp projects/p02-conway2d/conway.h projects/p02-conway2d/Board.cpp projects/p02-conway2d/Board.h projects/p02-conway2d/BoardWithCoins.cpp projects/p02-conway2d/BoardWithCoins.h projects/p02-conway2d/crack.cpp projects/p02-conway2d/crack.h)
add_executable(conwaybm projects/p02-conway-bitmap/conwaybm.cpp projects/p02-conway-bitmap/ThreadPool.h projects/p02-conway2d/macros.h)

add_executable(test test.cpp)
#add_executable(yahtzee projects/p01-yahtzee/yahtzee.cpp)
#add_executable(randcrack rand/randcrack.cpp)
#add_executable(randgen rand/randgen.cpp)
#add_executable(yahtzee-randcrack projects/p01-yahtzee/rand/yahtzee-randcrack.cpp)
#add_executable(yahtzee-randgen projects/p01-yahtzee/rand/yahtzee-randgen.cpp)

add_executable(pitch-penny
        projects/p03-pitch-penny/macros.h
        projects/p03-pitch-penny/pitch-penny.cpp
        projects/p03-pitch-penny/pitch-penny.h
)