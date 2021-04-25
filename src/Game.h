//
// Created by hari0 on 17-04-2021.
//

#ifndef ANDROID_PROJECT_GAME_H
#define ANDROID_PROJECT_GAME_H

#include "import.h"
#include "dimens.h"
#include "POSITION_.h"
#include "Rectangle.h"
#include "Circle.h"

class Game
{
    //static SCENE_* EXIT_CODE;
    SDL_Event event;
    SDL_Renderer * renderer;
    void  process_event(SDL_Event* event);
    void init();
    void loop();
    POSITION_ objectPos;
    void physUpdateObjects(float t);
    void morphObject();
    void callCheckBoundX();
    void callCheckBoundY();
    void spawnShapes(Uint32 time);
    void spawnEnemyRectangle(int bufferPos);
    void spawnEnemyCircle(int bufferPos);
    bool collisonDetectorRectangle(Rectangle *rect);
    bool collisonDetectorCircle(Circle *circle);
    void ReduceHealthPoints();
    void spawnFriendCircle(int bufferPos);
    void IncreaseHealthPoints();
    void spawnFriendRectangle(int i);
    void increaseDifficulty();

public:
    Game(SDL_Renderer* sd, SCENE_* stat);
    ~Game();

    int getCurrentScore();
};


#endif //ANDROID_PROJECT_GAME_H
