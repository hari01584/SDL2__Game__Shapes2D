#include <SDL2/SDL.h>
#include "MainMenu.h"


void startLooper(SDL_Renderer* renderer) {
	SCENE_ RENDER = SCENE_::mainmenu;
	while (true) {
		switch (RENDER)
		{
			case(SCENE_::quit):
				return;
			case(SCENE_::mainmenu):
				MainMenu mn(renderer, &RENDER);
				break;
		}
	}
}