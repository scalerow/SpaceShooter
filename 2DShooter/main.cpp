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
#include "gameobjects.h"
#include "components.h"
#include <string>
#include ".\levels\level_01.h"
#include ".\levels\level_02.h"

#ifdef PLATFORM_WEB
#include <emscripten/emscripten.h>
float initScreenWidth = 1280.f;
float initScreenHeight = 768.f;
#else
float initScreenWidth = 1280.f;
float initScreenHeight = 768.f;
#endif

using namespace std;

static Tools tools;
static Vector2 maxResolution = {3840.f, 2160.f};
static float resolutionNormalizer = 100.f;
static vector<int> enemyPositions;
static Game game = Game(initScreenWidth, initScreenHeight);
static Player player;
static HighScore highscores;
static Settings settings;
static Level_01 level1;
static Level_02 level2;
static void DrawGame();

int main(void)
{
    InitWindow(initScreenWidth, initScreenHeight, "Space Shooter");
    GameObjects::SetScreenSize(initScreenWidth, initScreenHeight);
    enemyPositions.push_back(GameObjects::CalculateObjectSizeX(400.f + 204.f));
    enemyPositions.push_back(GameObjects::CalculateObjectSizeX(400.f + 408.f));
    enemyPositions.push_back(GameObjects::CalculateObjectSizeX(400.f + 612.f));
    enemyPositions.push_back(GameObjects::CalculateObjectSizeX(400.f + 816.f));
    game.LoadMenu();

#ifdef PLATFORM_WEB
    emscripten_set_main_loop(DrawGame, 60, 1);
#else
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetWindowMinSize(480, 272);
    settings.loadSettings("config.xml", highscores.highScores, game.playerData);
    settings.InitGameSettings();

    SetTargetFPS(60);
    while (!game.shouldExit)
    {
        DrawGame();
    }
#endif
    UnloadTexture(game.gameTexture);
    UnloadTexture(game.menuTexture);
    UnloadTexture(player.playerTexture);
    level1.UnloadLevel1();

    CloseWindow();

    return 0;
}

