#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

// 矩形的属性
typedef struct {
    Shape super;    // 继承 Shape

    // 自己的属性
    unsigned int width;
    unsigned int height;
} Rectangle;

// 构造函数
void Rectangle_Ctor(Rectangle * const   rectPtr,
                    int                 x,          int             y,
                    unsigned int        width,      unsigned int    height);

#endif /* RECTANGLE_H */