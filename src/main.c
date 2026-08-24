// #include <raylib.h>
#include <raymath.h>

#include <stdio.h>
#include <stdlib.h>

#define WIDTH  900
#define HEIGHT 600
#define TITLE  "Unfair Soccer Matches"

#define BG_1 (Color) { 0x3d, 0x71, 0x2f, 0xff }
#define BG_2 (Color) { 0x43, 0x7b, 0x32, 0xff }
#define QUANTITY 5

const int striped_w = WIDTH / 12;

typedef struct {

	// Main Context
	float radius;
	Vector2 pos;

	// Physics Context
	Vector2 velocity;
	Vector2 acceleration;
	float friction;

} SoccerBall;

typedef struct {

	// Body
	Rectangle rect;
	Color color;

	// Ability
	bool kicked;

	// Physics
	float speed;

	// Delay Timer
	float kickTimer;

} SoccerPlayer;


SoccerPlayer* welcomePlayers();
void byebyePlayers(SoccerPlayer*);

void draw_soccerfield(float scale);
void draw_soccerplayer(SoccerPlayer* players);
void draw_soccerball(SoccerBall* ball);

void update_soccerball_physics(SoccerBall* ball, float dt, Sound* sfx);
void update_soccerplayers(SoccerPlayer* players, float dt);


int main() {
	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
	
	InitWindow(WIDTH, HEIGHT, TITLE);
	InitAudioDevice();

	SetTargetFPS(60);

	Sound sfx = LoadSound(ASSETS_PATH "/ball-collided-sfx.wav");
	Music bg_music = LoadMusicStream(ASSETS_PATH "/match-shout-background.mp3");	

	Camera2D camera = { 0 };
	SoccerPlayer* players = welcomePlayers();
	SoccerBall ball = {
		.radius = 10,
		.pos = { WIDTH / 2.0f, HEIGHT / 2.0f },
		.friction = 4.0f
	};

	int target = 0;
	bool getStart = false;
	float horizontalShot = false;
	float zoomInShot = false;
	float jumpingTimer = 1.5f;
	float offetX = 0.5;

	float played = GetMusicTimePlayed(bg_music);
	float length = GetMusicTimeLength(bg_music);

	camera.offset = (Vector2){ WIDTH  / 2.0f, HEIGHT / 2.0f };
	camera.target = (Vector2){ WIDTH  / 2.0f, HEIGHT / 2.0f };
	camera.rotation = 0.0f; 
	camera.zoom = 1.0f;

	ball.velocity = (Vector2){ 0, 0 },
	ball.acceleration = (Vector2){ 0, 0 };




	while (!WindowShouldClose()) {
		float dt = GetFrameTime();
		Vector2 movement = { 0, 0 };

		update_soccerball_physics(&ball, dt, &sfx);
		UpdateMusicStream(bg_music);

		if (!horizontalShot && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			zoomInShot = true;
			horizontalShot = true;

			PlayMusicStream(bg_music);
		}

		if (zoomInShot) {
			if (camera.zoom >= 1.8f) {
				zoomInShot = false;
			} else {
				camera.zoom += 0.5f * dt;
			}
		}

		if (!zoomInShot && horizontalShot) {
			// camera.rotation >= 90
			if (length - played <= 0.05f) {
				getStart = true;
				PauseMusicStream(bg_music);

				camera.target = (Vector2){
					players[target].rect.x,
					players[target].rect.y
				};

				camera.rotation = Lerp(
				    camera.rotation,
				    90.0f,
				    5.0f * dt
				);

				if (fabsf(camera.rotation - 90.0f) < 0.1f)
				    camera.rotation = 90.0f;
			} else {
				camera.rotation += 20 * dt;
				played = GetMusicTimePlayed(bg_music);
			}
		}


		if (getStart) {
			if (IsKeyDown(KEY_W)) {
				if (horizontalShot) {
					movement.x = -1;
				} else {
					movement.y = -1;
				}
			}

			if (IsKeyDown(KEY_S)) {
				if (horizontalShot) {
					movement.x = 1;
				} else {
					movement.y = 1;
				}
			}

			if (IsKeyDown(KEY_A)) {
				if (horizontalShot) {
					movement.y = 1;
				}

				else {
					movement.x = -1;
				}
			}

			if (IsKeyDown(KEY_D)) {
				if (horizontalShot) {
					movement.y = -1;
				}

				else {
					movement.x = 1;
				}
			}

			if ((movement.x != 0 || movement.y != 0)
			    && IsKeyPressed(KEY_SPACE)
			    && !players[target].kicked) {

			    players[target].kicked = true;

			    ball.velocity = Vector2Scale(
			        Vector2Normalize(movement),
			        300.0f
			    );
			}

			players[target].rect.x += movement.x * 100 * dt;
			players[target].rect.y += movement.y * 100 * dt;
		}


		BeginDrawing();

			ClearBackground(RAYWHITE);

			BeginMode2D(camera);
			
				draw_soccerfield(1.0f);
				draw_soccerplayer(players);
				draw_soccerball(&ball);

			EndMode2D();

			if (!horizontalShot) {
				DrawRectangle(
					0, 
					0, 
					WIDTH, 
					HEIGHT, 
					Fade(BLANK, 0.5)
				);

				DrawText(
					TITLE, 
					(WIDTH - MeasureText(TITLE, 40))/2.0f, 
					(HEIGHT - 20 ) / 2.0f, 
					40, 
					WHITE
				);

				if (jumpingTimer < 0) {
					jumpingTimer = 0.5;
					offetX = 0.8;
				} else {
					jumpingTimer -= dt;
					offetX = 0.5;
				}

				DrawText(
					"Click to Start", 
					(WIDTH - MeasureText("Click to Start", 20))/2.0f, 
					(HEIGHT - 20) / 2.0f + 60, 
					20, 
					Fade(YELLOW, offetX)
				);			
			}
		
		EndDrawing();
	}

	byebyePlayers(players);

	UnloadSound(sfx);

	UnloadMusicStream(bg_music);

	CloseAudioDevice();

	CloseWindow();
}

