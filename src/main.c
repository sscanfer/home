#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include "rectangle.h"
#include "circle.h"

int main(int argc, char **argv)
{
    Rectangle r1, r2;
    Circle    c1, c2;

    const Shape *shapes[] = {
        &c1.super,
        &r2.super,
        &c2.super,
        &r1.super
    };

    const Shape *s = NULL;

    // 实例化矩形对象
    Rectangle_Ctor(&r1, 0, 2, 10, 15);
    Rectangle_Ctor(&r2, -1, 3, 5, 8);

    // 实例化圆形对象
    Circle_Ctor(&c1, 1, -2, 12);
    Circle_Ctor(&c2, 1, -3, 6);

    s = Shape_GetLargest(shapes, sizeof(shapes) / sizeof(shapes[0]));
    printf("largest shape s(x=%d,y=%d)\n", Shape_GetX(s), Shape_GetY(s));

    Shape_DrawAll(shapes, sizeof(shapes) / sizeof(shapes[0]));

    return 0;
}