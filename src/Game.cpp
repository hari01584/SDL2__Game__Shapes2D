//
// Created by hari0 on 17-04-2021.
//
#include "Game.h"
#include "Shapes.h"
#include "Rectangle.h"
#include "FileOperations.h"
#include "Button.h"
#include "Text.h"
#include "import.h"
#include "Circle.h"
#include <cmath>

#define MARGIN_TEXT 12
#define TOP 20
#define BOTTOM 20
#define LEFT 20
#define RIGHT 20

SCENE_* EXIT_CODE;


Shapes* object;
const SDL_Color friendColor = {0, 255, 255, 255};
const SDL_Color defaultColor = {255, 255, 255, 255};

const SDL_Color enemyRectColor = {255,102,102,255};
const SDL_Color enemyCirColor = {255,178,102,255};
const SDL_Color friendRectColor = {51,255,255,255};
const SDL_Color friendCirColor = {51,255,153,255};

#if defined(ANDROID)
const int sqrSize = sqrt(height*width)/(2*DIMEN_FACTOR);
bool isObjectTouch = false;
#elif defined(WINDOW)
//const int sqrSize = width/(DIMEN_FACTOR*6);
const int sqrSize = sqrt(height*width)/(6*DIMEN_FACTOR);
#endif

TTF_Font* font;
TTF_Font* fontMedium;
TTF_Font* fontSmall;
TTF_Font *fontXtraLarge;

const float objectSpeed = 2;
const float enemySpeed = 0.145;

bool isRectObject = true;
Text* ScoreBoard;
Text* Morph;
int scores;

int fps;
bool isDoubleClick;
int morph_times;
float BasefallSpeed;

#if defined(ANDROID)
int BASE_NO_OF_ENEMY_RECT;
int BASE_NO_OF_ENEMY_CIRLCE;
int BASE_NO_OF_FRIEND_RECT;
int BASE_NO_OF_FRIEND_CIRCLE;
#else
int BASE_NO_OF_ENEMY_RECT;
int BASE_NO_OF_ENEMY_CIRLCE;
int BASE_NO_OF_FRIEND_RECT;
int BASE_NO_OF_FRIEND_CIRCLE;
#endif

int CURRENT_NO_OF_ENEMY_RECT;
int CURRENT_NO_OF_ENEMY_CIRLCE;
int CURRENT_NO_OF_FRIEND_RECT;
int CURRENT_NO_OF_FRIEND_CIRCLE;


Rectangle* enemyRectangles[9];
Rectangle* friendRectangles[9];
Circle* enemyCircles[9];
Circle* friendCircles[9];

bool babyProtocol = false;
Text *b01, *b02, *b03, *b04, *timer;
Spritesheet *babyInfoSp,*babyConfirmSp;
Button babyConfirm;

int randomval;
bool lock = false;
bool lockF = false;

void confirmBaby(){
    FileOp::saveOptionData.firstTimeEntry = false;
    FileOp::saveConfigBin();
    babyProtocol = false;
}

Game::Game(SDL_Renderer* sd, SCENE_* stat) {
    renderer = sd;
    EXIT_CODE = stat;
    init();
    loop();
}

