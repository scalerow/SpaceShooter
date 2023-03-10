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

#ifdef PLATFORM_WEB
#include <emscripten/emscripten.h>
#endif

using namespace std;

static Tools tools;
static float screenWidth = 1920.f;
static float screenHeight = 1080.f;
static int enemyPositions[] = {400 + 204, 400 + 408, 400 + 612, 400 + 816};
static Game game = Game(screenWidth, screenHeight);
static Player player;
static Settings settings;

static void DrawGame();

int main(void)
{

    InitWindow(screenWidth, screenHeight, "Space Shooter");

    player.InitPlayer(GetScreenHeight(), GetScreenWidth());
    game.LoadMenu();

#ifdef PLATFORM_WEB
    emscripten_set_main_loop(DrawGame, 60, 1);
#else

    SetTargetFPS(60);
    while (!game.shouldExit && !WindowShouldClose())
    {
        DrawGame();
    }
#endif
    UnloadTexture(game.gameTexture);
    UnloadTexture(game.menuTexture);
    UnloadTexture(player.playerTexture);

    CloseWindow();

    return 0;
}

void DrawGame()
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

#ifndef PLATFORM_WEB
        // Exit button
        float exitWidth = MeasureText("EXIT", 72);
        Rectangle rectExit = Rectangle{(screenWidth / 2.f) - (exitWidth / 2), (screenHeight / 2.f) + 400.f, exitWidth, 72};
        Rectangle exitHitbox = Rectangle{rectExit.x, rectExit.y, rectExit.width, rectExit.height};
        DrawText("EXIT", rectExit.x, rectExit.y, 72, game.exitButtonColor);
        game.ExitAction(exitHitbox);
#endif

        game.SettingsAction(settingsHitbox);
        game.PlayAction(rectPlay);
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
            game.RenderBackground();

            char stringPlayerHealth[15 + sizeof(char)] = "";
            sprintf(stringPlayerHealth, "%d", player.health);
            int healthStringWidth = MeasureText(stringPlayerHealth, 72);
            char stringPlayerScore[15 + sizeof(char)] = "";
            sprintf(stringPlayerScore, "Score: %d", player.score);
            DrawText(stringPlayerScore, (screenWidth - 400) - 50, 50, 72, GREEN);
            DrawRectangleLines((screenWidth - 450), 958, 400, 72, GREEN);
            DrawRectangle((screenWidth - 450), 958, (400.f/150.f) * (float)player.health, 72, GREEN);
            DrawText(stringPlayerHealth, (screenWidth - 200) - healthStringWidth,958, 72,WHITE);
            

            // DrawTexture(player.planeTexture, player.position.x, player.position.y, WHITE);
            // DrawTexture(player.planeTexture, cos((player.rotation * DEG2RAD)) * (player.planeTexture.width / 2) - sin((player.rotation * DEG2RAD)) * (player.planeTexture.width / 2), sin((player.rotation * DEG2RAD)) * (player.planeTexture.width / 2) + cos((player.rotation * DEG2RAD)) * (player.planeTexture.width / 2), WHITE);

            player.UpdateLeftBullet();
            player.UpdateRightBullet();
            player.UpdatePlayer(deltaTime, game.flightArea);
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
                if(!player.playerActive)
                {
                    player.leftBullets.clear();
                    player.rightBullets.clear();
                    tools.enemies[i].ResetDefaultEnenmy();
                    tools.enemies[i].enemyBullets.clear();
                }
            }

            for (int i = 0; i < tools.enemies.size(); i++)
            {
                if (tools.enemies[i].health > 0 && tools.enemies[i].active)
                {
                    tools.enemies[i].isHit(player.leftBullets, player.rightBullets, player.score);
                }
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
                // tools.enemies.clear();
                player.UnloadPlayer();
                game.isGameActive = false;
                game.LoadGame();
            }
            if (IsKeyPressed(KEY_BACKSPACE))
            {
                for (int i = 0; i < tools.enemies.size(); i++)
                {
                    player.leftBullets.clear();
                    player.rightBullets.clear();
                    tools.enemies[i].UnloadEnemy();
                    tools.enemies[i].ResetDefaultEnenmy();
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