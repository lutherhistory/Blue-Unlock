#ifndef  REFEREER_H
#define  REFEREER_H

#include <raylib.h>

typedef struct {

    Vector2 center;

    Vector2 pointA;
    Vector2 pointB;
    Vector2 pointC;

    float   offset;

    Color   color;

} Referee;

Referee create_referee(float pos_x, float pos_y, float offset);

void updaet_referee(Referee* referee, float dt);

void draw_referee(Referee* referee);

#endif
