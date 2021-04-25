//
// Created by hari0 on 15-04-2021.
//
//#import "looper.h"
#include "import.h"
#include "SCENE_.h"
#include "MainMenu.h"
#include "Game.h"
#include "GameOver.h"

void startLooper(SDL_Renderer* renderer){
    SCENE_ RENDER = SCENE_::mainmenu;
    int scores;
    while (true) {
        switch (RENDER)
        {
            case(SCENE_::quit):
                return;
            case(SCENE_::mainmenu): {
                auto* mn = new MainMenu (renderer, &RENDER);
                delete(mn);
                break;
            }
            case(SCENE_::ingame): {
                auto gm = new Game (renderer, &RENDER);
                scores = gm->getCurrentScore();
                delete(gm);
                break;
            }
            case(SCENE_::gameover): {
                auto go = new GameOver (renderer, &RENDER, &scores);
                delete(go);
                break;
            }
            default:
                break;
        }
    }
}
