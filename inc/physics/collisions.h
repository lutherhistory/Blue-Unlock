#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <raylib.h>

// Prototype
typedef struct Collider Collider;

// Declaration
typedef void (*CollisionResponse)();

typedef struct Collider {

    // Collider's Data
    Rectangle* rect;

    // Collision Resolution
    bool enable;

    // Collision Response
    CollisionResponse response;

} Collider;


void update_collision(Collider* collder1, Collider* collider2);


#endif
