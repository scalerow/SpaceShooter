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
vector<int> enemyPositions;
static Game game = Game(screenWidth, screenHeight);
static Player player;
static HighScore highscores;
static Settings settings;

static void DrawGame();

int main(void)
{

    InitWindow(screenWidth, screenHeight, "Space Shooter");
#ifdef PLATFORM_DESKTOP
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetWindowMinSize(480, 272);
#endif
    settings.loadSettings("config.xml", highscores.highScores);

    enemyPositions.push_back(CalculateObjectSizeX(400.f + 204.f));
    enemyPositions.push_back(CalculateObjectSizeX(400.f + 408.f));
    enemyPositions.push_back(CalculateObjectSizeX(400.f + 612.f));
    enemyPositions.push_back(CalculateObjectSizeX(400.f + 816.f));
    game.LoadMenu();

#ifdef PLATFORM_WEB
    emscripten_set_main_loop(DrawGame, 60, 1);
#else
    settings.LoadGameSettings();
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
        // if (IsWindowResized())
        // {
        //     screenHeight = GetScreenHeight();
        //     screenWidth = GetScreenWidth();
        //     game.InitMenu();
        // }

        game.RenderBackground(true);
        // DrawTexture(game.menuTexture, game.menuBackgroudPosition.x, game.menuBackgroudPosition.y, DARKGRAY);

        // Play button
        Rectangle startButtonPos = {CalculateXCoord((resolutionNormalizer / 2.f) - 13.f), CalculateYCoord(resolutionNormalizer / 2.f), CalculateObjectSizeX(500), CalculateObjectSizeY(120)};
        DrawRectangleLinesEx(startButtonPos, 10, game.playButtonColor);
        Vector2 startButtonTextPos = {50.f - 6.5f, 50.f + 1.3f};
        DrawText("PLAY", CalculateXCoord(startButtonTextPos.x), CalculateYCoord(startButtonTextPos.y), CalculateObjectSizeY(96.f), game.playButtonColor);

        // Settings button
        float settingsWidth = MeasureText("SETTINGS", CalculateObjectSizeY(72));
        Rectangle rectSettings = Rectangle{(screenWidth / 2.f) - (settingsWidth / 2), (screenHeight / 2.f) + CalculateYCoord(27.77f), settingsWidth, CalculateObjectSizeY(72.f)};
        Rectangle settingsHitbox = Rectangle{rectSettings.x, rectSettings.y, rectSettings.width, rectSettings.height};
        DrawText("SETTINGS", rectSettings.x, rectSettings.y, CalculateObjectSizeY(72), game.settingsButtonColor);

#ifndef PLATFORM_WEB
        // Exit button
        float exitWidth = MeasureText("EXIT", CalculateObjectSizeY(72));
        Rectangle rectExit = Rectangle{(screenWidth / 2.f) - (exitWidth / 2), (screenHeight / 2.f) + CalculateYCoord(37.03f), exitWidth, CalculateObjectSizeY(72)};
        Rectangle exitHitbox = Rectangle{rectExit.x, rectExit.y, rectExit.width, rectExit.height};
        DrawText("EXIT", rectExit.x, rectExit.y, CalculateObjectSizeY(72), game.exitButtonColor);
        game.ExitAction(exitHitbox);
#endif
        game.SettingsAction(settingsHitbox);
        game.PlayAction(startButtonPos);
    }
    else if (game.activateGame)
    {
        if (!game.isGameActive)
        {
            game.UnloadMenu();
            highscores.highscoreUpdated = false;
            game.InitGame();
            player.InitPlayer(screenHeight, screenWidth);
        }

        // if (IsWindowResized())
        // {
        //     screenHeight = GetScreenHeight();
        //     screenWidth = GetScreenWidth();
        //     game.InitGame();
        //     player.InitPlayer(screenHeight, screenWidth);
        // }

        if (!player.gameOver)
        {
            game.RenderBackground();

            // DrawTexture(player.planeTexture, player.position.x, player.position.y, WHITE);
            // DrawTexture(player.planeTexture, cos((player.rotation * DEG2RAD)) * (player.planeTexture.width / 2) - sin((player.rotation * DEG2RAD)) * (player.planeTexture.width / 2), sin((player.rotation * DEG2RAD)) * (player.planeTexture.width / 2) + cos((player.rotation * DEG2RAD)) * (player.planeTexture.width / 2), WHITE);

            player.UpdateLeftBullet();
            player.UpdateRightBullet();
            tools.CreateMultipleEnemies(enemyPositions);
            player.UpdatePlayer(deltaTime, game.flightArea);

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
                if (!player.playerActive)
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

            char stringPlayerHealth[15 + sizeof(char)] = "";
            sprintf(stringPlayerHealth, "%d", player.health);
            int healthStringWidth = MeasureText(stringPlayerHealth, CalculateObjectSizeY(72));
            char stringPlayerScore[15 + sizeof(char)] = "";
            sprintf(stringPlayerScore, "Score: %d", player.score);
            DrawText(stringPlayerScore, CalculateXCoord(resolutionNormalizer - 23.4375f), CalculateYCoord(4.63f), CalculateObjectSizeY(72.f), GREEN);

            // Healthbar
            DrawRectangleLines(CalculateXCoord(resolutionNormalizer - 23.4375f), CalculateYCoord(88.7f), CalculateObjectSizeX(400.f), CalculateObjectSizeY(72.f), GREEN);
            // Healtbar filler
            DrawRectangle(CalculateXCoord(resolutionNormalizer - 23.4375f), CalculateYCoord(88.7f), CalculateObjectSizeX((400.f / 150.f) * (float)player.health), CalculateObjectSizeY(72.f), GREEN);
            // Health plain text
            DrawText(stringPlayerHealth, CalculateXCoord(resolutionNormalizer - 10.416f) - healthStringWidth, CalculateYCoord(88.7f), CalculateObjectSizeY(72.f), WHITE);
        }
        else
        {
            game.RenderBackground(true);
            int textWidth = MeasureText("GAME OVER", CalculateObjectSizeY(120.f));
            DrawText("GAME OVER", CalculateXCoord(resolutionNormalizer / 2) - (textWidth / 2), CalculateYCoord(9.26f), CalculateObjectSizeY(120.f), RED);

            if (!highscores.highscoreUpdated)
            {
                highscores.UpdateHighscores(player.score);
                settings.saveSettings("config.xml", highscores.highScores);
            }

            Color highscoreAchievedTextColor = highscores.newHighscoreEntry ? Color({110, 20, 143, 255}) : RED;

            char stringPlayerScore[15 + sizeof(char)] = "";
            sprintf(stringPlayerScore, "Score: %d", player.score);
            int scoreStringWidth = MeasureText(stringPlayerScore, CalculateObjectSizeY(100));
            DrawText(stringPlayerScore, CalculateXCoord(resolutionNormalizer / 2) - (scoreStringWidth / 2), CalculateYCoord(resolutionNormalizer / 2) - CalculateYCoord(18.56f), CalculateObjectSizeY(100.f), highscoreAchievedTextColor);

            int highscoreLabelWidth = MeasureText("Highscores", CalculateObjectSizeY(72.f));
            DrawText("Highscores", CalculateXCoord(resolutionNormalizer / 2) - (highscoreLabelWidth / 2), CalculateYCoord(resolutionNormalizer / 2) - CalculateYCoord(4.26f), CalculateObjectSizeY(72.f), RED);
            DrawLineEx({CalculateXCoord(resolutionNormalizer / 2) - (highscoreLabelWidth / 2) - CalculateObjectSizeX(75.f), CalculateYCoord(resolutionNormalizer / 2) + CalculateYCoord(3.f)}, {CalculateXCoord(resolutionNormalizer / 2) + (highscoreLabelWidth / 2) + CalculateObjectSizeX(75.f), CalculateYCoord(resolutionNormalizer / 2) + CalculateYCoord(3.f)}, 8.f, RED);

            int highscoresPosition = CalculateYCoord(resolutionNormalizer / 2) + CalculateYCoord(3.f);
            for (int i = 0; i < highscores.highScores.size(); i++)
            {
                highscoresPosition += CalculateYCoord(7.08f);

                char score[15 + sizeof(char)] = "";
                sprintf(score, "%d", highscores.highScores[i]);
                char scorePos[5 + sizeof(char)] = "";
                sprintf(scorePos, "%d.", i + 1);
                int scoreStringWidth = MeasureText(score, CalculateObjectSizeY(48.f));
                int scorePosStringWidth = MeasureText(score, CalculateObjectSizeY(48.f));
                if (highscores.highScores[i] == player.score)
                {
                    DrawText(score, CalculateXCoord(resolutionNormalizer / 2) + (highscoreLabelWidth / 2) + CalculateObjectSizeX(75.f) - (scoreStringWidth), highscoresPosition - CalculateObjectSizeY(48), CalculateObjectSizeY(48), highscoreAchievedTextColor);
                    DrawText(scorePos, CalculateXCoord(resolutionNormalizer / 2) - (highscoreLabelWidth / 2) - CalculateObjectSizeX(75.f), highscoresPosition - CalculateObjectSizeY(48), CalculateObjectSizeY(48), highscoreAchievedTextColor);
                }
                else
                {
                    DrawText(score, CalculateXCoord(resolutionNormalizer / 2) + (highscoreLabelWidth / 2) + CalculateObjectSizeX(75.f) - (scoreStringWidth), highscoresPosition - CalculateObjectSizeY(48), CalculateObjectSizeY(48), RED);
                    DrawText(scorePos, CalculateXCoord(resolutionNormalizer / 2) - (highscoreLabelWidth / 2) - CalculateObjectSizeX(75.f), highscoresPosition - CalculateObjectSizeY(48), CalculateObjectSizeY(48), RED);
                }
            }

            int subTextWidth = MeasureText("[ENTER OR SPACE: RESTART, ESC: MAIN MENU]", CalculateObjectSizeY(36.f));
            DrawText("[ENTER OR SPACE: RESTART, ESC: MAIN MENU]", (screenWidth / 2) - (subTextWidth / 2), CalculateYCoord(resolutionNormalizer - 4.63f), CalculateObjectSizeY(36.f), RED);
            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
            {
                // tools.enemies.clear();
                player.UnloadPlayer();
                game.isGameActive = false;
                game.LoadGame();
            }
            if (IsKeyPressed(KEY_ESCAPE))
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