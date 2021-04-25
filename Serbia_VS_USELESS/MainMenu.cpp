#include "MainMenu.h"
#include "SDL2/SDL.h"
#include <iostream>
#include <SDL2\SDL_ttf.h>
#include <SDL2\SDL_image.h>
#include "Button.h"
#include "dimens.h"
#include "Point.h"
#include <time.h>

#define MARGIN_BUTTONS 8

static SCENE_* EXIT_CODE;

std::string TITLE_PATH = "assets/title.png";
SDL_Surface* title;
SDL_Rect titleRect;

Spritesheet spr("assets/play.png", 2, 1);
Spritesheet play("assets/play.png", 2, 1);
Spritesheet option("assets/options.png", 2, 1);
Spritesheet exitsp("assets/exit.png", 2, 1);

Button b1;
Button b2;
Button b3;
Button b4;

//ANIMATION
Point points[2000];
int nP;


void btn1Click() {
	std::cout << "Button" << std::endl;
	*EXIT_CODE = SCENE_::quit;
}

MainMenu::MainMenu(SDL_Renderer* sd, SCENE_* stat) {
	renderer = sd;
	EXIT_CODE = stat;
	init();
	loop();
	exit();
}


void MainMenu::init() {
	TTF_Init();
	IMG_Init(IMG_InitFlags::IMG_INIT_PNG);
	srand(time(NULL));

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	title = IMG_Load(TITLE_PATH.c_str());
	int tw = title->w;
	int th = title->h;
	titleRect = { (width - tw) / 2, (height - th) / 4, tw ,th };

	int bw, bh;
	spr.getSize(&bw, &bh);
	SDL_Rect dstrect = {(width-bw)/2,(height - bh) / 2, bw ,bh };
	b1 = Button(&play, dstrect, &btn1Click);

	dstrect.y += bh + MARGIN_BUTTONS;
	b2 = Button(&option, dstrect, &btn1Click);

	dstrect.y += bh + MARGIN_BUTTONS;
	b3 = Button(&exitsp, dstrect, &btn1Click);

	//dstrect.y += bh + MARGIN_BUTTONS;
	//b4 = Button(&spr, dstrect, &btn1Click);

	//ANIMATION
	nP = rand() % (100 - 1 + 1) + 1;
	nP = 2000;
	for (int i = 0; i < nP;i++) {
		int x = (rand() % width) + 1;
		int y = (rand() % height) + 1;;

		float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

		points[i].x = x;
		points[i].y = y;
		points[i].speed = ((2 - 1) * ((float)rand() / RAND_MAX)) + 1;

		//std::cout << x << " " << y <<" " << points[i].speed << std::endl;
	}

}



void MainMenu::loop() {
	while (*EXIT_CODE != SCENE_::quit) {
		SDL_RenderClear(renderer);
		SDL_PollEvent(&event);
		if (ScreenBasics::startUpFlow(renderer, event) == -1) {
			*EXIT_CODE = SCENE_::quit;
			//return;
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderSetScale(renderer, 5, 5);

		//ANIMATE FALLERS
		for (int i = 0; i < nP;i++) {
			SDL_RenderDrawPoint(renderer, points[i].x, points[i].y);
			++points[i];
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);



		SDL_Surface* tempSurface = SDL_CreateRGBSurface(0,width,height, 32, 0xff, 0xff00, 0xff0000, 0xff000000);

		SDL_BlitSurface(title, NULL, tempSurface, &titleRect);
		b1.renderButton(tempSurface, &event);
		b2.renderButton(tempSurface, &event);
		b3.renderButton(tempSurface, &event);
		//b4.renderButton(tempSurface, &event);


		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
		SDL_RenderCopy(renderer, texture, NULL, NULL);



		SDL_FreeSurface(tempSurface);
		SDL_DestroyTexture(texture);
		SDL_RenderPresent(renderer);
	}
}

void MainMenu::exit() {
	IMG_Quit();
	TTF_Quit();
}
