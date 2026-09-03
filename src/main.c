// Sensible Soccer Inspire
#include <raylib.h>
#include <raymath.h>

#include "colour.h"
#include "football/pitch.h"
#include "football/player.h"

#include "football/referee.h"
#include "need.h"
#include "physics/collisions.h"

typedef struct {

    bool muted;
    bool rotated;
    bool zommed;
    bool attribute;

} Settings;

#if DEBUG
    Settings settings = {
        .rotated    = false,
        .muted      = true,
        .zommed     = true,
        .attribute  = false
    };
#else
    Settings settings = {
        .rotated    = true,
        .muted      = false,
        .zommed     = true,
        .attribute  = true
    };
#endif

void game_settings(Settings* settings) {
    if (IsKeyPressed(KEY_F4)) {

        settings->muted = !settings->muted;
    }

    else if (IsKeyPressed(KEY_F8)) {

        settings->rotated = true;
    }

    else if (IsKeyPressed(KEY_F9)) {

        settings->zommed  = !settings->zommed;
    }

    else if (IsKeyPressed(KEY_F10)) {

        settings->attribute = !settings->attribute;
    }

    else if (IsKeyPressed(KEY_F11)) {
        static int screenshotID = 0;


        TakeScreenshot(TextFormat("/screenshots/screenshots(%d).png", screenshotID));
        screenshotID += 1;
    }

    if (settings->muted)
        SetMasterVolume(0.0f);

    else
        SetMasterVolume(1.0f);
}

