#include <assert.h>
#include <stdio.h>
#include "shape.h"

// Shape 的虚函数
static unsigned int Shape_Area_(const Shape * const shapePtr);
static void Shape_Draw_(const Shape * const shapePtr);

// 构造函数
void Shape_Ctor(Shape * const shapePtr, int x, int y)
{
    // Shape 类的虚表
    const static struct ShapeVtbl vtbl = {
        Shape_Area_,
        Shape_Draw_
    };
    shapePtr->vptr = &vtbl;
    shapePtr->x    = x;
    shapePtr->y    = y;
    return;
}

void Shape_Move(Shape * const shapePtr, int dx, int dy)
{
    shapePtr->x += dx;
    shapePtr->y += dy;
    return;
}

// 获取属性值函数
int Shape_GetX(const Shape * const shapePtr)
{
    return shapePtr->x;
}

int Shape_GetY(const Shape * const shapePtr)
{
    return shapePtr->y;
}

// Shape 类的虚函数实现
static unsigned int Shape_Area_(const Shape * const shapePtr)
{
    assert(0);  // 类似纯虚函数
    return 0U;  // 避免警告
}

static void Shape_Draw_(const Shape * const shapePtr)
{
    assert(0);  // 纯虚函数不能被调用
}

const Shape* Shape_GetLargest(const Shape *shapes[], unsigned int shapeNum)
{
    const Shape *s = NULL;
    unsigned int max = 0;

    for (unsigned int i = 0; i < shapeNum; i++) {
        unsigned int area = Shape_Area(shapes[i]);  // 虚函数调用
        if (area > max) {
            max = area;
            s = shapes[i];
        }
    }
    return s;
}

void Shape_DrawAll(const Shape *shapes[], unsigned int shapeNum)
{
    for (unsigned int i = 0; i < shapeNum; i++) {
        Shape_Draw(shapes[i]);
    }
    return;
}