#include <raylib.h>
#include <math.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 576
#define UPDATE_DT (1.0f / 60.0f)
#define MAGNITUDE(vec) sqrtf(vec.x * vec.x + vec.y * vec.y)

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Bird Demo");
    SetTargetFPS(60);

    float velocity = 0.0f;
    float radius = 30.0f;
    float target_radius = 15.0f;
    float player_speed = 400.0f;
    float player_height = 140.0f;
    float floor_height = 60.0f;
    float leg_thickness = 8.0f;

    Vector2 player_pos = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT - player_height - floor_height };
    Vector2 foot_target = { player_pos.x, player_pos.y + player_height };

    while (!WindowShouldClose()) {
        int left_right = (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) - (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT));
        velocity = left_right * player_speed;;
        player_pos.x += velocity * UPDATE_DT;

        BeginDrawing();
        ClearBackground(BLACK);

        Vector2 foot_vec_constrained = { foot_target.x - player_pos.x, foot_target.y - player_pos.y };
        float unconstrained_distance = MAGNITUDE(foot_vec_constrained);
        if (unconstrained_distance > player_height) {
            foot_vec_constrained.x *= player_height / unconstrained_distance;
            foot_vec_constrained.y *= player_height / unconstrained_distance;
        }
        Vector2 foot_pos_constrained = { player_pos.x + foot_vec_constrained.x, player_pos.y + foot_vec_constrained.y };

        DrawCircleV(player_pos, radius, WHITE);
        DrawLineEx(player_pos, foot_pos_constrained, leg_thickness, WHITE);
        DrawCircleLinesV(foot_target, target_radius, YELLOW);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
