#include <raylib.h>
#include <iostream>
#include "bullet.h"
#include "enemy.h"
#include <vector>

using namespace std;

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

void UpdatePlane(PlanePlayer *player, float delta, Vector4 flightArea);
void UpdateLeftBullet(vector<Bullet> &bullets, Texture2D &texture, Vector2 &position, int &shotTimer);
void UpdateRightBullet(vector<Bullet> &bullets, Texture2D &texture, Vector2 &position, int &shotTimer);

int main(void)
{
    static vector<Bullet> bulletsRight;
    static vector<Bullet> bulletsLeft;
    static vector<Enemy> defaultEnemy;

    float screenWidth = 1920.f;
    float screenHeight = 1080.f;
    InitWindow(screenWidth, screenHeight, "DesertSpaceShooter");
    Image icon = LoadImage("../myymedia/icon.ico");
    SetWindowIcon(icon);
    UnloadImage(icon);

    Image background = LoadImage("../mymedia/2d_desert_sprite.png");
    ImageResize(&background, background.width, screenHeight);
    Texture2D backgroundTexture = LoadTextureFromImage(background);
    Vector2 backgroundPos = {(screenWidth - backgroundTexture.width) / 2, 0};
    UnloadImage(background);

    Image bulletImg = LoadImage("../mymedia/bullet_0.png");
    Texture2D bulletTexture = LoadTextureFromImage(bulletImg);
    UnloadImage(bulletImg);

Image bulletImg = LoadImage("../mymedia/bullet_0.png");
    Texture2D bulletTexture = LoadTextureFromImage(bulletImg);
    UnloadImage(bulletImg);

    Image planeImg = LoadImage("../mymedia/plane_100_0.png");
    Vector2 planePosition = {screenWidth / 2, screenHeight - 100};
    PlanePlayer planePlayer = {0};
    planePlayer.planeTexture = LoadTextureFromImage(planeImg);
    planePlayer.position = planePosition;
    planePlayer.speed = 8.f;
    planePlayer.canShoot = true;
    UnloadImage(planeImg);

    Vector4 flightArea = {
        backgroundPos.x,
        backgroundPos.y,
        backgroundPos.x + backgroundTexture.width,
        backgroundPos.y + backgroundTexture.height};

    int shotTimer = 0;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        // Move player around
        UpdatePlane(&planePlayer, deltaTime, flightArea);

        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexture(backgroundTexture, backgroundPos.x, backgroundPos.y, RAYWHITE);
        DrawTexture(planePlayer.planeTexture, planePlayer.position.x, planePlayer.position.y, WHITE);

        // UpdateLeftBullet(&bulletLeft, planePlayer.position);
        UpdateLeftBullet(bulletsLeft, bulletTexture, planePlayer.position, shotTimer);
        // UpdateRightBullet(bulletRight[i], planePlayer.position);
        UpdateRightBullet(bulletsRight, bulletTexture, planePlayer.position, shotTimer);
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

void UpdateLeftBullet(vector<Bullet> &bullets, Texture2D &texture, Vector2 &position, int &shotTimer)
{
    if (shotTimer < 7)
    {
        shotTimer++;
    }

    if (shotTimer >= 7)
    {
        Bullet bullet = {};
        bullet.speed = 10;
        bullet.texture = texture;
        bullet.x = position.x + 13;
        bullet.y = position.y;
        bullets.push_back(bullet);
        shotTimer = 0;
    }

    for (int i = 0; i < bullets.size(); i++)
    {
        if (!bullets[i].collidesWidth())
        {
            bullets[i].update();
            DrawTexture(bullets[i].texture, bullets[i].x, bullets[i].y, WHITE);
                }
        else
        {
            bullets.erase(bullets.begin() + i);
        }
    }
}

void UpdateRightBullet(vector<Bullet> &bullets, Texture2D &texture, Vector2 &position, int &shotTimer)
{
    if (shotTimer < 7)
    {
        shotTimer++;
    }

    if (shotTimer >= 7)
    {
        Bullet bullet = {};
        bullet.speed = 10;
        bullet.texture = texture;
        bullet.x = position.x + 78;
        bullet.y = position.y;
        bullets.push_back(bullet);
        shotTimer = 0;
    }

    for (int i = 0; i < bullets.size(); i++)
    {
        if (!bullets[i].collidesWidth())
        {
            bullets[i].update();
            DrawTexture(bullets[i].texture, bullets[i].x, bullets[i].y, WHITE);
        }
        else
        {
            bullets.erase(bullets.begin() + i);
        }
    }
}