void Game::init(){

    scores = 0;
    fps  = 0;
    isDoubleClick = false;
    morph_times = 6;
    BasefallSpeed = 1.2;
#if defined(ANDROID)
    BASE_NO_OF_ENEMY_RECT = 4;
    BASE_NO_OF_ENEMY_CIRLCE = 4;
    BASE_NO_OF_FRIEND_RECT = 2;
    BASE_NO_OF_FRIEND_CIRCLE = 2;
#else
    BASE_NO_OF_ENEMY_RECT = 2;
    BASE_NO_OF_ENEMY_CIRLCE = 2;
    BASE_NO_OF_FRIEND_RECT = 2;
    BASE_NO_OF_FRIEND_CIRCLE = 2;
#endif

    CURRENT_NO_OF_ENEMY_RECT=0;
    CURRENT_NO_OF_ENEMY_CIRLCE=0;
    CURRENT_NO_OF_FRIEND_RECT=0;
    CURRENT_NO_OF_FRIEND_CIRCLE=0;

    randomval;
    lock = false;
    lockF = false;


    IMG_Init(IMG_InitFlags::IMG_INIT_PNG);

    babyProtocol = FileOp::saveOptionData.firstTimeEntry;
    if(babyProtocol){
        SDL_Log("First time entry detected, starting baby protocol");
        babyInfoSp = new Spritesheet(BABY_INFO_INSTR, 1, 1);
        babyInfoSp->select_sprite(0,0);
        babyInfoSp->setNinePatch(BABY_INFO_BG, 20, 20, 20, 20, false);

        babyConfirmSp = new Spritesheet(BABY_CONFIRM, 2, 1);
        babyConfirmSp->select_sprite(0,0);
        babyConfirmSp->setNinePatch(BABY_CONFIRM_BG, TOP, BOTTOM, LEFT, RIGHT, false);
        //b01 = new Text();
    }

    TTF_Init();
    fontXtraLarge = TTF_OpenFont(FONT_OPENSANS, 60);
    font = TTF_OpenFont(FONT_OPENSANS, 48);
    fontMedium = TTF_OpenFont(FONT_OPENSANS, 36);
    fontSmall = TTF_OpenFont(FONT_OPENSANS, 18);

    if(babyProtocol){
        SDL_Color c= {255,255,255};
        SDL_Rect rect = {25,30,-1,-1};
        int w,h;
        b01 = new Text(renderer,font,HEADER_BABY,c,rect);
        TTF_SizeText(font, HEADER_BABY, &w, &h);

        rect.y += h+MARGIN_TEXT+5;
        //rect.w = -1;
        b02 = new Text(renderer,font,S02_BABY,c,rect);
        TTF_SizeText(font, HEADER_BABY, &w, &h);

        rect.y += h+MARGIN_TEXT;
        b03 = new Text(renderer,font,S03_BABY,c,rect);

        rect.y += h+MARGIN_TEXT;
        b04 = new Text(renderer,font,S04_BABY,c,rect);

        rect.h = 200;
        rect.y = height - rect.h - 20 - MARGIN_TEXT;
        rect.w = width-40;


        babyConfirm = Button(babyConfirmSp, rect, &confirmBaby);
    }

    int ix = ((width/DIMEN_FACTOR)-sqrSize)/2;
    int iy = ((height/DIMEN_FACTOR)-sqrSize)/2;
    object = new Rectangle(ix,iy,0,sqrSize,sqrSize);
    int w,h;
    SDL_Color orange= {255,69,0};

#if defined(ANDROID)
    TTF_Font* tFont = fontXtraLarge;
#else
    TTF_Font* tFont = fontMedium;
#endif
    TTF_SizeText(tFont, "Scores:", &w, &h);
    SDL_Rect scoreRect = {20,20,w , h};
    ScoreBoard = new Text(renderer, tFont, "Scores:",orange,scoreRect);

    //scoreRect.x += width/2;

    TTF_SizeText(tFont, "M:0", &w, &h);

    scoreRect.x = width - 20 - w;
    scoreRect.w = w;
    Morph = new Text(renderer, tFont, "M:0",orange,scoreRect);
}


void Game::process_event(SDL_Event* event) {
#if defined(WINDOW)
    if (event->type==SDL_QUIT){
        *EXIT_CODE = SCENE_::quit;
        return;
    }

    if(event->type == SDL_KEYDOWN){
        switch( event->key.keysym.sym )
        {
            case SDLK_w:
                objectPos = POSITION_::up;
                break;

            case SDLK_s:
                objectPos = POSITION_::down;
                break;

            case SDLK_a:
                objectPos = POSITION_::left;
                break;

            case SDLK_d:
                objectPos = POSITION_::right;
                break;
            case SDLK_c:
                objectPos = POSITION_::morph;
                break;
            default:
                break;
        }
    }

    if(babyProtocol) {
        babyConfirm.processEvent(event);
        return;
    }

#elif defined(ANDROID)
    if (event->type==BACK_BUTTON_PRESS){
        *EXIT_CODE = SCENE_::quit;
    }

    if(babyProtocol) {
        babyConfirm.processEvent(event);
        return;
    }
    if(event->type==SDL_FINGERDOWN || event->type==SDL_FINGERUP || event->type==SDL_FINGERMOTION){
        int x = width * event->tfinger.x;
        int y = height * event->tfinger.y;
        if(event->type == SDL_FINGERDOWN && isDoubleClick){
            morphObject();
        }
        if(event->type==SDL_FINGERDOWN && object->isInside(x/3,y/3) && !isObjectTouch){
            isObjectTouch = true;
            isDoubleClick = true;
        }
        else if(event->type==SDL_FINGERMOTION && isObjectTouch){
            object->setXY(x/3,y/3);
            callCheckBoundX();
            callCheckBoundY();

        }
        else if(event->type==SDL_FINGERUP){
            isObjectTouch = false;
        }
    }

#endif
}


