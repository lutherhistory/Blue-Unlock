// Sensible Soccer Inspire
#include <raylib.h>
#include <raymath.h>

#include "football/pitch.h"
#include "football/player.h"

#include "football/referee.h"
#include "need.h"

typedef struct {

    bool muted;
    bool rotated;

} Settings;

void game_settings(Settings* settings) {
    if (IsKeyPressed(KEY_F4)) {
        if (settings->muted)
            SetMasterVolume(0.0f);

        else
            SetMasterVolume(1.0f);

        settings->muted = !settings->muted;
    }

    else if (IsKeyPressed(KEY_F8)) {

        settings->rotated = true;
    }

    else if (IsKeyPressed(KEY_F11)) {
        static int screenshotID = 0;


        TakeScreenshot(TextFormat("/screenshots/screenshots(%d).png", screenshotID));
        screenshotID += 1;
    }
}

// --- src/main.c ---
int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    InitAudioDevice();

    SetTargetFPS(60);

    Pitch       pitch       = {
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
    Player*     players     = call_players(&pitch, 7, 7);
    Referee     referee     = create_referee(100, 100, 50);
    Camera2D    camera      = {
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

    bool        game_start  = false;
    bool        game_intro  = false;

    float       lighting    = 0.7f;
    float       timerLight  = 2.0f / 4.0f;

    // Sound Effects and Audios
    Sound       floodlight_sfx      = LoadSound(ASSETS_PATH "/audios/floodlight.wav");
    Music       fan_shout_music     = LoadMusicStream(ASSETS_PATH "/audios/football-fan-shout.mp3");
    Music       before_match_music  = LoadMusicStream(ASSETS_PATH "/audios/football-before-match.mp3");


    const char* loading_title[] = {
        "Warming Up...",
        "Adjusting the Lighting..."
    };


    if (players) {
        Settings settings = {
            .rotated = false,
            .muted   = true
        };

        PlayMusicStream(fan_shout_music);
        PlayMusicStream(before_match_music);

        while (!WindowShouldClose()) {
            Vector2     mousePos = GetMousePosition();

            float       dt        = GetFrameTime();
            float       scroll    = GetMouseWheelMove();


            game_settings(&settings);


            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                game_intro = true;
            }

            if (game_start) {
                static float end = 0.0f;

                if (settings.rotated) {
                    end += 90.0f;
                    settings.rotated = false;
                }

                camera.rotation = Lerp(camera.rotation, end, 45 * dt);

                update_players(players, &camera, dt);

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

                EndMode2D();


                if (!game_start) {
                    const char* progression = WINDOW_TITLE;


                    BeginBlendMode(BLEND_ALPHA);

                        DrawRectangle(
                            0,
                            0,
                            WINDOW_WIDTH,
                            WINDOW_HEIGHT,
                            Fade(BLACK, lighting)
                        );

                    EndBlendMode();


                    if (game_intro) {

                        if (lighting > 0.0f)
                            progression = loading_title[1];
                        else
                            progression = loading_title[0];

                    } else {
                        DrawText(
                            "Click to start",
                            (WINDOW_WIDTH - MeasureText("Click to start", 20)) * 0.5f,
                            WINDOW_HEIGHT * 0.9f,
                            20,
                            Fade(YELLOW, 0.7)
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
                } else {

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

    // Free up the heap memory usage...
    kill_players(players);

    UnloadMusicStream(before_match_music);

    UnloadMusicStream(fan_shout_music);

    UnloadSound(floodlight_sfx);

    // Close the Raylib Audio Subsystem...
    CloseAudioDevice();

    // Close Raylib Window...
    CloseWindow();
}
