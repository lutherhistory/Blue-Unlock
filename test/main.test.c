#include <raylib.h>
#include <rlgl.h>

#define BG (Color) { 0xf9, 0xef, 0xde, 0xff }

#define CUTE_BLUE   (Color) { 0x59, 0x94, 0xb2, 0xff }
#define CUTE_ORANGE (Color) { 0xfd, 0xb3, 0x63, 0xff }
#define CUTE_RED    (Color) { 0xe6, 0x70, 0x52, 0xff }
#define CUTE_GREEN  (Color) { 0x66, 0xa3, 0x6f, 0xff }
#define CUTE_YELLOW (Color) { 0xf5, 0xc5, 0x66, 0xff }
#define CUTE_CYAN   (Color) { 0x56, 0xa3, 0x97, 0xff}

void DrawParallelogram(Vector2 origin, float width, float height, float skewX, Color color) {
    // Calculate the 4 corners of the parallelogram
    Vector2 p1 = { origin.x + skewX, origin.y };              // Top-left
    Vector2 p2 = { origin.x, origin.y + height };              // Bottom-left
    Vector2 p3 = { origin.x + width, origin.y + height };      // Bottom-right
    Vector2 p4 = { origin.x + width + skewX, origin.y };       // Top-right

    rlBegin(RL_QUADS);
        rlColor4ub(color.r, color.g, color.b, color.a);
        rlVertex2f(p1.x, p1.y);
        rlVertex2f(p2.x, p2.y);
        rlVertex2f(p3.x, p3.y);
        rlVertex2f(p4.x, p4.y);
    rlEnd();
}

int main(void) {
    InitWindow(800, 600, "Cute Geometry");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

            ClearBackground(BG);

            DrawParallelogram(
                (Vector2){ 100.0f, 100.0f },
                200.0f,
                150.0f,
                100.0f,
                CUTE_RED
            );

        EndDrawing();
    }

    CloseWindow();
}
