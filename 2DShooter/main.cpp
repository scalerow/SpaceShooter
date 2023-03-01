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
#include "settings.h"

using namespace std;

typedef struct PlanePlayer
{
    Vector2 position;
    float speed;
    bool canShoot;
    float health = 100.f;
    Texture2D planeTexture;
} PlanePlayer;

void UpdateLeftBullet(vector<Bullet> &bullets, Texture2D &texture, Vector2 position, float rotation, int &shotTimer);
void UpdateRightBullet(vector<Bullet> &bullets, Texture2D &texture, Vector2 position, float rotation, int &shotTimer);
void DrawGame();
// void UpdateDefaultEnemies(vector<Enemy> &enemies, Texture2D &texture, int xPositions[4]);
//  void UpdateDefaultEnemyBullet(vector<Bullet> &bullets, Texture2D &texture, int (&enemyPositions)[4], int &shotTimer);

int main(void)
{
    Tools tools;
    vector<Bullet> bulletsRight;
    vector<Bullet> bulletsLeft;

    static vector<Bullet> defaultEnemyBullets;

    float screenWidth = 1920.f;
    float screenHeight = 1080.f;
    InitWindow(screenWidth, screenHeight, "Space Shooter");
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
    Vector2 mouseposition = GetMousePosition();
    Game game = Game(screenWidth, screenHeight);
    game.LoadMenu();
    Player player;
    Settings settings;

    SetTargetFPS(60);
    while (!game.shouldExit && !WindowShouldClose())
    {
        // Move player around
        float deltaTime = GetFrameTime();

        BeginDrawing();
        ClearBackground(BLACK);

        if (!game.activateGame && !game.activateMenu && !game.activateSettings)
        {
            game.LoadMenu();
        }

        if (game.activateMenu)
        {
            if (!game.isMenuActive)
            {

                // Clear remenants of texture from memory
                player.UnloadPlayer();
                game.UnloadGame();

                game.InitMenu();
            }

            game.RenderBackground(true);
            // DrawTexture(game.menuTexture, game.menuBackgroudPosition.x, game.menuBackgroudPosition.y, DARKGRAY);

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

            if (!player.gameOver)
            {
                player.UpdatePlayer(deltaTime, game.flightArea);

                game.RenderBackground();

                char stringPlayerScore[15 + sizeof(char)] = "";
                sprintf(stringPlayerScore, "Score: %d", player.score);
                int scoreStringWidth = MeasureText(stringPlayerScore, 72);
                DrawText(stringPlayerScore, (screenWidth - scoreStringWidth) - 50, 50, 72, GREEN);
                char stringPlayerHealth[15 + sizeof(char)] = "";
                sprintf(stringPlayerHealth, "Health: %d", player.health);
                DrawText(stringPlayerHealth, 50, 50, 72, GREEN);
                // DrawTexture(player.planeTexture, player.position.x, player.position.y, WHITE);
                // DrawTexture(player.planeTexture, cos((player.rotation * DEG2RAD)) * (player.planeTexture.width / 2) - sin((player.rotation * DEG2RAD)) * (player.planeTexture.width / 2), sin((player.rotation * DEG2RAD)) * (player.planeTexture.width / 2) + cos((player.rotation * DEG2RAD)) * (player.planeTexture.width / 2), WHITE);

                // UpdateLeftBullet(&bulletLeft, planePlayer.position);
                UpdateLeftBullet(bulletsLeft, bulletTexture, player.position, player.rotation, game.shotTimerLeft);
                // UpdateRightBullet(bulletRight[i], planePlayer.position);
                UpdateRightBullet(bulletsRight, bulletTexture, player.position, player.rotation, game.shotTimerRight);

                DrawTextureV(player.planeTexture, player.position, WHITE);
                tools.CreateMultipleEnemies(enemyPositions);

                if (IsKeyDown(KEY_SPACE))
                {
                    tools.InitSpecialAttack(player.position);
                }

                if (tools.bullets.size() > 0)
                {
                    for (int i = 0; i < tools.bullets.size(); i++)
                    {
                        tools.bullets[i].UpdateSpecialAttack(player.position);
                    }
                }

                for (int i = 0; i < tools.enemies.size(); i++)
                {
                    player.isHit(tools.enemies[i].enemyBullets);
                }

                for (int i = 0; i < tools.enemies.size(); i++)
                {
                    tools.enemies[i].isHit(bulletsLeft, bulletsRight, player.score);
                }
            }
            else
            {
                game.RenderBackground(true);
                int textWidth = MeasureText("GAME OVER", 100);
                DrawText("GAME OVER", (screenWidth / 2) - (textWidth / 2), 100, 100, RED);

                char stringPlayerScore[15 + sizeof(char)] = "";
                sprintf(stringPlayerScore, "Score: %d", player.score);
                int scoreStringWidth = MeasureText(stringPlayerScore, 100);
                DrawText(stringPlayerScore, (screenWidth / 2) - (scoreStringWidth / 2), (screenHeight / 2) - 50, 100, RED);

                int subTextWidth = MeasureText("[ENTER: RESTART, BACKSPACE: EXIT TO MAIN MENU]", 48);
                DrawText("[ENTER: RESTART, BACKSPACE: EXIT TO MAIN MENU]", (screenWidth / 2) - (subTextWidth / 2), screenHeight - 100, 48, RED);
                if (IsKeyPressed(KEY_ENTER))
                {
                    for (int i = 0; i < tools.enemies.size(); i++)
                    {
                        bulletsLeft.clear();
                        bulletsRight.clear();
                        tools.enemies[i].ResetDefaultEnenmy(enemyPositions[i]);
                        tools.enemies[i].enemyBullets.clear();
                    }
                    // tools.enemies.clear();
                    player.UnloadPlayer();
                    game.isGameActive = false;
                    game.LoadGame();
                }
                if (IsKeyPressed(KEY_BACKSPACE))
                {
                    for (int i = 0; i < tools.enemies.size(); i++)
                    {
                        bulletsLeft.clear();
                        bulletsRight.clear();
                        tools.enemies[i].UnloadEnemy();
                        tools.enemies[i].ResetDefaultEnenmy(enemyPositions[i]);
                        tools.enemies[i].enemyBullets.clear();
                    }

                    tools.enemies.clear();
                    player.UnloadPlayer();
                    game.UnloadGame();
                    game.isGameActive = false;
                    game.LoadMenu();
                }
            }
        }
        else if (game.activateSettings)
        {
            if (!settings.isSettingsActive)
            {
                game.UnloadMenu();
                player.UnloadPlayer();
                game.UnloadGame();
                settings.InitSettings();
            }
            game.RenderBackground(true);
            settings.DrawSettings();

            if (settings.exitSettings)
            {
                settings.exitSettings = false;
                game.LoadMenu();
            }
        }

        // Update enemy bullets
        // UpdateDefaultEnemyBullet(defaultEnemyBullets, defaultenemyBulletTexture, enemyPositions, enemyShotTimer);

        EndDrawing();
    }
    UnloadTexture(game.gameTexture);
    UnloadTexture(game.menuTexture);
    UnloadTexture(player.planeTexture);
    UnloadTexture(bulletTexture);

    CloseWindow();

    return 0;
}

