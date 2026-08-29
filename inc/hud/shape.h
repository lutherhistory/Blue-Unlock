#ifndef SHAPE_H
#define SHAPE_H

#include <stddef.h>
#include <raylib.h>

typedef struct {

    int __id;
    size_t __capc;
    size_t __size;

    Vector2 size;
    Vector2 pos;
    Color   color;

    bool set_outline;
    bool set_inner;
    bool set_dynamic;

    struct Simple_Shape* next;

} Simple_Shape;


Simple_Shape* push_back(Simple_Shape value);

void clean(Simple_Shape* shapes);

#endif
