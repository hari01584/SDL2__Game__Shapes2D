//
// Created by hari0 on 15-04-2021.
//

#ifndef ANDROID_PROJECT_MAINMENU_H
#define ANDROID_PROJECT_MAINMENU_H

#include "import.h"
class MainMenu
{
    //static SCENE_* EXIT_CODE;
    SDL_Event event;
    SDL_Renderer * renderer;

    void init();
    void loop();
    void RecyclePointers();
    void process_event(SDL_Event* event);
    void physUpdateObjects(float dT);


public:
    MainMenu(SDL_Renderer* sd, SCENE_* stat);
    ~MainMenu();
};

void btn1Click();


#endif //ANDROID_PROJECT_MAINMENU_H
