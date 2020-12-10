//
// Created by Hykilpikonna on 12/9/20.
//

#include "conwayaf.h"
#include <arrayfire.h>
#include <cstdio>
#include <iostream>

using namespace af;

#define Long unsigned long long

int main(int, char**) {
    try {
        static const float h_kernel[] = {1, 1, 1, 1, 0, 1, 1, 1, 1};
        static const int reset        = 500;
        static const int game_w = 50, game_h = 50;

        af::info();

        // af::Window myWindow(200, 200, "Conway's Game of Life using ArrayFire");

        int frame_count = 0;

        // Initialize the kernel array just once
        const af::array kernel(3, 3, h_kernel, afHost);
        array state;
        state = (af::randu(game_h, game_w, f32) > 0.5).as(f32);

        // Randomly initialise cell map with ~50% on pixels
        std::cout << "Initializing" << std::endl;

        Long start = std::chrono::system_clock::now().time_since_epoch().count() / 1000;

        int generation = 1000001;
        for (int i = 0; i <= generation; i++)
        {
            // Convolve gets neighbors
            af::array nHood = convolve(state, kernel);

            // Generate conditions for life
            // state == 1 && nHood < 2 ->> state = 0
            // state == 1 && nHood > 3 ->> state = 0
            // else if state == 1 ->> state = 1
            // state == 0 && nHood == 3 ->> state = 1
            af::array C0 = (nHood == 2);
            af::array C1 = (nHood == 3);

            // Update state
            state = state * C0 + C1;
        }
        Long end = std::chrono::system_clock::now().time_since_epoch().count() / 1000;

        std::cout << "Total Generations: " << generation << std::endl
             << "Time: " << (end - start) << "ms" << std::endl;

    } catch (af::exception& e) {
        fprintf(stderr, "%s\n", e.what());
        throw;
    }
    return 0;
}
// int main(int, char**) {
//    try {
//        static const float h_kernel[] = {1, 1, 1, 1, 0, 1, 1, 1, 1};
//        static const int reset        = 500;
//        static const int game_w = 128, game_h = 128;
//
//        af::info();
//
//        af::Window myWindow(512, 512, "Conway's Game of Life using ArrayFire");
//
//        int frame_count = 0;
//
//        // Initialize the kernel array just once
//        const af::array kernel(3, 3, h_kernel, afHost);
//        array state;
//        state = (af::randu(game_h, game_w, f32) > 0.5).as(f32);
//
//        while (!myWindow.close()) {
//            myWindow.image(state);
//            frame_count++;
//
//            // Generate a random starting state
//            if (frame_count % reset == 0)
//                state = (af::randu(game_h, game_w, f32) > 0.5).as(f32);
//
//            // Convolve gets neighbors
//            af::array nHood = convolve(state, kernel);
//
//            // Generate conditions for life
//            // state == 1 && nHood < 2 ->> state = 0
//            // state == 1 && nHood > 3 ->> state = 0
//            // else if state == 1 ->> state = 1
//            // state == 0 && nHood == 3 ->> state = 1
//            af::array C0 = (nHood == 2);
//            af::array C1 = (nHood == 3);
//
//            // Update state
//            state = state * C0 + C1;
//        }
//    } catch (af::exception& e) {
//        fprintf(stderr, "%s\n", e.what());
//        throw;
//    }
//    return 0;
//}