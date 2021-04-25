//
// Created by hari0 on 15-04-2021.
//

#include "MainMenu.h"
#include <time.h>
#include "dimens.h"
#include "Button.h"
#include "Point.h"

#include <SDL_image.h>
#include "9Patches.h"
#include "Rectangle.h"
#include "Circle.h"

#define MARGIN_BUTTONS 8

// 9 slice params
#define TOP 20
#define BOTTOM 20
#define LEFT 20
#define RIGHT 20


static SCENE_* EXIT_CODE;

SDL_Surface* title;
SDL_Rect titleRect;
SDL_Surface* s;

Button b1;
Button b2;
Button b3;
Button b4;

//ANIMATION
Point points[NO_OF_FALLING_POINTS_MAINSCREN];
Rectangle rectangles[NO_OF_FALLING_RECTANGLES_MAINSCREN];
Circle circles[NO_OF_FALLING_CIRLCES_MAINSCREN];

void btn1Click() {
    SDL_Log("Button");
    //*EXIT_CODE = SCENE_::quit;
}

void btn3Click() {
   // SDL_Log("Button");
    *EXIT_CODE = SCENE_::quit;
}

void startPlayGame() {
    SDL_Log("Starting Game!");
    *EXIT_CODE = SCENE_::ingame;
}

bool isInit;
MainMenu::MainMenu(SDL_Renderer* sd, SCENE_* stat) {
    renderer = sd;
    EXIT_CODE = stat;
    init();
    isInit = true;
    loop();
}

Spritesheet* test;
Spritesheet* play;
Spritesheet* option;
Spritesheet* exitsp;

void MainMenu::init() {
    IMG_Init(IMG_InitFlags::IMG_INIT_PNG);
    srand(time(NULL));

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    title = IMG_Load(TITLE_PATH);
    int tw = title->w;
    int th = title->h;
    float asp = tw/th;

    if(height>=1.5*width){
        tw = width/1.1;
        th = height/6;
    }
    else {
        tw = width / 1.5;
        th = height / 4;
    }

    int tx = (width - tw) / 2;
    int ty = (height - th) / 4;

    titleRect = { tx, ty, tw ,th };
    //titleRect = {0,0,10,10};

//    test = new Spritesheet(TITLE_PATH.c_str(), 2, 1);
//    test->setBackround(IMG_FILE,TOP,LEFT,BOTTOM,RIGHT, true);
//

    play = new Spritesheet(IMAGE_PLAY, 2, 1);
    option = new Spritesheet(IMAGE_OPTIONS, 2, 1);
    exitsp = new Spritesheet(IMAGE_EXIT, 2, 1);

    play->setNinePatch(IMAGE_PLAY_BG,TOP,LEFT,BOTTOM,RIGHT, true);
    option->setNinePatch(IMAGE_OPTIONS_BG,TOP,LEFT,BOTTOM,RIGHT, true);
    exitsp->setNinePatch(IMAGE_EXIT_BG,TOP,LEFT,BOTTOM,RIGHT, true);

    SDL_Rect dstrect = {tx,ty+ty+MARGIN_BUTTONS+height/10,tw,th/2};
    b1 = Button(play, dstrect, &startPlayGame);

    dstrect.y += th/2 + MARGIN_BUTTONS;
    b2 = Button(option, dstrect, &btn1Click);

    dstrect.y += th/2 + MARGIN_BUTTONS;
    b3 = Button(exitsp, dstrect, &btn3Click);

    //dstrect.y += bh + MARGIN_BUTTONS;
    //b4 = Button(&spr, dstrect, &btn1Click);

    //ANIMATION
    //Point
    for (int i = 0; i < NO_OF_FALLING_POINTS_MAINSCREN;i++) {
        int x = (rand() % width/5) + 1;
        int y = (rand() % height) + 1;;
        points[i] = Point(x,y,((MAX_OUT_OF_BOUNDS_Y_PARTICLE_SPEED - MIN_OUT_OF_BOUNDS_Y_PARTICLE_SPEED) * ((float)rand() / RAND_MAX)) + MIN_OUT_OF_BOUNDS_Y_PARTICLE_SPEED);
    }

    //Rect
    for (int i = 0; i < NO_OF_FALLING_RECTANGLES_MAINSCREN;i++) {
        int x = (rand() % width/5) + 1;
        int y = (rand() % height) + 1;
        int w = rand()%(width/10 -3 + 1) + 3;
        int h = rand()%(height/10 -3 + 1) + 3;

        rectangles[i] = Rectangle(x,y,((MAX_OUT_OF_BOUNDS_Y_PARTICLE_SPEED - MIN_OUT_OF_BOUNDS_Y_PARTICLE_SPEED) * ((float)rand() / RAND_MAX)) + MIN_OUT_OF_BOUNDS_Y_PARTICLE_SPEED,w,h);
    }

    //Circle
    for (int i = 0; i < NO_OF_FALLING_CIRLCES_MAINSCREN;i++) {
        int x = (rand() % width/5) + 1;
        int y = (rand() % height) + 1;
        int r = rand()%(50 - 10 + 1) + 10;

        //x = 50;
        //y = 50;
       // r = 10;

        circles[i] = Circle(x,y,((MAX_OUT_OF_BOUNDS_Y_PARTICLE_SPEED - MIN_OUT_OF_BOUNDS_Y_PARTICLE_SPEED) * ((float)rand() / RAND_MAX)) + MIN_OUT_OF_BOUNDS_Y_PARTICLE_SPEED,r);
    }

}

