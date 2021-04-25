//
// Created by hari0 on 19-04-2021.
//

#ifndef ANDROID_PROJECT_CIRCLE_H
#define ANDROID_PROJECT_CIRCLE_H

#include "import.h"
#include "Shapes.h"

class Circle : public Shapes{
    int r;
public:
    Circle();
    Circle(int x, int y, float speed, int r);
    void renderCircle(SDL_Renderer * sdlRenderer);

    void checkBoundsY();
    void checkBoundsX();
    bool isOutOfHeight();
    void getXYR(int *mx, int *my, int *mr);
};


#endif //ANDROID_PROJECT_CIRCLE_H
