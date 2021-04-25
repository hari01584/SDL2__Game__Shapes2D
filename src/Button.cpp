//
// Created by hari0 on 15-04-2021.
//

#include "Button.h"
#include "dimens.h"


Button::Button() {
}

Button::Button(Spritesheet* s, SDL_Rect r, void(*c)())
{
    sprites = s;
    Message_rect = r;
    click = c;
}

void Button::processEvent(SDL_Event *e) {
#if defined(WINDOW)

    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x > Message_rect.x && x < Message_rect.x + Message_rect.w && y>Message_rect.y && y < Message_rect.y + Message_rect.h) {
            if (e->type == SDL_MOUSEBUTTONDOWN && buttonRelease) {
                sprites->select_sprite(0, 1);
                buttonClick = true;
                buttonRelease = false;
            }
            else if (e->type == SDL_MOUSEBUTTONUP && buttonClick) {
                sprites->select_sprite(0, 1);
                click();
                buttonClick = false;
                buttonRelease = true;
            }
            else if(e->type == SDL_MOUSEMOTION){
                sprites->select_sprite(0, 1);
            }
        }
        else if(e->type == SDL_MOUSEMOTION){
            sprites->select_sprite(0, 0);
        }
    }
    else{
        sprites->select_sprite(0, 0);
    }

#elif defined(ANDROID)
    if(e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP){
        int x = width * e->tfinger.x;
        int y = height * e->tfinger.y;
        if (x > Message_rect.x && x < Message_rect.x + Message_rect.w && y>Message_rect.y && y < Message_rect.y + Message_rect.h) {
            if(e->type == SDL_FINGERDOWN){
                sprites->select_sprite(0, 1);
                buttonClick = true;
            }
            else if (e->type == SDL_FINGERUP && buttonClick) {
                sprites->select_sprite(0, 0);
                click();
                buttonClick = false;
            }
        }
    }
    else if(!buttonClick){
        sprites->select_sprite(0, 0);
    }

#endif

}

void Button::renderButton(SDL_Surface* surface)
{
//#if defined(WINDOW)
//
//#elif defined(ANDROID)
//    if(e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP){
//        int x = width * e->tfinger.x;
//        int y = height * e->tfinger.y;
//        if (x > Message_rect.x && x < Message_rect.x + Message_rect.w && y>Message_rect.y && y < Message_rect.y + Message_rect.h) {
//            if(e->type == SDL_FINGERDOWN){
//                sprites->select_sprite(0, 1);
//                buttonClick = true;
//                while(SDL_PollEvent(e)); //Clears the buffer
//            }
//            else if (e->type == SDL_FINGERUP && buttonClick) {
//                sprites->select_sprite(0, 0);
//                click();
//                buttonClick = false;
//                while(SDL_PollEvent(e)); //Clears the buffer
//
//            }
//        }
//    }
//    else if(!buttonClick){
//        sprites->select_sprite(0, 0);
//    }
//
//#endif

    sprites->draw_selected_sprite(surface, &Message_rect);

}