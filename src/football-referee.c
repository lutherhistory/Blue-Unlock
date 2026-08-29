#include "football/referee.h"

#include <raylib.h>

Referee create_referee(float pos_x, float pos_y, float offset) {
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
        .pointA = a,
        .pointB = b,
        .pointC = c,
        .color  = color
    };
}

void updaet_referee(Referee* referee, float dt) {

}

void draw_referee(Referee* referee) {



    return;

    DrawTriangleLines(
        referee->pointA,
        referee->pointB,
        referee->pointC,
        referee->color
    );

    DrawTriangle(
        referee->pointA,
        referee->pointB,
        referee->pointC,
        referee->color
    );

    DrawTriangleStrip(
        &referee->pointA,
        3,
        PURPLE
    );

    DrawTriangleFan(
        &referee->pointA,
        3,
        MAROON
    );
}
