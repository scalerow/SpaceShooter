#include <raylib.h>
#include <iostream>

#define PLAYER_HOR_SPD 350.0f

typedef struct PlanePlayer
{
    Vector2 position;
    float speed;
    bool canShoot;
    float health = 100.f;
    Texture2D planeTexture;
} PlanePlayer;

void UpdatePlane(PlanePlayer *player, float delta, int width, int height);

int main(void)
{

    float screenWidth = 1024.f;
    float screenHeight = 1024.f;
    InitWindow(1024, 1024, "Ett program");

    Image background = LoadImage("../mymedia/2d_desert_sprite.png");
    ImageResize(&background, background.width, background.height);

    Image plane = LoadImage("../mymedia/plane_100_0.png");
    Vector2 planePosition = {screenWidth / 2, screenHeight / 2};
    PlanePlayer planePlayer = {0};
    planePlayer.planeTexture = LoadTextureFromImage(plane);
    planePlayer.position = planePosition;
    planePlayer.speed = 8.f;
    planePlayer.canShoot = true;
    UnloadImage(plane);

    Texture2D texture = LoadTextureFromImage(background);

    UnloadImage(background);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        // Move player around
        UpdatePlane(&planePlayer, deltaTime, background.width, background.height);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(texture, 0, 0, RAYWHITE);
        DrawTexture(planePlayer.planeTexture, planePlayer.position.x, planePlayer.position.y, WHITE);

        // DrawText("Dette er ett spill", screenWidth / 2, screenHeight / 2, 45, GREEN);
        EndDrawing();
    }
    UnloadTexture(planePlayer.planeTexture);
    UnloadTexture(texture);
    CloseWindow();

    return 0;
}

void UpdatePlane(PlanePlayer *player, float delta, int width, int height)
{
    if (IsKeyDown(KEY_RIGHT) && player->position.x <= width - 100)
        player->position.x += PLAYER_HOR_SPD * delta;
    if (IsKeyDown(KEY_LEFT) && player->position.x >= 0)
        player->position.x -= PLAYER_HOR_SPD * delta;
    if (IsKeyDown(KEY_DOWN) && player->position.y <= height - 100)
        player->position.y += PLAYER_HOR_SPD * delta;
    if (IsKeyDown(KEY_UP) && player->position.y >= 0)
        player->position.y -= PLAYER_HOR_SPD * delta;
}