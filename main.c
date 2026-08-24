#include <raylib.h>

#define WIDTH  900
#define HEIGHT 600

#define BG_1 (Color) { 0x3d, 0x71, 0x2f, 0xff }
#define BG_2 (Color) { 0x43, 0x7b, 0x32, 0xff }

void draw_soccerfield(void);

int main() {
	InitWindow(WIDTH, HEIGHT, "Unfair Soccer");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();

			ClearBackground(RAYWHITE);

			draw_soccerfield();
		
		EndDrawing();
	}

	CloseWindow();
}


void draw_soccerfield(void) {
	int striped_w = WIDTH / 12;

	/// Stripped Grass Field
	for (int i=0; i < 12; i++) {
		DrawRectangle(
			striped_w * i, 
			0, 
			striped_w, 
			HEIGHT, 
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