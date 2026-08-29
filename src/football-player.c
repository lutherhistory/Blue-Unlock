#include "football/pitch.h"
#include "football/player.h"
#include "colour.h"

#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>

Player* call_players(const Pitch* pitch, size_t team1, size_t team2) {
    if (team1 == 0 || team2 == 0) {

        return NULL;
    }

    Player* players = malloc(sizeof(Player) * (team1 + team2));

    Rectangle field = pitch->bound;
    Vector2   strip = pitch->strip;

    Color     team_colours[] = {
        RED,
        BLUE,
        ORANGE,
        GOLD,
        GREEN,
        MAROON,
        VIOLET
    };

    Vector2 body = {
        strip.x * 0.2,
        strip.x * 0.2
    };

    if (!players) {

        return NULL;
    }

    players->total = team1 + team2;

    for (int i=0; i < players->total; i++) {
        players[i].sprinting = false;

        players[i].velocity = (Vector2){ 0, 0 };
        players[i].speed    = 70;
        players[i].max_stamina  = GetRandomValue(100, 500);
        players[i].stamina      = players->max_stamina;
        players[i].body = (Rectangle) {
            .width  = body.x,
            .height = body.y,
        };
        players[i].rotation = 0.0f;

        if (i < team1) {
            players[i].color = RED;

            players[i].body.x = field.x + (field.width * 0.5f - strip.x * 1.25f),
            players[i].body.y = field.y + (field.height / 2.0f + (i - (team1 - 1) / 2.0f) * strip.x);
        } else {
            int j = i - team1;

            players[i].color = TEAM_BLUE_UNLOCK;

            players[i].body.x = field.x + (field.width * 0.5f + strip.x * 1.25f),
            players[i].body.y = field.y + (field.height / 2.0f + (j - (team2 - 1) / 2.0f) * strip.x);
        }
    }

    return players;
}

void kill_players(Player* players) {
    if (players) {
        size_t size = players->total;

        free(players);
        players = NULL;

        TraceLog(LOG_INFO, "Players' heap[%zu bytes] usages had free up successfully.", size);
    } else {

        TraceLog(LOG_ERROR, "Players' heap usages had something well wrong.");
    }
}

void draw_players(const Player* players) {
    for (int i=0; i < players->total; i++) {
        Vector2 origin = {
            players[i].body.width  * 0.5f,
            players[i].body.height * 0.5f
        };

        Rectangle outline = {
            .width  = players[i].body.width  + 5,
            .height = players[i].body.height + 5,
            .x      = players[i].body.x,
            .y      = players[i].body.y
        };

        DrawRectanglePro(
            outline,
            (Vector2){
                outline.width  * 0.5f,
                outline.height * 0.5f
            },
            players[i].rotation,
            BLACK
        );

        DrawRectanglePro(
            players[i].body,
            origin,
            players[i].rotation,
            players[i].color
        );
    }
}

void handle_player(Player* player, float camera_rotation, float dt) {
    Vector2 direction = { 0, 0 };


    if (player->stamina > 1.0f && IsKeyDown(KEY_LEFT_SHIFT)) {
        player->speed = 100.0f;
        player->sprinting = true;

    } else {
        player->speed = 50.0f;

        player->sprinting = false;
    }

    if (IsKeyDown(KEY_A)) direction.x = -1;
    if (IsKeyDown(KEY_D)) direction.x =  1;
    if (IsKeyDown(KEY_W)) direction.y = -1;
    if (IsKeyDown(KEY_S)) direction.y =  1;

    if (!player->kicked && IsKeyPressed(KEY_SPACE)) {
        // TraceLog(LOG, const char *text, ...)
    }

    if (direction.x != 0 || direction.y != 0) {

        if (player->sprinting)
            player->stamina -= 10 * dt;

        direction = Vector2Normalize(direction);
    }

    direction = Vector2Rotate(direction, -camera_rotation * DEG2RAD);

    player->velocity.x = direction.x * player->speed;
    player->velocity.y = direction.y * player->speed;
}

void update_players(Player* players, Camera2D* camera, float dt) {

    float follow_speed = 8.0f;

    camera->target.x = Lerp(camera->target.x, players->body.x, follow_speed * dt);
    camera->target.y = Lerp(camera->target.y, players->body.y, follow_speed * dt);

    // handle_ai_player();
    handle_player(&players[0], camera->rotation, dt);

    for (int i=0; i < players->total; i++) {
        // Regenerating Stamina
        if (!players[i].sprinting && players[i].stamina < players[i].max_stamina) {
            players[i].stamina += 5.0f * dt;
        }

        players[i].body.x += players[i].velocity.x * dt;
        players[i].body.y += players[i].velocity.y * dt;
    }
}
