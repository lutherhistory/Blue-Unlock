#include <raylib.h>
#include <raymath.h>

#include "physics/collisions.h"

typedef struct {

    Rectangle   rec;
    Color       color;

    Collider    collider;

    Vector2     position;
    Vector2     velocity;

} Entity;


void draw_entity(Entity* entities) {
    entities->rec.x = entities->position.x;
    entities->rec.y = entities->position.y;

    DrawRectangleRec(entities->rec, entities->color);
}

void handle_movement(Entity* player, float speed) {
    Vector2 movement = Vector2Zero();

    if (IsKeyDown(KEY_A)) movement.x = -1;
    if (IsKeyDown(KEY_D)) movement.x =  1;
    if (IsKeyDown(KEY_W)) movement.y = -1;
    if (IsKeyDown(KEY_S)) movement.y =  1;

    player->velocity.x = movement.x * speed;
    player->velocity.y = movement.y * speed;
}

void update_entities_physics(Entity* entity, float dt) {
    entity->position.x += entity->velocity.x * dt;
    entity->position.y += entity->velocity.y * dt;
}

int main() {
    InitWindow(800, 600, "Collisioin System");
    SetTargetFPS(60);

    Entity object1 = {
        .rec = {
            .width  = 50,
            .height = 50,
        },
        .position   = {
            200,
            200
        },
        .color      = RED,
        .velocity   = Vector2Zero(),
    };
    Entity object2 = {
        .rec = {
            .width  = 50,
            .height = 50,
        },
        .position   = {
            400,
            200
        },
        .color      = BLUE,
        .velocity   = Vector2Zero(),
    };


    object1.collider = (Collider) {
        .rect = &object1.rec,
    };
    object2.collider = (Collider) {
        .rect = &object2.rec
    };


    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        handle_movement(&object1, 100);

        update_collision(&object1.collider, &object2.collider);

        if (object1.collider.enable && object1.collider.response)
            object1.collider.response();

        update_entities_physics(&object1, dt);
        update_entities_physics(&object2, dt);

        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText(
                "AABB Collision",
                (GetScreenWidth() - MeasureText("AABB Collision", 40)) / 2,
                10,
                40,
                BLACK
            );

            draw_entity(&object1);
            draw_entity(&object2);

        EndDrawing();
    }

    CloseWindow();
}
