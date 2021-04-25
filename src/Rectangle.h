//
// Created by hari0 on 18-04-2021.
//

#ifndef ANDROID_PROJECT_RECTANGLE_H
#define ANDROID_PROJECT_RECTANGLE_H

#include "import.h"
#include "Shapes.h"

class Rectangle : public Shapes {

public:
    Rectangle();

    Rectangle(int x, int y, float speed, int w, int h);

    void checkBoundsY();
    void checkBoundsX();

    SDL_Rect getRekt();

    bool isOutOfHeight();

    int getRectLB();
};

#endif //ANDROID_PROJECT_RECTANGLE_H
