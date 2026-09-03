#ifndef  REFEREER_H
#define  REFEREER_H

#include "football/pitch.h"

#include <raylib.h>

typedef struct {

    Vector2 center;

    Vector2 pointA;
    Vector2 pointB;
    Vector2 pointC;

    Vector2 velocity;
    Vector2 chase_target;

    Color   color;

} Referee;

Referee create_referee(float pos_x, float pos_y);

void updaet_referee(Referee* referee, const Pitch* pitch, Sound* whistle, float dt);

void draw_referee(Referee* referee);

#endif
