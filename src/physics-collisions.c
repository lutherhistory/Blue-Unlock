#include "physics/collisions.h"

#include <raylib.h>


void update_collision(Collider* collider1, Collider* collider2) {
    if (!collider1 || !collider2) {

        return;
    }



    if (CheckCollisionRecs(*collider1->rect, *collider2->rect)) {
        if (collider1->response);
        // collider1->response();
    }
}
