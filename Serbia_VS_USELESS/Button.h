#pragma once
#include <SDL2\SDL_pixels.h>
#include <SDL2\SDL_ttf.h>
#include <string>
#include "SpriteSheet.h"
#include <functional>

enum BUTTON_STATE_
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3,
	BUTTON_SPRITE_TOTAL = 4
};
class Button
{
	SDL_Rect Message_rect;
	Spritesheet * sprites;
	void(*click)();

public:
	Button();
	Button(Spritesheet* s, SDL_Rect r, void(*click)());

	Spritesheet* getSprites() {
		return sprites;
	}

	SDL_Rect getRect() {
		return Message_rect;
	}

	void renderButton(SDL_Surface* surface, SDL_Event* sdl);
};

