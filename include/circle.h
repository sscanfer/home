#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

#define PI 3.1415926
typedef struct {
    Shape super;    // 继承 Shape

    // 自己的属性
    unsigned int radius;
} Circle;

void Circle_Ctor(Circle * const circlePtr, int x, int y, unsigned int radius);

#endif /* CIRCLE_H */