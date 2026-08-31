#include "football/pitch.h"

#include "colour.h"
#include <raylib.h>

// --- src/football-pitch.c
void update_pitch(Pitch* pitch);

void draw_pitch(Pitch* pitch) {
    Rectangle   area        = pitch->area;
    Rectangle   bound       = pitch->bound;
    Vector2     strip       = pitch->strip;
    Color       paint       = RAYWHITE;

    float       thick       = 5.0f;

    Vector2     center      = {
        bound.x + bound.width  * 0.5f,
        bound.y + bound.height * 0.5f
    };

    Vector2     pentalty    = {
        strip.x * 3.0f,
        bound.height * 0.6
    };

    Vector2     goalArea    = {
        strip.x,
        strip.x * 2.5
    };

    Vector2     goalStand        = {
        goalArea.x * 0.4,
        goalArea.y * 0.6
    };

    float       depth       = goalStand.x * 0.35f;

    Rectangle front = {
        .width  = goalStand.x,
        .height = goalStand.y
    };

    front.x     = bound.x - front.width - depth;
    front.y     = bound.y + (bound.height - front.height) * 0.5f;

    Rectangle back = {
        .width  = front.width,
        .height = front.height + depth
    };

    back.x      = bound.x - back.width;
    back.y      = bound.y + (bound.height - back.height) * 0.5f;

    // Drawing Grasss
    for (int i=0; i < area.width / strip.x; i++){
        DrawRectangleV(
            (Vector2){
                area.x + strip.x * i,
                area.y
            },
            (Vector2){
                strip.x,
                strip.y
            },
            (i % 2) ? COLOUR_GRASS2 : COLOUR_GRASS1
        );
    }

    // Drawing bound of Play
    DrawRectangleLinesEx(
        bound,
        thick,
        paint
    );

    // Drawing Corner Arcs
    DrawRing(
        (Vector2){
            bound.x,
            bound.y
        },
        strip.x * 0.5 + thick,
        strip.x * 0.5,
        0,
        90,
        0,
        paint
    );

    DrawRing(
        (Vector2){
            bound.x + bound.width,
            bound.y
        },
        strip.x * 0.5 + thick,
        strip.x * 0.5,
        90,
        180,
        0,
        paint
    );

    DrawRing(
        (Vector2){
            bound.x,
            bound.y + bound.height
        },
        strip.x * 0.5 + thick,
        strip.x * 0.5,
        -90,
        0,
        0,
        paint
    );

    DrawRing(
        (Vector2){
            bound.x + bound.width,
            bound.y + bound.height
        },
        strip.x * 0.5 + thick,
        strip.x * 0.5,
        -180,
        -90,
        0,
        paint
    );

    // Drawing Center Line
    DrawLineEx(
        (Vector2){
            center.x,
            center.y - bound.height * 0.5f
        },
        (Vector2){
            center.x,
            center.y + bound.height * 0.5f
        },
        thick,
        paint
    );

    // Center Circle
    DrawRing(
        center,
        strip.x + thick,
        strip.x,
        0,
        360,
        0,
        paint
    );

    // Drawing Center Spot
    DrawCircleV(
        center,
        thick * 1.5f,
        paint
    );

    // Drawing Pentalty Areas
    DrawRectangleLinesEx(
        (Rectangle){
            .width  = pentalty.x,
            .height = pentalty.y,
            .x      = bound.x + 0,
            .y      = bound.y + (bound.height - pentalty.y) / 2.0f
        },
        thick,
        paint
    );

    DrawRectangleLinesEx(
        (Rectangle){
            .width  = pentalty.x,
            .height = pentalty.y,
            .x      = bound.x + (bound.width - pentalty.x),
            .y      = bound.y + (bound.height - pentalty.y) / 2.0f
        },
        thick,
        paint
    );

    // Drawing Penalty Marks
    DrawCircleV(
        (Vector2){
            bound.x + (pentalty.x - strip.x),
            bound.y + bound.height / 2.0f
        },
        thick,
        paint
    );

    DrawCircleV(
        (Vector2){
            bound.x + bound.width - (pentalty.x - strip.x),
            bound.y + bound.height / 2.0f
        },
        thick,
        paint
    );

    // Drawing Penalty Arcs
    DrawRing(
        (Vector2){
            bound.x + pentalty.x,
            bound.y + bound.height / 2.0f
        },
        strip.x * 0.7 + thick,
        strip.x * 0.7,
        90.0f,
        -90.0f,
        0,
        paint
    );

    DrawRing(
        (Vector2){
            bound.x + bound.width - pentalty.x,
            bound.y + bound.height / 2.0f
        },
        strip.x * 0.7 + thick,
        strip.x * 0.7,
        90.0f,
        270.0f,
        0,
        paint
    );

    // Drawing Goal Areas
    DrawRectangleLinesEx(
        (Rectangle){
            .width  = goalArea.x,
            .height = goalArea.y,
            .x      = bound.x + 0,
            .y      = bound.y + (bound.height - goalArea.y) / 2.0f
        },
        thick,
        paint
    );

    DrawRectangleLinesEx(
        (Rectangle){
            .width  = goalArea.x,
            .height = goalArea.y,
            .x      = bound.x + (bound.width - goalArea.x),
            .y      = bound.y + (bound.height - goalArea.y) / 2.0f
        },
        thick,
        paint
    );

    // Drawing Goals Stands
    paint = (Color) {0xCC, 0xCC, 0xCC, 0xFF};

    DrawLineEx(
        (Vector2){
            front.x + front.width,
            front.y
        },
        (Vector2){
            back.x + back.width,
            back.y
        },
        thick * 0.2f,
        paint
    );
    DrawLineEx(
        (Vector2){
            front.x + front.width,
            front.y + front.height
        },
        (Vector2){
            back.x  + back.width,
            back.y  + back.height
        },
        thick * 0.2f,
        paint
    );
    DrawLineEx(
        (Vector2){
            front.x,
            front.y
        },
        (Vector2){
            back.x,
            back.y
        },
        thick * 0.2f,
        paint
    );
    DrawLineEx(
        (Vector2){
            front.x,
            front.y + front.height
        },
        (Vector2){
            back.x,
            back.y + back.height
        },
        thick * 0.2f,
        paint
    );

    DrawRectangleLinesEx(back, thick * 0.2f, paint);
    DrawRectangleLinesEx(front, thick * 0.2f, paint);

    DrawLineEx(
        (Vector2){
            bound.x + bound.width + depth,
            front.y
        },
        (Vector2){
            bound.x + bound.width,
            back.y
        },
        thick * 0.2f,
        paint
    );
    DrawLineEx(
        (Vector2){
            bound.x + bound.width + depth,
            front.y + front.height
        },
        (Vector2){
            bound.x + bound.width,
            back.y + back.height
        },
        thick * 0.2f,
        paint
    );
    DrawLineEx(
        (Vector2){
            bound.x + bound.width + depth + front.width,
            front.y
        },
        (Vector2){
            bound.x + bound.width + back.width,
            back.y
        },
        thick * 0.2f,
        paint
    );
    DrawLineEx(
        (Vector2){
            bound.x + bound.width + front.width + depth,
            front.y + front.height
        },
        (Vector2){
            bound.x + bound.width + back.width,
            back.y + back.height
        },
        thick * 0.2f,
        paint
    );

    DrawRectangleLinesEx(
        (Rectangle){
            bound.x + bound.width + depth,
            front.y,
            front.width,
            front.height
        },
        thick * 0.2f,
        paint
    );
    DrawRectangleLinesEx(
        (Rectangle){
            bound.x + bound.width,
            back.y,
            back.width,
            back.height
        },
        thick * 0.2f,
        paint
    );

    // Drawing Goal Nets
    for (int i=0; i < 12; i++) {
        DrawLineEx(
            (Vector2){
                bound.x + bound.width + depth,
                front.y + (front.height / 12.0f) * i
            },
            (Vector2){
                bound.x + bound.width + depth + front.width,
                front.y + (front.height / 12.0f) * i
            },
            thick * 0.05f,
            paint
        );

        DrawLineEx(
            (Vector2){
                bound.x - depth,
                front.y + (front.height / 12.0f) * i
            },
            (Vector2){
                bound.x - front.width - depth,
                front.y + (front.height / 12.0f) * i
            },
            thick * 0.05f,
            paint
        );
    }

    for (int i=0; i < 4; i++) {
        DrawLineEx(
            (Vector2){
                bound.x - depth - (front.width / 4.0f) * i,
                front.y
            },
            (Vector2){
                bound.x - depth - (front.width / 4.0f) * i,
                front.y + front.height
            },
            thick * 0.05f,
            paint
        );

        DrawLineEx(
            (Vector2){
                bound.x + bound.width + depth + (front.width / 4.0f) * i,
                front.y
            },
            (Vector2){
                bound.x + bound.width + depth + (front.width / 4.0f) * i,
                front.y + front.height
            },
            thick * 0.05f,
            paint
        );
    }
}
