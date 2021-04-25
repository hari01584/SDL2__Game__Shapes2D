#include "SDL2/SDL.h"
#include "utility.h"
#include "looper.h"
#include "enums.h"
#include <iostream>

#pragma once
namespace ScreenBasics
{
     inline int startUpFlow(SDL_Renderer* sdl,SDL_Event event) {
         if (event.type == SDL_QUIT) {
             return -1;
         }

        if (event.type == SDL_KEYDOWN) {
            const char* key = SDL_GetKeyName(event.key.keysym.sym);
            if (strcmp(key, "C") == 0) {
                SDL_SetRenderDrawColor(sdl, randInt(0, 255), randInt(0, 255), randInt(0, 255), 255);
            }
        }
	}
};

