#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "looper.h"
#include "utility.h"
#include "dimens.h"

// Utility macros
#define CHECK_ERROR(test, message) \
    do { \
        if((test)) { \
            fprintf(stderr, "%s\n", (message)); \
            exit(1); \
        } \
    } while(0)




int main(int argc, char** argv) {
    // Initialize the random number generator
    srand((unsigned int)time(NULL));

    // Initialize SDL
    CHECK_ERROR(SDL_Init(SDL_INIT_VIDEO) != 0, SDL_GetError());
    TTF_Init();
    // Create an SDL window
    SDL_Window* window = SDL_CreateWindow("Serbia", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
    CHECK_ERROR(window == NULL, SDL_GetError());

    // Create a renderer (accelerated and in sync with the display refresh rate)
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    CHECK_ERROR(renderer == NULL, SDL_GetError());

    // Init renderer
    TTF_Font* font = TTF_OpenFont("OpenSans-Regular.ttf", 25);

    // Initial renderer color
    //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    bool running = true;
    SDL_Event event;

    // Clear screen
    SDL_RenderClear(renderer);

    // Draw
    startLooper(renderer);

    // Show what was drawn
    SDL_RenderPresent(renderer);

    // Release resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_CloseFont(font);
    TTF_Quit();
    return 0;
}