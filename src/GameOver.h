//
// Created by hari0 on 24-04-2021.
//

#ifndef ANDROID_PROJECT_GAMEOVER_H
#define ANDROID_PROJECT_GAMEOVER_H

#include "SCENE_.h"
#include "import.h"
#include "dimens.h"
#include "Text.h"

class GameOver {
    SDL_Event event;
    SDL_Renderer * renderer;
    void init();
    void loop();
    void process_event(SDL_Event* event);
public:
    GameOver(SDL_Renderer *pRenderer, SCENE_ *pScene, int* scores);
    ~GameOver();
};


#endif //ANDROID_PROJECT_GAMEOVER_H
