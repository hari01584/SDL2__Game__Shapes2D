#include "SpriteSheet.h"
#include <SDL2/SDL_Surface.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2\SDL_image.h>

Spritesheet::Spritesheet(){}

Spritesheet::Spritesheet(char const* path, int row, int column)
{
    m_spritesheet_image = IMG_Load(path);

    m_clip.w = m_spritesheet_image->w / column;
    m_clip.h = m_spritesheet_image->h / row;
}

Spritesheet::~Spritesheet()
{
    SDL_FreeSurface(m_spritesheet_image);
}

void Spritesheet::select_sprite(int x, int y)
{
    m_clip.x = x * m_clip.w;
    m_clip.y = y * m_clip.h;
}

void Spritesheet::getSize(int* w, int* h) {
    *w = m_clip.w;
    *h = m_clip.h;
}

void Spritesheet::draw_selected_sprite(SDL_Surface* window_surface, SDL_Rect* position)
{
    SDL_BlitSurface(m_spritesheet_image, &m_clip, window_surface, position);
}