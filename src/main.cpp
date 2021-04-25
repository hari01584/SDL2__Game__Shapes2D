//
// Created by hari0 on 15-04-2021.
//

#include "main.h"
#include "looper.h"
#include "import.h"
#include "dimens.h"
#include "FileOperations.h"
#include <cstdio>
#include <cstdlib>
#include <stdbool.h>
#include <ctime>


// Utility macros
#define CHECK_ERROR(test, message) \
    do { \
        if((test)) { \
            fprintf(stderr, "%s\n", (message)); \
            exit(1); \
        } \
    } while(0)

// Get a random number from 0 to 255
int randInt(int rmin, int rmax) {
    return rand() % rmax + rmin;
}
int width = 800;
int height = 600;

int main(int argc, char **argv) {
    // Initialize the random number generator
    srand((unsigned int)time(NULL));

    // Initialize SDL
    CHECK_ERROR(SDL_Init(SDL_INIT_VIDEO) != 0, SDL_GetError());
    SDL_DisplayMode mode;

    FileOp::InitializePrefPath();
    FileOp::PrepareConfigFileDescriptor();

    FileOp::loadConfigBin();

#if defined(ANDROID)
    SDL_GetDesktopDisplayMode(0, &mode);
    width = mode.w;
    height = mode.h;
#endif

    // Create an SDL window
    SDL_Window *window = SDL_CreateWindow("Shapes!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
    CHECK_ERROR(window == NULL, SDL_GetError());

    // Create a renderer (accelerated and in sync with the display refresh rate)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    CHECK_ERROR(renderer == NULL, SDL_GetError());

    // Initial renderer color
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

//    SDL_Event event;

    startLooper(renderer);
//
//    while(running) {
//        // Process events
//        while(SDL_PollEvent(&event)) {
//            if(event.type == SDL_QUIT) {
//                running = false;
//            } else if(event.type == SDL_FINGERDOWN) {
//                SDL_SetRenderDrawColor(renderer, randInt(0, 255), randInt(0, 255), randInt(0, 255),
//                                       255);
//            }
//        }
//
//        // Clear screen
//        SDL_RenderClear(renderer);
//
//        // Draw
//
//        // Show what was drawn
//        SDL_RenderPresent(renderer);
//    }
//
//    // Release resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
