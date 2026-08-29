#ifndef PITCH_H
#define PITCH_H

#include <raylib.h>

// --- inc/football/pitch.h ---
typedef struct {

    Rectangle   area;
    Vector2     strip;
    Rectangle   bound;

} Pitch;


void update_pitch(Pitch* pitch);

void draw_pitch(Pitch* pitch);

#endif
