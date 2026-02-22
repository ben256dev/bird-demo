#include <raylib.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define UPDATE_DT (1.0f / 60.0f)

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Bird Demo");
    SetTargetFPS(60);

    Vector2 player_pos = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f };
    Vector2 velocity = { 180.0f, 140.0f };
    float radius = 22.0f;

    while (!WindowShouldClose()) {
        player_pos.x += velocity.x * UPDATE_DT;
        player_pos.y += velocity.y * UPDATE_DT;

        if (player_pos.x - radius <= 0.0f || player_pos.x + radius >= SCREEN_WIDTH) {
            velocity.x = -velocity.x;
        }
        if (player_pos.y - radius <= 0.0f || player_pos.y + radius >= SCREEN_HEIGHT) {
            velocity.y = -velocity.y;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        DrawCircleV(player_pos, radius, WHITE);
        DrawCircleLines(player_pos.x, player_pos.y, radius + 6.0f, WHITE);

        DrawText("raylib 2D example", 20, 20, 20, WHITE);
        DrawText("ESC to quit", 20, 48, 16, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
