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
float screenWidth = 1280.f;
float screenHeight = 760.f;
#else
float screenWidth = 1920.f;
float screenHeight = 1080.f;
#endif

using namespace std;

static Tools tools;
static Vector2 maxResolution = {3840.f, 2160.f};
static float resolutionNormalizer = 100.f;
static vector<int> enemyPositions;
static Game game = Game(screenWidth, screenHeight);
static Player player;
static HighScore highscores;
static Settings settings;
static Level_01 level1;
static Level_02 level2;

static void DrawGame();

int main(void)
{

    InitWindow(screenWidth, screenHeight, "Space Shooter");

    enemyPositions.push_back(CalculateObjectSizeX(400.f + 204.f));
    enemyPositions.push_back(CalculateObjectSizeX(400.f + 408.f));
    enemyPositions.push_back(CalculateObjectSizeX(400.f + 612.f));
    enemyPositions.push_back(CalculateObjectSizeX(400.f + 816.f));
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
            tools.UnloadMultipleEnemies();
            player.UnloadPlayer();

            game.UnloadGame();

            game.InitMenu();
        }
        if (IsWindowResized())
        {
            screenHeight = GetScreenHeight();
            screenWidth = GetScreenWidth();
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
            settings.saveSettings("config.xml", highscores.highScores, game.playerData);
            game.InitGame();
            player.InitPlayer(screenHeight, screenWidth, game.activePlayer);
        }

        if (IsWindowResized())
        {
            screenHeight = GetScreenHeight();
            screenWidth = GetScreenWidth();
            game.InitGame();
            player.InitPlayer(screenHeight, screenWidth, game.activePlayer);
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
                player.UpdatePlayer(deltaTime, game.flightArea);
                player.UpdateLeftBullet();
                player.UpdateRightBullet();
                player.EnemiesAttackingAction(level1.enemies);
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
                DrawText("Playerdata error - no level found", CalculateXCoord(100 / 2), CalculateYCoord(100 / 2), CalculateObjectSizeY(120), RED);
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
                player.UnloadPlayer();
                game.isGameActive = false;
                game.LoadGame();
            }
            if (IsKeyPressed(KEY_ESCAPE))
            {
                tools.UnloadMultipleEnemies();
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