//
// Created by hari0 on 18-04-2021.
//

#include "Rectangle.h"
#include "dimens.h"


SDL_Rect Rectangle::getRekt(){
    SDL_Rect rect = {x,y,w,h};
    return rect;
}

Rectangle::Rectangle(){

}

Rectangle::Rectangle(int x, int y, float speed, int w, int h) {
    this->w=w;
    this->h=h;
    this->x=x;
    this->y=y;
    this->speed=speed;
}

void Rectangle::checkBoundsY() {
    if (y > ((height / DIMEN_FACTOR) - h)) {
        y = height / DIMEN_FACTOR - h;
    } else if (y < 0) y = 0;
}

int Rectangle::getRectLB(){
    return w;
}

void Rectangle::checkBoundsX(){
    if(x > ((width / DIMEN_FACTOR) - w)){
        x = width/DIMEN_FACTOR -w+1;
    }
    else if(x<0) x=0;
}

bool Rectangle::isOutOfHeight(){
    if (y > ((height / DIMEN_FACTOR) - h)) {
        return true;
    }
    return false;
}