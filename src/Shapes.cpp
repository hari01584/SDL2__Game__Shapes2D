//
// Created by hari0 on 18-04-2021.
//

#include "Shapes.h"
#include "dimens.h"
#include "Circle.h"
#include "Rectangle.h"
#include <stdlib.h>


void Shapes::UpdateYDelta(float dT){
    //x += speed;
    //SDL_Log("Definately %f",dT);
    y += speed * dT/10;

    if (y >= height) {
        speed = (( MAX_OUT_OF_BOUNDS_Y_PARTICLE_SPEED - MIN_OUT_OF_BOUNDS_Y_PARTICLE_SPEED ) * ((float)rand() / RAND_MAX)) + MIN_OUT_OF_BOUNDS_Y_PARTICLE_SPEED;
        y = 0;
    }
}


void Shapes::UpdateY(float s , float dT){
    y += s * dT;
}


void Shapes::UpdateX(float s , float dT){
    x += s * dT;
}


bool Shapes::isInside(int mx, int my) {
    return mx > x && mx < x + w && my > y && my < y + h;
}

void Shapes::setXY(int mx, int my) {
    x = mx - w/2;
    y = my - h;
}

void Shapes::getXY(int *mx, int *my){
    *mx = x;
    *my = y;
}
