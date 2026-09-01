#include "football/pitch.h"
#include "football/player.h"

#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <stdlib.h>

Vector2 rotate_point(Vector2 point, Vector2 center, float angle) {
    Vector2 local = Vector2Subtract(point, center);

    return Vector2Add(
        center,
        (Vector2){
            local.x * cosf(angle) - local.y * sinf(angle),
            local.x * sinf(angle) + local.y * cosf(angle)
        }
    );
}


Player* call_players(const Pitch* pitch, size_t team1, size_t team2) {
    if (team1 == 0 || team2 == 0) {

        return NULL;
    }

    Player* players = malloc(sizeof(Player) * (team1 + team2));

    Rectangle field = pitch->bound;
    Vector2   strip = pitch->strip;

    Vector2 body = {
        strip.x * 0.3,
        strip.x * 0.3
    };

    if (!players) {

        return NULL;
    }

    players->total = team1 + team2;

    for (int i=0; i < players->total; i++) {
        players[i].sprinting    = false;

        players[i].velocity     = (Vector2) { 0, 0 };
        players[i].speed        = 70;
        players[i].direction    = (Vector2) { 0, 0 };

        players[i].max_stamina  = GetRandomValue(100, 600);
        players[i].stamina      = players->max_stamina;
        players[i].body = (Rectangle) {
            .width  = body.x,
            .height = body.y,
        };
        players[i].rotation = 0.0f;

        if (i < (int)team1) {
            players[i].number    = i + 1;

            players[i].color    = RED;
            players[i].outline  = BLACK;

            players[i].body.x = field.x + (field.width * 0.5f - strip.x * 1.25f),
            players[i].body.y = field.y + (field.height / 2.0f + (i - (team1 - 1) / 2.0f) * strip.x);
        } else {
            int j = i - team1;

            players[i].number    = j + 1;

            players[i].color    = BLUE;
            players[i].outline  = BLACK;

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
    float outLineThick = 5.0f;

    for (int i=0; i < players->total; i++) {
        Rectangle body    = {
            .width  = players[i].body.width  - outLineThick,
            .height = players[i].body.height - outLineThick,
            .x      = players[i].body.x,
            .y      = players[i].body.y
        };

        Rectangle outline = {
            .width  = body.width  + outLineThick,
            .height = body.height + outLineThick,
            .x      = body.x,
            .y      = body.y
        };

        Vector2 origin = {
            body.width  * 0.5f,
            body.height * 0.5f
        };

        DrawRectanglePro(
            outline,
            (Vector2){
                outline.width  * 0.5f,
                outline.height * 0.5f
            },
            players[i].rotation,
            players[i].outline
        );

        DrawRectanglePro(
            body,
            origin,
            players[i].rotation,
            players[i].color
        );

        DrawTextEx(
            GetFontDefault(),
            TextFormat("%d",
            players[i].number),
            (Vector2){
                body.x - MeasureText(TextFormat("%d", players[i].number), 5) * 0.5f,
                body.y - 2.5f
            },
            5,
            0,
            WHITE
        );

        if (i == 0) {
            Vector2 center = {
                body.x,
                body.y
            };

            float distance = Vector2Distance(center, *players->indicated_obj);

            if (distance > body.width * 5.0f) {
                float dx = players->indicated_obj->x - body.x;
                float dy = players->indicated_obj->y - body.y;

                float angle  = atan2f(dy, dx);

                Vector2 tip = {
                    center.x + (outline.width + body.width) * 0.9f,
                    center.y
                };

                Vector2 left = {
                    body.x + (outline.width + body.width ) * 0.7f,
                    body.y - body.height * 0.3f
                };

                Vector2 right = {
                    body.x + (outline.width + body.width ) * 0.7f,
                    body.y + body.height * 0.3f
                };

                tip     = rotate_point(tip,     center, angle);
                left    = rotate_point(left,    center, angle);
                right   = rotate_point(right,   center, angle);

                DrawTriangle(
                    tip,
                    left,
                    right,
                    YELLOW
                );
            }
        }
    }
}

void handle_player(Player* player, float camera_rotation, float dt) {
    Vector2 movement = Vector2Zero();

    if (player->stamina > player->max_stamina * 0.01f && IsKeyDown(KEY_LEFT_SHIFT)) {
        player->speed = 100.0f;
        player->sprinting = true;

    } else {
        player->speed = 50.0f;

        player->sprinting = false;
    }

    if (IsKeyDown(KEY_A)) movement.x = -1;
    if (IsKeyDown(KEY_D)) movement.x =  1;
    if (IsKeyDown(KEY_W)) movement.y = -1;
    if (IsKeyDown(KEY_S)) movement.y =  1;

    if (!player->kicked && IsKeyDown(KEY_SPACE)) {
        player->body.x += player->direction.x * 300 * dt;
        player->body.y += player->direction.y * 300 * dt;
    }

    if (movement.x != 0 || movement.y != 0) {

        if (player->sprinting)
            player->stamina -= 10 * dt;

        movement = Vector2Normalize(movement);
        movement = Vector2Rotate(movement, -camera_rotation * DEG2RAD);

        player->direction = movement;
    }

    player->velocity.x = movement.x * player->speed;
    player->velocity.y = movement.y * player->speed;
}

void update_players(Player* players, Camera2D* camera, float dt) {
    float follow_speed = 8.0f;

    camera->target.x = Lerp(camera->target.x, players->body.x, follow_speed * dt);
    camera->target.y = Lerp(camera->target.y, players->body.y, follow_speed * dt);

    // handle_ai_player();
    handle_player(&players[0], camera->rotation, dt);

    for (int i=0; i < players->total; i++) {
        // Regenerating Stamina
        float stamina_regen = 5.0f * dt;

        players[i].stamina += stamina_regen;

        if (players[i].sprinting) {
            stamina_regen *= 0.2f;
        }

        players[i].stamina = Clamp(
            players[i].stamina,
            0.0f,
            players[i].max_stamina
        );

        players[i].body.x += players[i].velocity.x * dt;
        players[i].body.y += players[i].velocity.y * dt;
    }

    for (int i=0; i < players->total; i++) {
        for (int j=i + 1; j < players->total; j++) {
            if (CheckCollisionRecs(players[i].body, players[j].body)) {
                Rectangle overlap = GetCollisionRec(players[i].body, players[j].body);
                if (overlap.width < overlap.height) {
                    float push = overlap.width * 0.5f;

                    if (players[i].body.x > players[j].body.x) {
                        players[i].body.x += push;
                        players[j].body.x -= push;
                    } else {
                        players[i].body.x -= push;
                        players[j].body.x += push;
                    }
                } else {
                    float push = overlap.height * 0.5f;

                    if (players[i].body.y > players[j].body.y) {
                        players[i].body.y += push;
                        players[j].body.y -= push;
                    } else {
                        players[i].body.y -= push;
                        players[j].body.y += push;
                    }
                }
            }
        }
    }
}
