//
// Created by hari0 on 16-04-2021.
//

#ifndef ANDROID_PROJECT_POINT_H
#define ANDROID_PROJECT_POINT_H

#include "import.h"
#include "Shapes.h"

class Point : public Shapes
{
public:
    Point();
    Point(int x, int y, float speed);

    int getX(){
        return x;
    }
    int getY(){
        return y;
    }

   // void Shapes::UpdateYDelta(float dT);

};



#endif //ANDROID_PROJECT_POINT_H
