#include "Button.h"
#include <SDL2\SDL_image.h>
#include <iostream>

Button::Button() {
}

Button::Button(Spritesheet* s, SDL_Rect r, void(*c)())
{
	sprites = s;
	Message_rect = r;
	click = c;
}

void Button::renderButton(SDL_Surface* surface, SDL_Event* e)
{
	sprites->select_sprite(0, 0);
	sprites->draw_selected_sprite(surface, &Message_rect);
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		if (x > Message_rect.x && x < Message_rect.x + Message_rect.w && y>Message_rect.y && y < Message_rect.y + Message_rect.h) {
			sprites->select_sprite(0, 1);
			sprites->draw_selected_sprite(surface, &Message_rect);

			if (e->type == SDL_MOUSEBUTTONDOWN) {
				click();
				SDL_Delay(100);
				return;
			}
			else if (e->type == SDL_MOUSEBUTTONUP) {
				sprites->select_sprite(0, 0);
				sprites->draw_selected_sprite(surface, &Message_rect);
			}
		}		
	}



}