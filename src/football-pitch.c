#include "football/pitch.h"

#include "colour.h"
#include <raylib.h>

// --- src/football-pitch.c
void update_pitch(Pitch* pitch) {

}

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

    Vector2     goal        = {
        goalArea.x * 0.6,
        goalArea.y * 0.6
    };

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

    // Drawing Goals
    Vector2 goalLeft = {
        .x      = bound.x - goal.x + thick,
        .y      = bound.y + (bound.height - goal.y) / 2.0f,
    };

    DrawRectangleLinesEx(
        (Rectangle){
            .width  = goal.x,
            .height = goal.y,
            .x      = goalLeft.x,
            .y      = goalLeft.y
        },
        thick * 0.2,
        paint
    );

    for (int i=0; i < 10; i++) {
        DrawLineV(
            (Vector2){
                goalLeft.x,
                goalLeft.y + i * (goal.y / 10)
            },
            (Vector2){
                goalLeft.x + goal.x,
                goalLeft.y + i * (goal.y / 10)
            },
            paint
        );
    }

    for (int i=0; i < 10; i++) {
        DrawLineV(
            (Vector2){
                goalLeft.x + i * (goal.x / 10),
                goalLeft.y
            },
            (Vector2){
                goalLeft.x + i * (goal.x / 10),
                goalLeft.y + goal.y
            },
            paint
        );
    }

    Vector2 goalRight = {
        .x      = bound.x + (bound.width - thick),
        .y      = bound.y + (bound.height - goal.y) / 2.0f,
    };

    DrawRectangleLinesEx(
        (Rectangle){
            .width  = goal.x,
            .height = goal.y,
            .x      = goalRight.x,
            .y      = goalRight.y
        },
        thick * 0.2,
        paint
    );

    for (int i=0; i < 10; i++) {
        DrawLineV(
            (Vector2){
                goalRight.x + i * (goal.x / 10),
                goalRight.y
            },
            (Vector2){
                goalRight.x + i * (goal.x / 10),
                goalRight.y + goal.y
            },
            paint
        );
    }

    for (int i=0; i < 10; i++) {
        DrawLineV(
            (Vector2){
                goalRight.x,
                goalRight.y + i * (goal.y / 10)
            },
            (Vector2){
                goalRight.x + goal.x,
                goalRight.y + i * (goal.y / 10)
            },
            paint
        );
    }
}
