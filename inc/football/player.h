#ifndef PLAYER_H
#define PLAYER_H

#include "football/pitch.h"

#include <raylib.h>
#include <stddef.h>

typedef struct {

    Rectangle   body;

    Color       color;
    Color       outline;

    Vector2*    indicated_obj;

    Vector2     velocity;
    Vector2     direction;
    float       speed;

    int         total;
    float       rotation;
    float       stamina;

    float       max_stamina;

    bool        sprinting;
    bool        kicked;

} Player;


Player* call_players(const Pitch* pitch, size_t team1, size_t team2);

void kill_players(Player* players);

void draw_players(const Player* players);

void update_players(Player* players, Camera2D* camera, float dt);


#endif
