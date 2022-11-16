#ifndef SHAPE_H
#define SHAPE_H

typedef struct {
    int x;
    int y;
} Shape;

void Shape_Ctor(Shape * const shapePtr, int x, int y);
void Shape_Move(Shape * const shapePtr, int offsetX, int offsetY);
int Shape_GetX(const Shape *const shapePtr);
int Shape_GetY(const Shape *const shapePtr);

#endif