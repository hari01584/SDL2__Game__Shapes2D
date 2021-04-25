#include "Point.h"
#include "dimens.h"
#include <cstdlib>

void Point::operator++()
{
    //x += speed;
    y += speed;
    
    if (y >= height) {
        speed = ((4 - 1) * ((float)rand() / RAND_MAX)) + 1;
        y = 0;
    }


}
