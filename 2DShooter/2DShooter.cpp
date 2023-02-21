#include <raylib.h>
#include <iostream>
#include "bullet.h"
#include "enemy.h"
#include "player.h"
#include "game.h"
#include <vector>

using namespace std;

typedef struct PlanePlayer
{
    Vector2 position;
    float speed;
    bool canShoot;
    float health = 100.f;
    Texture2D planeTexture;
} PlanePlayer;

void UpdateLeftBullet(vector<Bullet> &bullets, Texture2D &texture, Vector2 &position, int &shotTimer);
void UpdateRightBullet(vector<Bullet> &bullets, Texture2D &texture, Vector2 &position, int &shotTimer);
void UpdateDefaultEnemies(vector<Enemy> &enemies, Texture2D &texture, int xPositions[4]);
// void UpdateDefaultEnemyBullet(vector<Bullet> &bullets, Texture2D &texture, int (&enemyPositions)[4], int &shotTimer);

int main(void)
{
    static vector<Bullet> bulletsRight;
    static vector<Bullet> bulletsLeft;
    static vector<Enemy> defaultEnemy;
    static vector<Bullet> defaultEnemyBullets;

    float screenWidth = 1920.f;
    float screenHeight = 1080.f;
    InitWindow(screenWidth, screenHeight, "DesertSpaceShooter");
    Image icon = LoadImage("../myymedia/icon.ico");
    SetWindowIcon(icon);
    UnloadImage(icon);

    Image bulletImg = LoadImage("../mymedia/bullet_0.png");
    Texture2D bulletTexture = LoadTextureFromImage(bulletImg);
    UnloadImage(bulletImg);

    Image defaultEnemyImg = LoadImage("../mymedia/default_enemy_0.png");
    Texture2D defaultEnemyTexture = LoadTextureFromImage(defaultEnemyImg);
    UnloadImage(defaultEnemyImg);

    Image defaultEnemyBulletImg = LoadImage("../mymedia/bullet_enemy_0.png");
    Texture2D defaultenemyBulletTexture = LoadTextureFromImage(defaultEnemyBulletImg);
    UnloadImage(defaultEnemyBulletImg);

    int enemyPositions[] = {400 + 204, 400 + 408, 400 + 612, 400 + 816};

    int enemyShotTimer = 0;
    Vector2 pos = {50, 50};
    Game game;
    game.gameActive = true;
    game.load(screenHeight, screenWidth);

    Vector4 flightArea = {
        game.backgroudPosition.x,
        game.backgroudPosition.y,
        game.backgroudPosition.x + game.backgroundTexture.width,
        screenHeight};

    Player player;
    player.InitPlayer({screenWidth, screenHeight});

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Move player around
        float deltaTime = GetFrameTime();

        player.UpdatePlayer(deltaTime, flightArea);

        BeginDrawing();
        ClearBackground(BLACK);

        
        DrawTexture(game.backgroundTexture, game.backgroudPosition.x, game.backgroudPosition.y, RAYWHITE);
        DrawTexture(player.planeTexture, player.position.x, player.position.y, WHITE);

        // UpdateLeftBullet(&bulletLeft, planePlayer.position);
        UpdateLeftBullet(bulletsLeft, bulletTexture, player.position, game.shotTimerLeft);
        // UpdateRightBullet(bulletRight[i], planePlayer.position);
        UpdateRightBullet(bulletsRight, bulletTexture, player.position, game.shotTimerRight);

        // UpdateEnemies
        UpdateDefaultEnemies(defaultEnemy, defaultEnemyTexture, enemyPositions);

        // Update enemy bullets
        // UpdateDefaultEnemyBullet(defaultEnemyBullets, defaultenemyBulletTexture, enemyPositions, enemyShotTimer);

        EndDrawing();
    }
    // UnloadTexture(planePlayer.planeTexture);
    // UnloadTexture(backgroundTexture);
    CloseWindow();

    return 0;
}

void UpdateLeftBullet(vector<Bullet> &bullets, Texture2D &texture, Vector2 &position, int &shotTimer)
{
    if (shotTimer < 12)
    {
        shotTimer++;
    }

    if (shotTimer >= 12)
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
        if (!bullets[i].playerBulletCollides())
        {
            bullets[i].updatePlayer();
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
    if (shotTimer < 12)
    {
        shotTimer++;
    }

    if (shotTimer >= 12)
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
        if (!bullets[i].playerBulletCollides())
        {
            bullets[i].updatePlayer();
            DrawTexture(bullets[i].texture, bullets[i].x, bullets[i].y, WHITE);
        }
        else
        {
            bullets.erase(bullets.begin() + i);
        }
    }
}

void UpdateDefaultEnemies(vector<Enemy> &enemies, Texture2D &enemyTexture, int xPositions[4])
{

    if (IsKeyPressed(KEY_SPACE) && enemies.size() > 1)
    {
        enemies[0].health = 0;
    }

    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        if (enemies.size() < MAX_ENEMIES)
        {
            Enemy defEnemy = {};
            defEnemy.active = false;
            defEnemy.speed = 2;
            defEnemy.isBoss = false;
            defEnemy.texture = enemyTexture;
            defEnemy.x = xPositions[i];
            defEnemy.y = -100;
            enemies.push_back(defEnemy);
        }

        if (!enemies[i].active && enemies[i].health >= 0)
            enemies[i].active = true;

        if (enemies[i].health == 0)
        {
            enemies.erase(enemies.begin() + i);
        }

        if (enemies[i].active && enemies[i].health >= 0)
        {
            enemies[i].active = true;
            if (enemies[i].y < 150)
                enemies[i].y += enemies[i].speed;
            else
                enemies[i].hover(xPositions[i], 50);
            DrawTexture(enemies[i].texture, enemies[i].x, enemies[i].y, WHITE);
        }
    }
}

// void UpdateDefaultEnemyBullet(vector<Bullet> &bullets, Texture2D &texture, int (&enemyPositions)[4], int &shotTimer)
// {
//     if (shotTimer < 5)
//     {
//         shotTimer++;
//     }

//     if (shotTimer >= 5)
//     {
//         Bullet bullet = {};
//         bullet.speed = 10;
//         bullet.texture = texture;
//         bullet.y = 250;
//         bullets.push_back(bullet);
//         shotTimer = 0;
//     }

//     for (int i = 0; i < bullets.size(); i++)
//     {
//         if (!bullets[i].enemyBulletCollides())
//         {
//             bullets[i].updateEnemy();
//             DrawTexture(bullets[i].texture, 100, bullets[i].y, WHITE);
//         }
//         else
//         {
//             bullets.erase(bullets.begin() + i);
//         }
//     }
// }