void UpdateLeftBullet(vector<Bullet> &bullets, Texture2D &texture, Vector2 position, float rotation, int &shotTimer)
{
    if (shotTimer < 15)
    {
        shotTimer++;
    }

    if (shotTimer >= 15)
    {
        Bullet bullet = {};
        bullet.bulletSpeed = 7.f;
        bullet.bulletTexture = texture;
        bullet.x = position.x + 0.5;
        bullet.y = position.y;
        bullet.bulletActive = true;
        bullets.push_back(bullet);
        shotTimer = 0;
    }

    for (int i = 0; i < bullets.size(); i++)
    {
        if (!bullets[i].playerBulletCollides())
        {
            bullets[i].updatePlayerBullet();
            DrawTextureV(bullets[i].bulletTexture, {bullets[i].x, bullets[i].y}, WHITE);
        }
        else
        {
            bullets.erase(bullets.begin() + i);
        }
    }
}

void UpdateRightBullet(vector<Bullet> &bullets, Texture2D &texture, Vector2 position, float rotation, int &shotTimer)
{
    if (shotTimer < 15)
    {
        shotTimer++;
    }

    if (shotTimer >= 15)
    {
        Bullet bullet = {};
        bullet.bulletSpeed = 7;
        bullet.bulletTexture = texture;
        bullet.x = position.x + 149.5;
        bullet.y = position.y;
        bullet.bulletActive = true;
        bullets.push_back(bullet);
        shotTimer = 0;
    }

    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets[i].bulletActive)
        {
            bullets[i].updatePlayerBullet();
            DrawTextureV(bullets[i].bulletTexture, {bullets[i].x, bullets[i].y}, WHITE);
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

void DrawGame()
{
}