// --- src/main.c ---
int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    InitAudioDevice();

    SetTargetFPS(60);

    // Core
    Pitch       pitch           = {
        .area  = {
            .width  = WINDOW_WIDTH,
            .height = WINDOW_HEIGHT,
            .x = 0,
            .y = 0
        },

        .strip = {
            WINDOW_WIDTH / 24.0f,
            WINDOW_HEIGHT
        },

        .bound = {
            .width  = pitch.area.width  - pitch.strip.x * 2.0f,
            .height = pitch.area.height - pitch.strip.x * 2.0f,
            .x      = pitch.area.x + pitch.strip.x,
            .y      = pitch.area.y + pitch.strip.x,
        }
    };
    Player*     players         = call_players(&pitch, 7, 7);
    Referee     referee         = create_referee(pitch.area.width / 2.0f, pitch.bound.height);
    Camera2D    camera          = {
        .offset = {
            WINDOW_WIDTH  / 2.0f,
            WINDOW_HEIGHT / 2.0f
        },
        .rotation = 0.0f,
        .target = {
            pitch.area.width  / 2.0f,
            pitch.area.height / 2.0f
        },
        .zoom = 1.0f
    };

    referee.chase_target   = (Vector2) {
        GetRandomValue(pitch.bound.x, pitch.bound.x + pitch.bound.width),
        GetRandomValue(pitch.bound.y, pitch.bound.y + pitch.bound.height)
    };

    // Textures
    // RenderTexture2D goalStand = LoadRenderTexture(pitch.area.width, pitch.area.height);

    // Game Setup
    bool        game_start  = false;
    bool        game_intro  = false;
    bool        game_skip   = false;
    bool        game_menu   = false;

    float       lighting    = 0.7f;
    float       timerLight  = 2.0f / 4.0f;

    Rectangle   attributeUI = {
        .width  = WINDOW_WIDTH,
        .height = WINDOW_HEIGHT * 0.07
    };

    attributeUI.x = (WINDOW_WIDTH - attributeUI.width) / 2.0f;
    attributeUI.y = WINDOW_HEIGHT - attributeUI.height;

    // Sound Effects and Audios
    Sound       floodlight_sfx      = LoadSound(ASSETS_PATH "/audios/floodlight.wav");
    Sound       whistle_sfx         = LoadSound(ASSETS_PATH "/audios/referee-whistle.wav");
    Music       fan_shout_music     = LoadMusicStream(ASSETS_PATH "/audios/football-fan-shout.mp3");
    Music       before_match_music  = LoadMusicStream(ASSETS_PATH "/audios/football-before-match.mp3");


    const char* loading_title[] = {
        "Warming Up...",
        "Adjusting the Lighting..."
    };


    if (players) {
        Vector2 stamina_hud_size      = {
            attributeUI.width  * 0.3f,
            attributeUI.height * 0.3f
        };
        Vector2 stamina_hud_pos       = {
            attributeUI.x + (attributeUI.width  - stamina_hud_size.x) * 0.5f,
            attributeUI.y + (attributeUI.height - stamina_hud_size.y) * 0.5f
        };

        PlayMusicStream(fan_shout_music);
        PlayMusicStream(before_match_music);

        while (!WindowShouldClose()) {
            // Vector2     mousePos = GetMousePosition();

            float       dt        = GetFrameTime();
            // float       scroll    = GetMouseWheelMove();

            float    curr_stamina = (stamina_hud_size.x * (players->stamina / players->max_stamina));

            curr_stamina = curr_stamina > stamina_hud_size.x * 0.03 ? curr_stamina : stamina_hud_size.x * 0.03;


            game_settings(&settings);


            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {

                game_menu = !game_menu;
            }


            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

                game_intro = true;
            }

            else if (IsKeyPressed(KEY_TAB)) {

                game_skip = true;
            }

            if (game_skip) {
                if (lighting <= 0.8f)
                    lighting += dt;
                else {

                    PauseMusicStream(before_match_music);

                    game_start  = true;
                    game_intro  = false;
                }
            }

            if (game_start) {
                static float end = 0.0f;
                if (!players->indicated_obj)
                    players->indicated_obj = &referee.center;

                if (settings.rotated) {
                    end += 90.0f;
                    settings.rotated = false;
                }

                camera.rotation = Lerp(camera.rotation, end, 45 * dt);

                if (settings.zommed){
                    if (camera.zoom <= 5.0f)
                        camera.zoom += 2 * dt;
                }

                else {
                    if (camera.zoom >= 1.0f)
                        camera.zoom -= 2.f * dt;
                }

                update_players(players, &camera, dt);
                updaet_referee(&referee, &pitch, &whistle_sfx, dt);

            } else {
                if (game_intro) {
                    if (lighting >= 0.0f) {
                        if (timerLight >= 0.0f) {

                            timerLight  -= dt;
                        } else {
                            lighting    -= 0.7f / 4.0f;

                            SetMusicVolume(before_match_music, 0.5f);
                            PlaySound(floodlight_sfx);

                            timerLight   = 2.0f / 4.0f;
                        }
                    } else {
                        PauseMusicStream(before_match_music);
                        UpdateMusicStream(fan_shout_music);


                        float length    = GetMusicTimeLength(fan_shout_music);
                        float played   = GetMusicTimePlayed(fan_shout_music);


                        if (camera.zoom <= 4.0f)
                            camera.zoom += dt;
                        else {
                            if (length - played >= 0.05f) {

                                camera.rotation += 20.0f * dt;
                            } else {

                                game_intro = false;
                                game_start = true;

                                PauseMusicStream(fan_shout_music);
                            }
                        }
                    }
                }
            }

            UpdateMusicStream(before_match_music);

            BeginDrawing();

                ClearBackground((Color){ 25, 25, 25, 255 });

                BeginMode2D(camera);

                    draw_pitch(&pitch);

                    draw_players(players);

                    draw_referee(&referee);

                EndMode2D();

                if (game_menu) {

                    // DrawRectangle
                }

                if (!game_start) {

                    BeginBlendMode(BLEND_ALPHA);

                        DrawRectangle(
                            0,
                            0,
                            WINDOW_WIDTH,
                            WINDOW_HEIGHT,
                            Fade(BLACK, lighting)
                        );

                    EndBlendMode();

                    if (!game_menu) {
                        const char* progression = WINDOW_TITLE;


                        if (game_intro) {

                            if (lighting > 0.0f)
                                progression = loading_title[1];
                            else
                                progression = loading_title[0];

                        } else {
                            DrawText(
                                "Left Click to Start / Right Click to Open Menu",
                                (WINDOW_WIDTH - MeasureText("Left Click to Start / Right Click to Open Menu", 15)) * 0.5f,
                                WINDOW_HEIGHT * 0.9f,
                                15,
                                (Color) {0xFA, 0xCC, 0x15, 0xff}
                            );
                        }

                        DrawTextPro(
                            GetFontDefault(),
                            progression,
                            (Vector2){
                                WINDOW_WIDTH  * 0.5f,
                                WINDOW_HEIGHT * 0.5f
                            },
                            (Vector2){
                                MeasureText(progression, 40) * 0.5f,
                                40 * 0.5f
                            },
                            0.0f,
                            40,
                            4,
                            WHITE
                        );
                    }
                } else if (settings.attribute) {

                    BeginBlendMode(BLEND_ALPHA);

                        DrawRectangleRec(attributeUI, Fade(BLACK, 0.5f));

                        DrawRectangleRounded(
                            (Rectangle){
                                stamina_hud_pos.x,
                                stamina_hud_pos.y,
                                stamina_hud_size.x,
                                stamina_hud_size.y
                            },
                            50.0f,
                            0,
                            Fade(WHITE_NORD1, 0.5f)
                        );

                        DrawRectangleRounded(
                            (Rectangle){
                                stamina_hud_pos.x,
                                stamina_hud_pos.y,
                                curr_stamina,
                                stamina_hud_size.y
                            },
                            50.0f,
                            0,
                            WHITE_NORD4
                        );

                    EndBlendMode();
                }

            EndDrawing();
        }
    }

    else {
        const char* msg = "Memory crash";

        while (!WindowShouldClose()) {
            BeginDrawing();

                ClearBackground((Color){0x22, 0x22, 0x22, 0xff});
                DrawTextEx(
                    GetFontDefault(),
                    msg,
                    (Vector2){
                        .x = (WINDOW_WIDTH - MeasureText(msg, 40)) * 0.5f,
                        .y = (WINDOW_HEIGHT - 5) * 0.5f
                    },
                    40,
                    5,
                    RED
                );

            EndDrawing();
        }
    }

    // Free up the Players' heap memory usage...
    kill_players(players);

    // Free up texture memory usage...
    // UnloadRenderTexture(goalStand);

    // Unload the music streams...
    UnloadMusicStream(before_match_music);

    UnloadMusicStream(fan_shout_music);

    UnloadSound(floodlight_sfx);

    UnloadSound(whistle_sfx);

    // Close the Raylib Audio Subsystem...
    CloseAudioDevice();

    // Close Raylib Window...
    CloseWindow();
}