SoccerPlayer* welcomePlayers() {
    SoccerPlayer* players =
        malloc(sizeof(SoccerPlayer) * QUANTITY);

    if (!players) {
        perror("alloc");
        exit(1);
    }

    for (int i = 0; i < QUANTITY; i++) {

        players[i].rect = (Rectangle){
            .width  = 30,
            .height = 30,
            .x      = WIDTH / 2.0f + 100,
            .y      = HEIGHT / 2.0f
                    + (i - (QUANTITY - 1) / 2.0f) * 80.0f
        };

        players[i].speed = 100.0f;
        players[i].color = RED;
        players[i].kicked = false;
        players[i].kickTimer = 1.5f;
    }

    return players;
}

void byebyePlayers(SoccerPlayer* players) {
	free(players);

	TraceLog(LOG_INFO, "Free up successful");
}

void draw_soccerfield(float scale) {
	/// Stripped Grass Field
	for (int i=0; i < 12; i++) {
		DrawRectangle(
			striped_w * i, 
			0, 
			striped_w * scale, 
			HEIGHT * scale, 
			(i % 2) ? BG_2 : BG_1
		);
	}

	/// Playground
	DrawRectangleLinesEx(
		(Rectangle){
			striped_w, 
			striped_w, 
			striped_w * 10, 
			HEIGHT - striped_w * 2,
		}, 
		5.0f, 
		RAYWHITE
	);

	/// Center of Field
	DrawRing(
		(Vector2){WIDTH / 2.f, HEIGHT / 2.0f}, 
		striped_w + 10, 
		striped_w + 10 - 5.0f, 
		0.0f, 
		360.0f, 
		1, 
		RAYWHITE
	);

	DrawLineEx(
		(Vector2){ WIDTH / 2.0f, striped_w }, 
		(Vector2){ WIDTH / 2.0f, HEIGHT - striped_w }, 
		5.0f, 
		RAYWHITE
	);

	DrawCircle(
		WIDTH / 2.0f, 
		HEIGHT / 2.0f, 
		6.0f, 
		RAYWHITE
	);

	/// Team 1's Goal
	DrawRectangleLinesEx(
		(Rectangle){
			striped_w, 
			(HEIGHT - striped_w * 3.8f) / 2.0f,
			striped_w * 1.7f,
			striped_w * 3.8f
		}, 
		5.0f, 
		RAYWHITE
	);

	DrawRectangleLinesEx(
		(Rectangle){
			striped_w, 
			(HEIGHT - striped_w * 2.0f) / 2.0f,
			striped_w * 0.7f,
			striped_w * 2.0f
		}, 
		5.0f, 
		RAYWHITE
	);	

	DrawRectangleLinesEx(
		(Rectangle){
			striped_w - striped_w * 0.4f + 5.0F, 
			(HEIGHT - striped_w * 1.2f) / 2.0f,
			striped_w * 0.4f,
			striped_w * 1.2f
		}, 
		5.0f, 
		RAYWHITE
	);

	DrawRing(
		(Vector2){ 
			striped_w * 1.9f, 
			HEIGHT / 2.0f 
		}, 
		90, 
		90 - 5.0f, 
		-50.0f, 
		50.0f, 
		0, 
		RAYWHITE
	);

	DrawCircle(
		striped_w * 2.1f, 
		HEIGHT / 2.0f, 
		5.5f, 
		RAYWHITE
	);

	/// Team 2's Goal
	DrawRectangleLinesEx(
		(Rectangle){
			WIDTH - striped_w - striped_w * 1.7f, 
			(HEIGHT - striped_w * 3.8f) / 2.0f,
			striped_w * 1.7f,
			striped_w * 3.8f
		}, 
		5.0f, 
		RAYWHITE
	);

	DrawRectangleLinesEx(
		(Rectangle){
			(WIDTH - striped_w * 0.7f) - striped_w, 
			(HEIGHT - striped_w * 2.0f) / 2.0f,
			striped_w * 0.7f,
			striped_w * 2.0f
		}, 
		5.0f, 
		RAYWHITE
	);

	DrawRectangleLinesEx(
		(Rectangle){
			WIDTH - striped_w - 5.0f, 
			(HEIGHT - striped_w * 1.2f) / 2.0f,
			striped_w * 0.4f,
			striped_w * 1.2f
		}, 
		5.0f, 
		RAYWHITE
	);

	DrawRing(
		(Vector2){ 
			WIDTH -	striped_w * 1.9f, 
			HEIGHT / 2.0f 
		}, 
		90, 
		90 - 5.0f, 
		130.0f, 
		230.0f, 
		0, 
		RAYWHITE
	);

	DrawCircle(
		WIDTH - striped_w * 2.1f, 
		HEIGHT / 2.0f, 
		5.5f, 
		RAYWHITE
	);
}

