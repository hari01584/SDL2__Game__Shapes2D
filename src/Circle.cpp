//
// Created by hari0 on 19-04-2021.
//

#include "Circle.h"
#include "dimens.h"

Circle::Circle() {


}


Circle::Circle(int x, int y, float speed, int r){
    this->x=x;
    this->y=y;
    this->speed=speed;
    this->r=r;

    this->h=r;
    this->w=r;

}

void Circle::getXYR(int *mx, int *my, int *mr){
    *mx = x;
    *my = y;
    *mr = r;
}

void Circle::checkBoundsY() {
    if (y > ((height / DIMEN_FACTOR) - h)) {
        y = height / DIMEN_FACTOR - h;
    } else if (y < r) y = r;
}

bool Circle::isOutOfHeight(){
    if (y > ((height / DIMEN_FACTOR) - h)) {
        return true;
    }
    return false;
}

void Circle::checkBoundsX(){
    if(x > ((width / DIMEN_FACTOR) - w)){
        x = width/DIMEN_FACTOR -w+1;
    }
    else if(x<r) x=r;
}


 void Circle::renderCircle(SDL_Renderer * renderer)
{
    int radius = r;
    int centreX = this->x;
    int centreY = this->y;
    int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }

}
