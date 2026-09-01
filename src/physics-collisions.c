#include "physics/collisions.h"
#include <raylib.h>

void update_collision_system(CollisionSystem* collisions) {
    Vector2 point1 = {
        collisions->collider1st->rect.x,
        collisions->collider1st->rect.y
    };

    if (!CheckCollisionPointRec(point1, collisions->collider2nd->rect)) {
        Rectangle overlap = GetCollisionRec(collisions->collider1st->rect, collisions->collider2nd->rect);

        collisions->collider1st->overlap = (Rectangle) {
            .x = overlap.x,
            .y = overlap.y + (collisions->collider1st->rect.height - overlap.height),
            .width  = overlap.width,
            .height = collisions->collider1st->rect.height - overlap.height
        };
    } else {
        collisions->collider1st->overlap = (Rectangle) {};
    }

    Vector2 point2 = {
        collisions->collider1st->rect.x + collisions->collider1st->rect.width,
        collisions->collider1st->rect.y + collisions->collider1st->rect.height
    };

    if (!CheckCollisionPointRec(point2, collisions->collider2nd->rect)) {

    }
}
