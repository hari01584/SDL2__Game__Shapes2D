#ifndef MONSTER_H
#define MONSTER_H

#include <SDL.h>

#include <iostream>
#include <string>
#include "SCENE_.h"

#include "Spritesheet.h"
#include <SDL_image.h>
#include <SDL_ttf.h>


#if defined(ANDROID) || defined(__ANDROID__)
#define ANDROID "ANDROID"
#elif __APPLE__
#define LINUX "LINUX"
#else
#define WINDOW "WINDOW"
#endif

#endif
