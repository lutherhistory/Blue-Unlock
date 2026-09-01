#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <raylib.h>

typedef struct {

    Rectangle rect;
    Rectangle overlap;

    bool enable;
    bool inbox;

} Collider;

typedef struct {

    Collider* collider1st;
    Collider* collider2nd;

} CollisionSystem;


void update_collision_system(CollisionSystem* collisions);

#endif