void Game::callCheckBoundX() {
    if(isRectObject){
        ((Rectangle*)object)->checkBoundsX();
    }
    else{
        ((Circle*)object)->checkBoundsX();
    }
}

void Game::callCheckBoundY() {
    if(isRectObject){
        ((Rectangle*)object)->checkBoundsY();
    }
    else{
        ((Circle*)object)->checkBoundsY();
    }
}

void Game::physUpdateObjects(float dT) {
    if(objectPos==POSITION_::up){
        object->UpdateY(-objectSpeed,dT);
        callCheckBoundY();
        objectPos = POSITION_::idle;
    }
    else if(objectPos==POSITION_::down){
        object->UpdateY(objectSpeed,dT);
        callCheckBoundY();
        objectPos = POSITION_::idle;
    }
    else if(objectPos==POSITION_::left){
        object->UpdateX(-objectSpeed,dT);
        callCheckBoundX();
        objectPos = POSITION_::idle;
    }
    else if(objectPos==POSITION_::right){
        object->UpdateX(objectSpeed,dT);
        callCheckBoundX();
        objectPos = POSITION_::idle;
    }
    else if(objectPos==POSITION_::morph){
        morphObject();
    }
//Movement over
     float speed = enemySpeed + scores / 1000;

    for(int i=0;i<CURRENT_NO_OF_ENEMY_CIRLCE;i++){
        enemyCircles[i]->UpdateY(speed,dT);
        if(enemyCircles[i]->isOutOfHeight()){
            spawnEnemyCircle(i);
        }
        if(collisonDetectorCircle(enemyCircles[i])){
            ReduceHealthPoints();
            spawnEnemyCircle(i);
        }
    }
    for(int i=0;i<CURRENT_NO_OF_ENEMY_RECT;i++){
        enemyRectangles[i]->UpdateY(speed,dT);
        if(enemyRectangles[i]->isOutOfHeight()){
            spawnEnemyRectangle(i);
        }
        if(collisonDetectorRectangle(enemyRectangles[i])){
            ReduceHealthPoints();
            spawnEnemyRectangle(i);
        }
    }


    for(int i=0;i<CURRENT_NO_OF_FRIEND_CIRCLE;i++){
        friendCircles[i]->UpdateY(speed,dT);
        if(friendCircles[i]->isOutOfHeight()){
            spawnFriendCircle(i);
        }
        if(collisonDetectorCircle(friendCircles[i])){
            IncreaseHealthPoints();
            spawnFriendCircle(i);
        }
    }
    for(int i=0;i<CURRENT_NO_OF_FRIEND_RECT;i++){
        friendRectangles[i]->UpdateY(speed,dT);
        if(friendRectangles[i]->isOutOfHeight()){
            spawnFriendRectangle(i);
        }
        if(collisonDetectorRectangle(friendRectangles[i])){
            IncreaseHealthPoints();
            spawnFriendRectangle(i);
        }
    }
    //scores += dT/10;
}

inline void Game::morphObject(){
    int mx,my;
    object->getXY(&mx,&my);
    delete object;
    if(isRectObject){
        int r = rand()%(sqrSize - 20 + 1) + 20;
        object = new Circle(mx+r/2,my+r/2,0.0f,r);
        isRectObject = false;
    }
    else{
        object = new Rectangle(mx-20,my-20,0,sqrSize,sqrSize);
        isRectObject = true;
    }

    objectPos = POSITION_::idle;
}

