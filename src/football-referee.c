#include "football/pitch.h"
#include "football/referee.h"

#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>

float offset = 10.0f;

void update_triangle(Vector2* a, Vector2* b, Vector2 *c, Vector2 center) {
    *a = (Vector2) {
        .x = center.x,
        .y = center.y - offset
    };

    *b = (Vector2) {
        .x = center.x - offset,
        .y = center.y + offset
    };

    *c = (Vector2) {
        .x = center.x + offset,
        .y = center.y + offset
    };

}

Referee create_referee(float pos_x, float pos_y) {
    Vector2 a = {
        .x = pos_x,
        .y = pos_y - offset
    };

    Vector2 b = {
        .x = pos_x - offset,
        .y = pos_y + offset
    };

    Vector2 c = {
        .x = pos_x + offset,
        .y = pos_y + offset
    };

    Color color = GOLD;

    return (Referee){
        .center = (Vector2){
            pos_x,
            pos_y
        },
        .velocity = Vector2Zero(),
        .pointA = a,
        .pointB = b,
        .pointC = c,
        .color  = color
    };
}

void updaet_referee(Referee* referee, const Pitch* pitch, Sound* whistle, float dt) {
    float distance = Vector2Distance(referee->center, referee->chase_target);

    if (distance > offset * 2.0f) {
        Vector2 direction = Vector2Subtract(referee->chase_target, referee->center);
        direction = Vector2Normalize(direction);

        referee->velocity.x = direction.x;
        referee->velocity.y = direction.y;
    } else {
        PlaySound(*whistle);

        float genRandomX = GetRandomValue(pitch->bound.x, pitch->bound.x + pitch->bound.width);
        float genRandomY = GetRandomValue(pitch->bound.y, pitch->bound.x + pitch->bound.height);

        referee->chase_target.x = Clamp(genRandomX, pitch->bound.x, pitch->bound.x + pitch->bound.width);
        referee->chase_target.y = Clamp(genRandomY, pitch->bound.y, pitch->bound.y + pitch->bound.height);
    }

    referee->center.x += referee->velocity.x * 100 * dt;
    referee->center.y += referee->velocity.y * 100 * dt;

    update_triangle(&referee->pointA, &referee->pointB, &referee->pointC, referee->center);
}

void draw_referee(Referee* referee) {
    float thick = offset * 0.3;

    // Vector2 a = {
    //     referee->pointA.x,
    //     referee->pointA.y - thick * 2.0f
    // };
    // Vector2 b = {
    //     referee->pointB.x - thick,
    //     referee->pointB.y + thick
    // };
    // Vector2 c = {
    //     referee->pointC.x + thick,
    //     referee->pointC.y + thick
    // };


    // DrawTriangle(
    //     a,
    //     b,
    //     c,
    //     BLACK
    // );

    DrawTriangle(
        referee->pointA,
        referee->pointB,
        referee->pointC,
        referee->color
    );

    DrawLineEx(referee->pointA, referee->pointB, thick, BLACK);
    DrawLineEx(referee->pointB, referee->pointC, thick, BLACK);
    DrawLineEx(referee->pointA, referee->pointC, thick, BLACK);

    DrawCircleV(referee->pointA, thick * 0.5, BLACK);
    DrawCircleV(referee->pointB, thick * 0.5, BLACK);
    DrawCircleV(referee->pointC, thick * 0.5, BLACK);
}
