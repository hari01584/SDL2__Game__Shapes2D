#pragma once

#include <SDL2/SDL.h>

class Spritesheet
{
public:
    Spritesheet();
    Spritesheet(char const* path, int row, int column);
    ~Spritesheet();

    void select_sprite(int x, int y);
    void draw_selected_sprite(SDL_Surface* window_surface, SDL_Rect* position);

    void getSize(int* w, int* h);
//private:
    SDL_Rect     m_clip;
    SDL_Surface* m_spritesheet_image;
};