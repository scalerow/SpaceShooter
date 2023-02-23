#include <raylib.h>
#include <iostream>
#include "bullet.h"
#include "enemy.h"
#include "player.h"
#include "game.h"
#include "home.h"
#include "mainmenu.h"
#include <vector>
#include "tools.h"

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
// void UpdateDefaultEnemies(vector<Enemy> &enemies, Texture2D &texture, int xPositions[4]);
//  void UpdateDefaultEnemyBullet(vector<Bullet> &bullets, Texture2D &texture, int (&enemyPositions)[4], int &shotTimer);

int main(void)
{
    Tools tools;
    static vector<Bullet> bulletsRight;
    static vector<Bullet> bulletsLeft;

    static vector<Bullet> defaultEnemyBullets;

    float screenWidth = 1920.f;
    float screenHeight = 1080.f;
    InitWindow(screenWidth, screenHeight, "DesertSpaceShooter");
    Image icon = LoadImage("../myymedia/icon.ico");
    SetWindowIcon(icon);

    Image bulletImg = LoadImage("../mymedia/bullet_0.png");
    Texture2D bulletTexture = LoadTextureFromImage(bulletImg);
    UnloadImage(bulletImg);

    Image defaultEnemyBulletImg = LoadImage("../mymedia/bullet_enemy_0.png");
    Texture2D defaultenemyBulletTexture = LoadTextureFromImage(defaultEnemyBulletImg);
    UnloadImage(defaultEnemyBulletImg);

    static vector<Enemy> defaultEnemies;
    int enemyPositions[] = {400 + 204, 400 + 408, 400 + 612, 400 + 816};
    int enemyCounter = 0;
    int enemyShotTimer = 0;
    Game game = Game(screenHeight, screenWidth);
    game.LoadMenu();
    Player player;

    SetTargetFPS(60);
    while (!game.shouldExit && !WindowShouldClose())
    {
        // Move player around
        float deltaTime = GetFrameTime();

        BeginDrawing();
        ClearBackground(BLACK);

        if (game.activateMenu)
        {
            if (!game.isMenuActive)
            {
                // Clear remenants of texture from memory
                player.UnloadPlayer();
                game.UnloadGame();

                game.InitMenu();
            }

            // Need to unload game texture
            Color interactionColor = ColorAlphaBlend(BLACK, WHITE, BLUE);

            BeginBlendMode(BLEND_ALPHA);
            DrawTexture(game.menuTexture, game.menuBackgroudPosition.x, game.menuBackgroudPosition.y, DARKGRAY);
            EndBlendMode();

            // Play button
            Rectangle rectPlay = Rectangle{(screenWidth / 2.f) - 250, screenHeight / 2.f, 500, 120};
            DrawRectangleLinesEx(rectPlay, 10, game.playButtonColor);
            DrawText("PLAY", (screenWidth / 2.f) - 125, (screenHeight / 2.f) + 15, 96, game.playButtonColor);

            // Settings button
            float settingsWidth = MeasureText("SETTINGS", 72);
            Rectangle rectSettings = Rectangle{(screenWidth / 2.f) - (settingsWidth / 2), (screenHeight / 2.f) + 300.f, settingsWidth, 72};
            Rectangle settingsHitbox = Rectangle{rectSettings.x, rectSettings.y, rectSettings.width, rectSettings.height};
            DrawText("SETTINGS", rectSettings.x, rectSettings.y, 72, game.settingsButtonColor);

            // Exit button
            float exitWidth = MeasureText("EXIT", 72);
            Rectangle rectExit = Rectangle{(screenWidth / 2.f) - (exitWidth / 2), (screenHeight / 2.f) + 400.f, exitWidth, 72};
            Rectangle exitHitbox = Rectangle{rectExit.x, rectExit.y, rectExit.width, rectExit.height};
            DrawText("EXIT", rectExit.x, rectExit.y, 72, game.exitButtonColor);

            game.SettingsAction(settingsHitbox);
            game.PlayAction(rectPlay);
            game.ExitAction(exitHitbox);
        }
        else if (game.activateGame)
        {
            if (!game.isGameActive)
            {
                game.UnloadMenu();

                game.InitGame();
                player.InitPlayer(screenHeight, screenWidth);
            }
            player.UpdatePlayer(deltaTime, game.flightArea);

            DrawTexture(game.gameTexture, game.gameBackgroudPosition.x, game.gameBackgroudPosition.y, RAYWHITE);
            DrawTexture(player.planeTexture, player.position.x, player.position.y, WHITE);

            // UpdateLeftBullet(&bulletLeft, planePlayer.position);
            UpdateLeftBullet(bulletsLeft, bulletTexture, player.position, game.shotTimerLeft);
            // UpdateRightBullet(bulletRight[i], planePlayer.position);
            UpdateRightBullet(bulletsRight, bulletTexture, player.position, game.shotTimerRight);

            tools.CreateMultipleEnemies(enemyPositions);

            for (int i = 0; i < tools.enemies.size(); i++)
            {

                Vector2 enemyPos = {tools.enemies[i].x, tools.enemies[i].y};
                Vector2 enemySize = {(float)tools.enemies[i].enemyTexture.width, (float)tools.enemies[i].enemyTexture.height};

                Rectangle enemyRect = {enemyPos.x, enemyPos.y, enemySize.x, enemySize.y};

                for (int x = 0; x < bulletsRight.size(); x++)
                {
                    Vector2 bulletRightPos = {(float)bulletsRight[x].x, (float)bulletsRight[x].y};
                    Vector2 bulletRightSize = {(float)bulletsRight[x].texture.width, (float)bulletsRight[x].texture.height};
                    Rectangle bulletRect = {bulletRightPos.x, bulletRightPos.y, bulletRightSize.x, bulletRightSize.y};
                    if (CheckCollisionRecs(enemyRect, bulletRect))
                    {
                        tools.enemies[i].health -= 10;
                        bulletsRight.erase(bulletsRight.begin() + x);
                    }
                }
            }
            // UpdateEnemies
            // UpdateDefaultEnemies(defaultEnemy, defaultEnemyTexture, enemyPositions);
        }
        else if (game.activateSettings)
        {
        }

        // Update enemy bullets
        // UpdateDefaultEnemyBullet(defaultEnemyBullets, defaultenemyBulletTexture, enemyPositions, enemyShotTimer);

        EndDrawing();
    }
    UnloadTexture(player.planeTexture);
    UnloadTexture(game.gameTexture);
    UnloadTexture(game.menuTexture);
    UnloadTexture(player.planeTexture);
    UnloadTexture(bulletTexture);

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

// void UpdateDefaultEnemies(vector<Enemy> &enemies, Texture2D &enemyTexture, int xPositions[4])
// {
//     if (IsKeyPressed(KEY_SPACE) && enemies.size() > 1)
//     {
//         enemies[0].health = 0;
//     }

//     for (int i = 0; i < 4; i++)
//     {
//         if (enemies.size() < 4)
//         {
//             Enemy defEnemy = {};
//             defEnemy.active = false;
//             defEnemy.speed = 2;
//             defEnemy.isBoss = false;
//             defEnemy.enemyTexture = enemyTexture;
//             defEnemy.x = xPositions[i];
//             defEnemy.y = -100;
//             enemies.push_back(defEnemy);
//         }

//         if (!enemies[i].active && enemies[i].health >= 0)
//             enemies[i].active = true;

//         if (enemies[i].health == 0)
//         {
//             enemies.erase(enemies.begin() + i);
//         }

//         if (enemies[i].active && enemies[i].health >= 0)
//         {
//             enemies[i].active = true;
//             if (enemies[i].y < 150)
//                 enemies[i].y += enemies[i].speed;
//             else
//                 enemies[i].hover(xPositions[i], 50);
//             DrawTexture(enemies[i].enemyTexture, enemies[i].x, enemies[i].y, WHITE);
//         }
//     }
// }

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
