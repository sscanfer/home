#include <stdio.h>
#include "circle.h"

// Circle 虚函数
static unsigned int Circle_Area(const Shape * const shapePtr);
static void Circle_Draw(const Shape * const shapePtr);

// Circle 构造函数
void Circle_Ctor(Circle * const circlePtr, int x, int y, unsigned int radius)
{
    const static struct ShapeVtbl vtbl = {
        Circle_Area,
        Circle_Draw
    };
    Shape_Ctor(&circlePtr->super, x, y);   // 调用基类的构造函数
    circlePtr->super.vptr = &vtbl;        // 重载 vptr
    circlePtr->radius     = radius;
    return;
}

// Cirlcle 虚函数的实现
static unsigned int Circle_Area(const Shape * const shapePtr)
{
    const Circle * const circlePtr = (const Circle *)shapePtr;
    return (unsigned int)(PI * circlePtr->radius * circlePtr->radius);
}

static void Circle_Draw(const Shape * const shapePtr)
{
    const Circle * const circlePtr = (const Circle *)shapePtr;
    printf("Circle_Draw(x=%d,y=%d,radius=%d)\n",
           Shape_GetX(shapePtr), Shape_GetY(shapePtr), circlePtr->radius);
    return;
}