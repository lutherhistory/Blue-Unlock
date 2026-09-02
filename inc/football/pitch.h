#ifndef PITCH_H
#define PITCH_H

#include "physics/collisions.h"

#include <raylib.h>

// --- inc/football/pitch.h ---
typedef struct Pitch {

    Rectangle   area;
    Vector2     strip;
    Rectangle   bound;

    Collider    collider;

} Pitch;


void update_pitch(Pitch* pitch);

void draw_pitch(Pitch* pitch);

#endif
