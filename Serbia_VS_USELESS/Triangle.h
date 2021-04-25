#include "SDL2/SDL.h"

#pragma once
class Triangle
{
	SDL_Point points[3];
	int thickness;
	float speed;

public:
	Triangle(int th);
	SDL_Point* getPoints(int center);
};

