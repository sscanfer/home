#ifndef SHAPE_H
#define SHAPE_H

struct ShapeVtbl;

// Shape 的属性
typedef struct {
    const struct ShapeVtbl     *vptr;   // 虚指针
    int                         x;
    int                         y;
} Shape;

// 虚表
struct ShapeVtbl {
    unsigned int (*area)(const Shape * const shapePtr);
    void (*draw)(const Shape * const shapePtr);
};

// Shape 的操作函数，接口函数
void Shape_Ctor(Shape * const shapePtr, int x, int y);
void Shape_Move(Shape * const shapePtr, int dx, int dy);
int Shape_GetX(const Shape *const shapePtr);
int Shape_GetY(const Shape *const shapePtr);

static inline unsigned int Shape_Area(const Shape * const shapePtr)
{
    return shapePtr->vptr->area(shapePtr);
}

static inline void Shape_Draw(const Shape * const shapePtr)
{
    shapePtr->vptr->draw(shapePtr);
}

const Shape* Shape_GetLargest(const Shape *shapes[], unsigned int shapeNum);
void Shape_DrawAll(const Shape *shapes[], unsigned int shapeNum);

#endif /* SHAPE_H */