void Game::loop(){
    Uint32 lastupdate = SDL_GetTicks();
    Uint32 oneSec = 0;
    Uint32 tenSec = 0;
    while (*EXIT_CODE == SCENE_::ingame) {
        Uint32 current = SDL_GetTicks();
        float dT = (current - lastupdate);
        physUpdateObjects(dT);
        oneSec+=dT;
        tenSec+=dT;
        if(oneSec > 1000){
            isDoubleClick = false;
            scores+=1;
            oneSec=0;
        }
        if(tenSec > 10000){
            increaseDifficulty();
            tenSec=0;
        }
        lastupdate = current;
        spawnShapes(lastupdate);


        while(SDL_PollEvent(&event)) { process_event(&event); }
        SDL_SetRenderDrawColor(renderer, defaultColor.r, defaultColor.g, defaultColor.b, defaultColor.a);

        SDL_RenderClear(renderer);
        SDL_Surface* tempSurface = SDL_CreateRGBSurface(0,width,height, 32, 0xff, 0xff00, 0xff0000, 0xff000000);
        SDL_RenderSetLogicalSize(renderer, width, height);

        //BabyMode
        if(babyProtocol){
            SDL_Rect sdl = {0,0,width,height};
            babyInfoSp->draw_9patch_sprite(tempSurface,&sdl);

            babyConfirm.renderButton(tempSurface);

            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
            SDL_RenderCopy(renderer, texture, NULL, NULL);

            b01->renderText(renderer);
            b02->renderText(renderer);
            b03->renderText(renderer);
            b04->renderText(renderer);


            SDL_FreeSurface(tempSurface);
            SDL_DestroyTexture(texture);
            SDL_RenderPresent(renderer);
            continue;
        }


        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        SDL_RenderCopy(renderer, texture, NULL, NULL);

        std::string score = "Scores: "+ std::to_string(scores);
        ScoreBoard->dynamicRender(renderer, score.c_str());
        std::string morph = "M: "+ std::to_string(morph_times);
        Morph->dynamicRender(renderer,morph.c_str());

        SDL_SetRenderDrawColor(renderer, friendColor.r, friendColor.g, friendColor.b, friendColor.a);

        //Render here
        SDL_RenderSetScale(renderer,3,3);

        if(isRectObject) {
            SDL_Rect sdl = ((Rectangle *) object)->getRekt();
            SDL_RenderDrawRect(renderer, &sdl);
        }
        else{
            ((Circle*) object)->renderCircle(renderer);
        }

        //CREATE LOGIC ENEMY FALLIN FRIEND FALLIN SHAPES!!
        SDL_SetRenderDrawColor(renderer, enemyCirColor.r, enemyCirColor.g, enemyCirColor.b, enemyCirColor.a);
        for(int i=0;i<CURRENT_NO_OF_ENEMY_CIRLCE;i++){
            enemyCircles[i]->renderCircle(renderer);
        }

        SDL_SetRenderDrawColor(renderer, enemyRectColor.r, enemyRectColor.g, enemyRectColor.b, enemyRectColor.a);
        for(int i=0;i<CURRENT_NO_OF_ENEMY_RECT;i++){
            SDL_Rect r = enemyRectangles[i]->getRekt();
            SDL_RenderDrawRect(renderer,&r);
        }

        SDL_SetRenderDrawColor(renderer, friendCirColor.r, friendCirColor.g, friendCirColor.b, friendCirColor.a);
        for(int i=0;i<CURRENT_NO_OF_FRIEND_CIRCLE;i++){
            friendCircles[i]->renderCircle(renderer);
        }

        SDL_SetRenderDrawColor(renderer, friendCirColor.r, friendCirColor.g, friendCirColor.b, friendCirColor.a);
        for(int i=0;i<CURRENT_NO_OF_FRIEND_RECT;i++){
            SDL_Rect r = friendRectangles[i]->getRekt();
            SDL_RenderDrawRect(renderer,&r);
        }


        SDL_FreeSurface(tempSurface);
        SDL_DestroyTexture(texture);
        SDL_RenderPresent(renderer);

    }

}


void Game::spawnShapes(Uint32 time) {
    if(time<randomval){
        return;
    }

    randomval = time + rand()%(1000-500 + 1) + 500;

    int ranAccess;
    int n = 2;

    ranAccess = rand() % 2;
    if(!ranAccess) return;

    if(CURRENT_NO_OF_ENEMY_CIRLCE < BASE_NO_OF_ENEMY_CIRLCE /*+ Some calculation */ && !lock){
        spawnEnemyCircle(CURRENT_NO_OF_ENEMY_CIRLCE++);
        lock = true;
    }
    else if(CURRENT_NO_OF_ENEMY_RECT < BASE_NO_OF_ENEMY_RECT /*+ Some calculation */){
        spawnEnemyRectangle(CURRENT_NO_OF_ENEMY_RECT++);
        lock = false;
    }

    if(CURRENT_NO_OF_FRIEND_CIRCLE < BASE_NO_OF_FRIEND_CIRCLE /*+ Some calculation */ && !lockF){
        spawnFriendCircle(CURRENT_NO_OF_FRIEND_CIRCLE++);
        lockF = true;
    }
    else if(CURRENT_NO_OF_FRIEND_RECT < BASE_NO_OF_FRIEND_RECT /*+ Some calculation */){
        spawnFriendRectangle(CURRENT_NO_OF_FRIEND_RECT++);
        lockF = false;
    }
}


