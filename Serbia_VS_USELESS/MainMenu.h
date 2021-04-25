#include "SDL2/SDL.h"
#include "CONSTANT_SCREEN.h"
#pragma once
class MainMenu
{
	//static SCENE_* EXIT_CODE;
	SDL_Event event;
	SDL_Renderer * renderer;
	public:
		MainMenu(SDL_Renderer* sd, SCENE_* stat);

	void init();
	void loop();
	void exit();


};

void btn1Click();

