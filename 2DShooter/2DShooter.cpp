#include <raylib.h>
#include <iostream>
#include "bullet.h"

#define PLAYER_HOR_SPD 350.0f
#define PLAYER_MAX_SHOTS 8

typedef struct PlanePlayer
{
    Vector2 position;
    float speed;
    bool canShoot;
    float health = 100.f;
    Texture2D planeTexture;
} PlanePlayer;

typedef struct BulletPlayer
{
    Vector2 position;
    float speed;
    bool active;
    Color color;
} BulletPlayer;

void UpdatePlane(PlanePlayer *player, float delta, Vector4 flightArea);
void UpdateLeftBullet(BulletPlayer (*bullet)[PLAYER_MAX_SHOTS], Vector2 position);
void UpdateRightBullet(BulletPlayer &bullet, Vector2 position);
void ResetBullet(BulletPlayer &bullet, Vector2 position, int number);

int main(void)
{
    static BulletPlayer bulletLeft[PLAYER_MAX_SHOTS] = {0};
    static BulletPlayer bulletRight[PLAYER_MAX_SHOTS] = {0};
    static Bullet *bullet[PLAYER_MAX_SHOTS] = {};

    float screenWidth = 1920.f;
    float screenHeight = 1080.f;
    InitWindow(screenWidth, screenHeight, "Ett program");

    Image background = LoadImage("../mymedia/2d_desert_sprite.png");
    ImageResize(&background, background.width, screenHeight);
    Texture2D backgroundTexture = LoadTextureFromImage(background);
    Vector2 backgroundPos = {(screenWidth - backgroundTexture.width) / 2, 0};
    UnloadImage(background);

    Image planeImg = LoadImage("../mymedia/plane_100_0.png");
    Vector2 planePosition = {screenWidth / 2, screenHeight - 100};
    PlanePlayer planePlayer = {0};
    planePlayer.planeTexture = LoadTextureFromImage(planeImg);
    planePlayer.position = planePosition;
    planePlayer.speed = 8.f;
    planePlayer.canShoot = true;
    UnloadImage(planeImg);

    // Starting positions of bullets
    Vector2 bulletLeftStartPos = {planePosition.x + 16, planePosition.y + 4};
    Vector2 bulletRightStartPos = {planePosition.x + 80, planePosition.y + 4};
    //
    for (int i = 0; i < PLAYER_MAX_SHOTS; i++)
    {
        bulletLeft[i].active = false;
        bulletLeft[i].color = RED;
        bulletLeft[i].position = bulletLeftStartPos;
        bulletLeft[i].speed = 1000;

        bulletRight[i].active = false;
        bulletRight[i].color = RED;
        bulletRight[i].position = bulletRightStartPos;
        bulletRight[i].speed = 8;
    }

    for (int x = 0; x < PLAYER_MAX_SHOTS; x++)
    {
        bullet[x] = new Bullet();
        bullet[x]->height = 20;
        bullet[x]->width = 5;
        bullet[x]->speed = 10;
        bullet[x]->x = planePosition.x + 80;
        bullet[x]->y = planePosition.y;
    }
    Vector4 flightArea = {
        backgroundPos.x,
        backgroundPos.y,
        backgroundPos.x + backgroundTexture.width,
        backgroundPos.y + backgroundTexture.height};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        // Move player around
        UpdatePlane(&planePlayer, deltaTime, flightArea);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(backgroundTexture, backgroundPos.x, backgroundPos.y, RAYWHITE);
        DrawTexture(planePlayer.planeTexture, planePlayer.position.x, planePlayer.position.y, WHITE);

        // UpdateLeftBullet(&bulletLeft, planePlayer.position);

        for (int i = 0; i <= PLAYER_MAX_SHOTS; i++)
        {

            bullet[i]->update();
            // UpdateRightBullet(bulletRight[i], planePlayer.position);
        }

        // DrawText("Dette er ett spill", screenWidth / 2, screenHeight / 2, 45, GREEN);
        EndDrawing();
    }
    UnloadTexture(planePlayer.planeTexture);
    UnloadTexture(backgroundTexture);
    CloseWindow();

    return 0;
}

void UpdatePlane(PlanePlayer *player, float delta, Vector4 flightArea)
{
    if (IsKeyDown(KEY_RIGHT) && player->position.x <= flightArea.z - 100)
        player->position.x += PLAYER_HOR_SPD * delta;
    if (IsKeyDown(KEY_LEFT) && player->position.x >= flightArea.x)
        player->position.x -= PLAYER_HOR_SPD * delta;
    if (IsKeyDown(KEY_DOWN) && player->position.y <= flightArea.w - 100)
        player->position.y += PLAYER_HOR_SPD * delta;
    if (IsKeyDown(KEY_UP) && player->position.y >= flightArea.y)
        player->position.y -= PLAYER_HOR_SPD * delta;
}

void UpdateLeftBullet(BulletPlayer (*bullet)[PLAYER_MAX_SHOTS], Vector2 position)
{
    for (int i = 0; i < PLAYER_MAX_SHOTS; i++)
    {

        if (!bullet[i]->active)
        {
            bullet[i]->position = Vector2{position.x + 16, position.y};
            bullet[i]->active = true;
            break;
        }
    }

    for (int i = 0; i < PLAYER_MAX_SHOTS; i++)
    {
        if (bullet[i]->active)
        {
            bullet[i]->position.y -= bullet[i]->speed * GetFrameTime();

            if (bullet[i]->position.y < 0)
                bullet[i]->active = false;

            if (bullet[i]->active)
                DrawRectangle(bullet[i]->position.x, bullet[i]->position.y, 5, 20, bullet[i]->color);
        }
    }
}

void UpdateRightBullet(BulletPlayer &bullet, Vector2 position)
{
    float planeX = position.x + 80;

    if (!bullet.active)
    {
        bullet.active = true;
        // printf("frameTime: %f", GetFrameTime());
        bullet.position.y -= bullet.speed;
        DrawRectangle(planeX, bullet.position.y, 5, 20, bullet.color);
    }

    if (bullet.position.y < 0)
    {
        bullet.active = false;
    }

    if (bullet.active)
    {
        ResetBullet(bullet, {planeX, position.y}, 1);
    }
}

void ResetBullet(BulletPlayer &bullet, Vector2 position, int number)
{
    Vector2 bulletPosition = {position.x, position.y - 20};
    bullet.position = bulletPosition;
    bullet.speed = 8;
    bullet.color = RED;
    bullet.active = false;
}