void DrawGame()
{
    // Move player around
    float deltaTime = GetFrameTime();

    BeginDrawing();
    ClearBackground(BLACK);

    if (!game.activateGame && !game.activateMenu && !game.activateSettings && !game.activateLoadGame && !game.activateNewGame)
    {
        game.LoadMenu();
    }

    //////////////////////////////////
    ///           MENU             ///
    //////////////////////////////////
    if (game.activateMenu)
    {
        if (!game.isMenuActive)
        {

            // Clear remenants of texture from memory
            game.UnloadMenu();
            player.UnloadPlayer();
            game.UnloadGame();
            level1.UnloadLevel1();
            level1.UnloadMultipleEnemies();

            game.InitMenu();
        }
        if (IsWindowResized())
        {
            initScreenHeight = GetScreenHeight();
            initScreenWidth = GetScreenWidth();
            game.InitMenu();
        }

        game.RenderBackground(true);
        game.DrawMainMenu();
    }
    else if (game.activateLoadGame)
    {
        if (!game.isLoadSelectGameActive)
        {
            game.InitLoadSelectedGame();
        }

        if (IsWindowResized())
        {
            initScreenHeight = GetScreenHeight();
            initScreenWidth = GetScreenWidth();
            game.InitLoadSelectedGame();
        }

        game.RenderBackground(true);
        game.LoadSelectGameActions();
        game.DrawLoadSelectGameMenu();
    }
    else if (game.activateNewGame)
    {
        if (!game.isNewGameActive)
        {
            game.InitNewGame();
        }

        if (IsWindowResized())
        {
            initScreenHeight = GetScreenHeight();
            initScreenWidth = GetScreenWidth();
            game.InitNewGame();
        }

        game.NewPlayerName();
        game.NewGameActions();
        game.RenderBackground(true);
        game.DrawNewGameMenu();
    }
    //////////////////////////////////
    ///           GAME             ///
    //////////////////////////////////
    else if (game.activateGame)
    {
        if (!game.isGameActive)
        {
            game.UnloadMenu();
            highscores.highscoreUpdated = false;
#ifndef PLATFORM_WEB
            settings.saveSettings("config.xml", highscores.highScores, game.playerData);
#endif
            game.InitGame();
            player.InitPlayer(initScreenHeight, initScreenWidth, game.activePlayer);
        }

        if (IsWindowResized())
        {
            initScreenHeight = GetScreenHeight();
            initScreenWidth = GetScreenWidth();
            game.InitGame();
            player.InitPlayer(initScreenHeight, initScreenWidth, game.activePlayer);
        }
        //////////////////////////////////
        ///       GAME IS ACTIVE       ///
        //////////////////////////////////
        if (!player.gameOver && !game.paused)
        {

            // DrawTexture(player.planeTexture, player.position.x, player.position.y, WHITE);
            // DrawTexture(player.planeTexture, cos((player.rotation * DEG2RAD)) * (player.planeTexture.width / 2) - sin((player.rotation * DEG2RAD)) * (player.planeTexture.width / 2), sin((player.rotation * DEG2RAD)) * (player.planeTexture.width / 2) + cos((player.rotation * DEG2RAD)) * (player.planeTexture.width / 2), WHITE);
            switch (player.currentLevel)
            {
            case 1:
            {
                game.RenderBackground();
                level1.DrawMultipleEnemies(enemyPositions, player);
                level1.RandomEnemySpawn();
                level1.DrawRandomEnemies(player);
                level1.UpdateRandomEnemies();
                player.UpdatePlayer(deltaTime, game.flightArea);
                player.UpdateLeftBullet();
                player.UpdateRightBullet();
                player.EnemiesAttackingAction(level1.defaultEnemies);
                if (level1.randomEnemies.size() > 0)
                {
                    player.EnemiesAttackingAction(level1.randomEnemies);
                }

                if (IsKeyReleased(KEY_K))
                {
                    player.currentLevel = 2;
                }
                break;
            }
            case 2:
            {
                if (!level2.levelActive)
                {
                    level2.InitLevel2();
                }

                level2.RenderBackground();
                player.UpdatePlayer(deltaTime, game.flightArea);
                player.UpdateLeftBullet();
                player.UpdateRightBullet();
                break;
            }
            default:
            {
                DrawText("Playerdata error - no level found", GameObjects::CalculateXCoord(100 / 2), GameObjects::CalculateYCoord(100 / 2), GameObjects::CalculateObjectSizeY(120), RED);
                break;
            }
            }

            if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_P))
            {
                game.PauseGame();
            }

            game.DrawGameUI(player.health, game.activePlayer.health, player.score);
        }
        //////////////////////////////////
        ///          GAME OVER         ///
        //////////////////////////////////
        else if (player.gameOver)
        {
            game.DrawGameOver(highscores, settings, player.score);

            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
            {
                // tools.enemies.clear();
                level1.UnloadLevel1();
                level1.UnloadMultipleEnemies();
                player.UnloadPlayer();
                game.isGameActive = false;
                game.LoadGame();
            }
            if (IsKeyPressed(KEY_ESCAPE))
            {
                level1.UnloadLevel1();
                level1.UnloadMultipleEnemies();
                player.UnloadPlayer();
                game.UnloadGame();
                game.isGameActive = false;
                game.LoadMenu();
            }
        }
        //////////////////////////////////
        ///           PAUSE            ///
        //////////////////////////////////
        else if (game.paused)
        {
            game.DrawPauseGame();
            game.UpdatePauseGame();
        }
    }
    //////////////////////////////////
    ///         SETTINGS           ///
    //////////////////////////////////
    else if (game.activateSettings)
    {
        if (!settings.isSettingsActive)
        {
            game.UnloadMenu();
            player.UnloadPlayer();
            game.UnloadGame();
            level1.UnloadLevel1();
            level1.UnloadMultipleEnemies();
            settings.InitSettings();
        }

        // if (IsWindowResized())
        // {
        //     screenHeight = GetScreenHeight();
        //     screenWidth = GetScreenWidth();
        //     game.screenHeight = screenHeight;
        //     game.screenWidth = screenWidth;
        //     settings.InitSettings();
        // }

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