void Game::spawnEnemyRectangle(int bufferPos){
    if(enemyRectangles[bufferPos]!=NULL){
        delete enemyRectangles[bufferPos];
    }

    int x = (rand() % width/DIMEN_FACTOR) + 1;
    int l = rand()%(40 - 10 + 1) + 10;
    enemyRectangles[bufferPos] = new Rectangle(x,0,1,l,l);
}

void Game::spawnEnemyCircle(int bufferPos){
    if(enemyCircles[bufferPos]!=NULL){
        delete enemyCircles[bufferPos];
    }

    int x = (rand() % width/DIMEN_FACTOR) + 1;
    int r = rand()%(40 - 10 + 1) + 10;
    enemyCircles[bufferPos] = new Circle(x,0,1,r);
}


void Game::spawnFriendCircle(int bufferPos) {
    if(friendCircles[bufferPos]!=NULL){
        delete friendCircles[bufferPos];
    }

    int x = (rand() % width/DIMEN_FACTOR) + 1;
    int r = rand()%(40 - 10 + 1) + 10;
    friendCircles[bufferPos] = new Circle(x,0,1,r);
}


void Game::spawnFriendRectangle(int bufferPos) {
    if(friendRectangles[bufferPos]!=NULL){
        delete friendRectangles[bufferPos];
    }

    int x = (rand() % width/DIMEN_FACTOR) + 1;
    int l = rand()%(40 - 10 + 1) + 10;
    friendRectangles[bufferPos] = new Rectangle(x,0,1,l,l);
}


void Game::IncreaseHealthPoints() {
    morph_times += 1;
}


void Game::ReduceHealthPoints() {
    morph_times -= 1;
    if(morph_times<=0){
        *EXIT_CODE = SCENE_::gameover;
    }
}


bool Game::collisonDetectorCircle(Circle* circle) {
    int mx,my,mr;
    circle->getXYR(&mx,&my,&mr);
    if(isRectObject){
        int cx,cy,cr;
        object->getXY(&cx,&cy);
        cr = ((Rectangle*)object)->getRectLB();

        int cenX = cx + (cr/2);
        int cenY = cy + (cr/2);

        return sqrt(pow(cenX - mx, 2) + pow(cenY - my, 2) * 1.0) < (cr/2) + mr;

    }
    else{
        int tx,ty,tr;
        ((Circle*)object)->getXYR(&tx,&ty,&tr);
        return sqrt(pow(tx - mx, 2) + pow(ty - my, 2) * 1.0) < tr + mr;
    }
}


bool Game::collisonDetectorRectangle(Rectangle *rect) {
    if(isRectObject){
        SDL_Rect tR = ((Rectangle*)object)->getRekt();
        SDL_bool collision = SDL_HasIntersection(&tR, reinterpret_cast<const SDL_Rect *>(rect));
        return collision;
    }
    else{
        int mx,my,mr;
        ((Circle*)object)->getXYR(&mx,&my,&mr);

        int cx,cy,cr;
        rect->getXY(&cx,&cy);
        cr = rect->getRectLB();

        int cenX = cx + (cr/2);
        int cenY = cy + (cr/2);

        return sqrt(pow(cenX - mx, 2) + pow(cenY - my, 2) * 1.0) < (cr/2) + mr;
    }
}



void Game::increaseDifficulty() {
    BASE_NO_OF_ENEMY_CIRLCE += 1;
    BASE_NO_OF_ENEMY_RECT += 1;
}

int Game::getCurrentScore(){
    return scores;
}


Game::~Game(){
    IMG_Quit();

    TTF_CloseFont(font);
    TTF_CloseFont(fontSmall);
    TTF_CloseFont(fontMedium);
    TTF_CloseFont(fontXtraLarge);
    TTF_Quit();

    if(babyProtocol) {
        delete babyInfoSp;
        delete b01;
        delete b02;
        delete b03;
        delete b04;
        delete babyConfirmSp;
        delete timer;
    }
    delete object;
    delete ScoreBoard;
    delete Morph;

    for(int i=0;i<CURRENT_NO_OF_ENEMY_CIRLCE;i++){
       //delete enemyCircles[i];
    }
    for(int i=0;i<9;i++){
        //delete enemyRectangles[i];
    }
    for(int i=0;i<9;i++){
        //delete friendCircles[i];
    }
    for(int i=0;i<9;i++){
        //delete friendRectangles[i];
    }
}
