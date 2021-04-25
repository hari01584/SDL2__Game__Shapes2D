//
// Created by hari0 on 18-04-2021.
//

#ifndef ANDROID_PROJECT_SHAPES_H
#define ANDROID_PROJECT_SHAPES_H

#include "import.h"

class Shapes {

protected:
    int x;
    int y;

    int h;
    int w;

    float speed;
public:
    bool isInside(int mx, int my);
    void UpdateYDelta(float dT);

    void UpdateX(float s , float dT);
    void UpdateY(float s , float dT);

    void setXY(int mx, int my);
    void getXY(int *mx, int *my);
};


#endif //ANDROID_PROJECT_SHAPES_H
