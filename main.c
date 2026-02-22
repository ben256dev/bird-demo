#include <raylib.h>
#include <math.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 576
#define UPDATE_DT (1.0f / 60.0f)
#define MAGNITUDE(vec) sqrtf(vec.x * vec.x + vec.y * vec.y)

Vector2 two_form_solve_elbow_vec(Vector2 shoulder, Vector2 end_effector, float l1, float l2, int elbow_direction_sign) {
    float x = end_effector.x - shoulder.x;
    float y = end_effector.y - shoulder.y;

    float numerator = l1 * l1 + x * x + y * y - l2 * l2;
    float denominator = 2.0f * l1 * sqrtf(x * x + y * y);

    float elbow_angle = acosf(numerator / denominator);
    if (elbow_angle != elbow_angle) {
        elbow_angle = 0.0f;
    }

    float end_effector_angle = atan2f(y, x);
    float final_angle = end_effector_angle + elbow_angle * elbow_direction_sign;

    return (Vector2){ cosf(final_angle) * l1, sinf(final_angle) * l1 };
}

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
    float leg_length = 160.0f;

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
        if (unconstrained_distance > leg_length) {
            foot_vec_constrained.x *= leg_length / unconstrained_distance;
            foot_vec_constrained.y *= leg_length / unconstrained_distance;
        }
        Vector2 foot_pos_constrained = { player_pos.x + foot_vec_constrained.x, player_pos.y + foot_vec_constrained.y };

        DrawCircleV(player_pos, radius, WHITE);

        Vector2 elbow_vec = two_form_solve_elbow_vec(player_pos, foot_pos_constrained, leg_length / 2, leg_length / 2, 1);
        Vector2 elbow_pos = { player_pos.x + elbow_vec.x, player_pos.y + elbow_vec.y };
        DrawLineEx(player_pos, elbow_pos, leg_thickness, WHITE);
        DrawLineEx(elbow_pos, foot_pos_constrained, leg_thickness, WHITE);
        DrawCircleLinesV(foot_target, target_radius, YELLOW);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