void draw_soccerplayer(SoccerPlayer* players) {
	for (int i=0; i < QUANTITY; i++) {
		Vector2 origin = { 
			players->rect.width  / 2.0f,
			players->rect.height / 2.0f
		};

		DrawRectanglePro(
			players[i].rect, 
			origin, 
			0.0f, 
			players[i].color
		);

		DrawRectangleLinesEx(
			(Rectangle){
				players[i].rect.x - players[i].rect.width / 2.0f,
				players[i].rect.y - players[i].rect.height / 2.0f,
				players[i].rect.width,
				players[i].rect.height
			}, 
			3.0f, 
			BLACK
		);
	}
}

void draw_soccerball(SoccerBall* ball) {
	DrawCircleV(ball->pos, ball->radius, BLACK);

	DrawCircleV(ball->pos, ball->radius * 0.5f, WHITE);
}

void update_soccerball_physics(SoccerBall* ball, float dt, Sound* sfx) {
	ball->velocity.x *= expf(-ball->friction * dt);
	ball->velocity.y *= expf(-ball->friction * dt);

	ball->pos.x += ball->velocity.x * dt;
	ball->pos.y += ball->velocity.y * dt;

	// Collision
	Rectangle field = {
		striped_w, 
		striped_w, 
		striped_w * 10, 
		HEIGHT - striped_w * 2,
	};

	if (ball->pos.x <= field.x
		|| ball->pos.x >= field.x + field.width) {

		ball->velocity.x *= -1;
		PlaySound(*sfx);
	}

	if (ball->pos.y <= field.y
		|| ball->pos.y >= field.y + field.height) {

		ball->velocity.y *= -1;
		PlaySound(*sfx);
	}
}

void update_soccerplayers(SoccerPlayer* players, float dt) {

}