void MainMenu::process_event(SDL_Event* event) {
#if defined(WINDOW)
    if (event->type==SDL_QUIT){
        *EXIT_CODE = SCENE_::quit;
    }
#elif defined(ANDROID)
    if (event->type==BACK_BUTTON_PRESS){
        *EXIT_CODE = SCENE_::quit;
    }
#endif

    b1.processEvent(event);
    b2.processEvent(event);
    b3.processEvent(event);

}


void MainMenu::physUpdateObjects(float dT) {
    for (int i = 0; i < NO_OF_FALLING_POINTS_MAINSCREN;i++) {
        points[i].UpdateYDelta(dT);
    }
    SDL_RenderSetScale(renderer, 1, 1);

    for (int i = 0; i < NO_OF_FALLING_RECTANGLES_MAINSCREN;i++) {
        rectangles[i].UpdateYDelta(dT);
    }

    for (int i = 0; i < NO_OF_FALLING_CIRLCES_MAINSCREN;i++) {
        circles[i].UpdateYDelta(dT);
    }
}


void MainMenu::loop() {
    Uint32 lastupdate = SDL_GetTicks();

    while (*EXIT_CODE == SCENE_::mainmenu) {
        Uint32 current = SDL_GetTicks();
        float dT = (current - lastupdate);
        physUpdateObjects(dT);
        lastupdate = current;

        while(SDL_PollEvent(&event)) { process_event(&event); }

        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderSetScale(renderer, 5, 5);
//
//        //ANIMATE FALLERS
        for (int i = 0; i < NO_OF_FALLING_POINTS_MAINSCREN;i++) {
            SDL_RenderDrawPoint(renderer, points[i].getX(), points[i].getY());
        }
        //SDL_RenderSetScale(renderer, 1, 1);

        for (int i = 0; i < NO_OF_FALLING_RECTANGLES_MAINSCREN;i++) {
            SDL_Rect t = (rectangles[i].getRekt());
            SDL_RenderDrawRect(renderer, &t);
        }

        for (int i = 0; i < NO_OF_FALLING_CIRLCES_MAINSCREN;i++) {
            circles[i].renderCircle(renderer);
        }



        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
//

        SDL_Surface* tempSurface = SDL_CreateRGBSurface(0,width,height, 32, 0xff, 0xff00, 0xff0000, 0xff000000);

//        SDL_Rect samplerect = {0,0,width,100};


        SDL_BlitScaled(title, NULL, tempSurface, &titleRect);
        b1.renderButton(tempSurface);
        b2.renderButton(tempSurface);
        b3.renderButton(tempSurface);
        //b4.renderButton(tempSurface, &event);

        SDL_RenderSetLogicalSize(renderer, width, height);

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);

        SDL_RenderCopy(renderer, texture, NULL, NULL);


        SDL_FreeSurface(tempSurface);
        SDL_DestroyTexture(texture);
        SDL_RenderPresent(renderer);
    }
}

MainMenu::~MainMenu() {

    IMG_Quit();
    RecyclePointers();
    //TTF_Quit();
}

void MainMenu::RecyclePointers() {
    delete test;
    delete play;
    delete option;
    delete exitsp;


}

