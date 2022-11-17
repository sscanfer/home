#include <stdio.h>
#include "rectangle.h"

// Rectangle 虚函数
static unsigned int Rectangle_Area(const Shape * const shapePtr);
static void Rectangle_Draw(const Shape * const shapePtr);

// 构造函数
void Rectangle_Ctor(Rectangle * const   rectPtr,
                    int                 x,          int             y,
                    unsigned int        width,      unsigned int    height)
{
    const static struct ShapeVtbl vtbl = {
        Rectangle_Area,
        Rectangle_Draw
    };
    Shape_Ctor(&rectPtr->super, x, y);  // 调用基类的构造函数
    rectPtr->super.vptr = &vtbl;        // 重载 vptr
    rectPtr->width      = width;
    rectPtr->height     = height;
    return;
}

// Rectangle 虚函数的实现
static unsigned int Rectangle_Area(const Shape * const shapePtr)
{
    const Rectangle * const rectPtr = (const Rectangle *)shapePtr;
    return (unsigned int)(rectPtr->width * rectPtr->height);
}

static void Rectangle_Draw(const Shape * const shapePtr)
{
    const Rectangle * const rectPtr = (const Rectangle *)shapePtr;
    printf("Rectangle_Draw(x=%d,y=%d,width=%d,height=%d)\n",
           Shape_GetX(shapePtr), Shape_GetY(shapePtr), rectPtr->width, rectPtr->height);
    return;
}