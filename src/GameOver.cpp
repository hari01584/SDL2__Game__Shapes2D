//
// Created by hari0 on 24-04-2021.
//

#include "GameOver.h"
#include "Game.h"


static SCENE_ *EXIT_CODE;

static TTF_Font * font;
Text * gameov, *it1, *it2;
int *score;

GameOver::GameOver(SDL_Renderer *pRenderer, SCENE_ *pScene, int* scores) {
    renderer = pRenderer;
    EXIT_CODE = pScene;
    score = scores;

    init();
    loop();
}


void GameOver::init() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderSetScale(renderer,1,1);
    TTF_Init();
    font = TTF_OpenFont(FONT_OPENSANS, 42);

    SDL_Color orange= {255,69,0};

    int w,h;
    std::string gmscore = "Game Over :(, Score:"+std::to_string(*score);
    TTF_SizeText(font, gmscore.c_str(), &w, &h);
    w = width/3;

    SDL_Rect rect = {(width-w)/2,(height-h)/3,w,h};
    gameov = new Text(renderer, font, gmscore.c_str(),orange,rect);

    rect.y+=(height-h)/4;
    rect.w+=20;
    it2 = new Text(renderer, font, "Restarting in 5 seconds.",orange,rect);

    const char* quote = (gameover_quotes[rand() % 10]).c_str();

    TTF_SizeText(font, quote, &w, &h);
#if defined(ANDROID)
    h = (w/width) * 4* 48;
#else
    h *= (w/width);
    h+=10;
#endif
    SDL_Rect quoterec = {0,5,width,h+10};
    it1 = new Text(renderer, font, quote,orange,quoterec);
}

void GameOver::process_event(SDL_Event* event) {
#if defined(WINDOW)
    if (event->type==SDL_QUIT){
        *EXIT_CODE = SCENE_::quit;
    }
#elif defined(ANDROID)
    if (event->type==BACK_BUTTON_PRESS){
        *EXIT_CODE = SCENE_::quit;
    }
#endif

}

void GameOver::loop() {
    Uint32 lastupdate = SDL_GetTicks();
    Uint32 oneSec = 0;
    int thsectimer = 5;
    while(*EXIT_CODE == SCENE_::gameover){
        Uint32 current = SDL_GetTicks();
        float dT = (current - lastupdate);
        oneSec+=dT;
        if(oneSec > 1000){
            thsectimer-=1;
            oneSec=0;
        }
        lastupdate = current;
        if(thsectimer<0){
            *EXIT_CODE = SCENE_::ingame;
        }

        while(SDL_PollEvent(&event)) { process_event(&event); }

        SDL_RenderClear(renderer);

        SDL_Surface* tempSurface = SDL_CreateRGBSurface(0,width,height, 32, 0xff, 0xff00, 0xff0000, 0xff000000);



        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);

        SDL_RenderCopy(renderer, texture, NULL, NULL);
        gameov->renderText(renderer);
        it1->renderText(renderer);

        std::string stin = "Restarting in "+ std::to_string(thsectimer) + "seconds.";
        it2->dynamicRender(renderer, stin.c_str());

        SDL_FreeSurface(tempSurface);
        SDL_DestroyTexture(texture);
        SDL_RenderPresent(renderer);

    }
}

GameOver::~GameOver() {
    TTF_CloseFont(font);
    TTF_Quit();

    delete gameov;
    delete it1;
    delete it2;
}
