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

void DrawGame();

int main(void)
{
    //Tools tools;

    float screenWidth = 1920.f;
    float screenHeight = 1080.f;
    InitWindow(screenWidth, screenHeight, "Space Shooter");

    int enemyPositions[] = {400 + 204, 400 + 408, 400 + 612, 400 + 816};
    Vector3 planepos = {0.f,0.f, 270.f};
    // Game game = Game(screenWidth, screenHeight);
    // game.LoadMenu();
    Player player;
    Settings settings;

    player.InitPlayer(screenHeight, screenWidth);

    // TEST CAMERA MODE
    Camera3D cam = {0};
    cam.position = {20.0f, 20.0f, 20.0f};
    cam.target = {0.0f, 8.0f,0.0f };
    cam.fovy = 45.f;
    cam.up = { 0.0f, 1.6f, 0.0f }; 
    cam.projection = CAMERA_ORTHOGRAPHIC;

    Camera2D camera = {0};
    camera.offset = {screenWidth/2, screenHeight/2};
    camera.target = {0.f, 8.f};
    camera.rotation = 0.f;
    camera.zoom = 1.f;
     Model plane = LoadModel("../mymedia/model.gltf");
     Model universe = LoadModel("../mymedia/universe.obj");

    BoundingBox bounds = GetMeshBoundingBox(plane.meshes[0]);

    // END TEST CAMERA MODE
    
    //player.InitPlayer(screenHeight, screenWidth);
    //game.InitGame();
    SetTargetFPS(60);
    // while (!game.shouldExit && !WindowShouldClose())
    while (!WindowShouldClose())
    { 
      //  float deltaTime = GetFrameTime();

        if (IsKeyDown(KEY_LEFT))
        {
            planepos.x -= 10;
            camera.offset.x -= 10;
        }
        if (IsKeyDown(KEY_RIGHT))
        {
            planepos.x += 10;
            camera.offset.x += 10;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            planepos.y += 10;
            camera.offset.y += 10;
        }
        if (IsKeyDown(KEY_UP))
        {
            planepos.y -= 10;
            camera.offset.y -= 10;
        }

        camera.target = {planepos.x, planepos.y};
        

        if (IsKeyDown(KEY_A))
            camera.rotation--;
        else if (IsKeyDown(KEY_S))
            camera.rotation++;
        camera.zoom += ((float)GetMouseWheelMove() * 1.f);
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode2D(camera);
        //DrawCircleV({planepos.x, planepos.y}, 100, RED);
       DrawTexture(player.playerTexture, planepos.x, planepos.y, WHITE );

         //DrawModelEx(plane, planepos,{0.f, 0.f,0.f},0, {1.f,1.f,1.f},WHITE );
         //DrawModel(universe, {900.f, 500.f, 0.f},0, BLACK);
        
        EndMode2D();
        // BeginMode3D(cam);
        // DrawSphere({-10.f, -10.f, 0.f}, 50.f, BLUE);
        // DrawModel(plane, {0.f, 0.f, 0.f}, 1.f, WHITE);
        // EndMode3D();
        EndDrawing();

        // Move player around
        

        // BeginDrawing();
        // ClearBackground(BLACK);

        // if (!game.activateGame && !game.activateMenu && !game.activateSettings)
        // {
        //     game.LoadMenu();
        // }

        // if (game.activateMenu)
        // {
        //     if (!game.isMenuActive)
        //     {

        //         // Clear remenants of texture from memory
        //         player.UnloadPlayer();
        //         game.UnloadGame();

        //         game.InitMenu();
        //     }

        //     game.RenderBackground(true);
        //     // DrawTexture(game.menuTexture, game.menuBackgroudPosition.x, game.menuBackgroudPosition.y, DARKGRAY);

        //     // Play button
        //     Rectangle rectPlay = Rectangle{(screenWidth / 2.f) - 250, screenHeight / 2.f, 500, 120};
        //     DrawRectangleLinesEx(rectPlay, 10, game.playButtonColor);
        //     DrawText("PLAY", (screenWidth / 2.f) - 125, (screenHeight / 2.f) + 15, 96, game.playButtonColor);

        //     // Settings button
        //     float settingsWidth = MeasureText("SETTINGS", 72);
        //     Rectangle rectSettings = Rectangle{(screenWidth / 2.f) - (settingsWidth / 2), (screenHeight / 2.f) + 300.f, settingsWidth, 72};
        //     Rectangle settingsHitbox = Rectangle{rectSettings.x, rectSettings.y, rectSettings.width, rectSettings.height};
        //     DrawText("SETTINGS", rectSettings.x, rectSettings.y, 72, game.settingsButtonColor);

        //     // Exit button
        //     float exitWidth = MeasureText("EXIT", 72);
        //     Rectangle rectExit = Rectangle{(screenWidth / 2.f) - (exitWidth / 2), (screenHeight / 2.f) + 400.f, exitWidth, 72};
        //     Rectangle exitHitbox = Rectangle{rectExit.x, rectExit.y, rectExit.width, rectExit.height};
        //     DrawText("EXIT", rectExit.x, rectExit.y, 72, game.exitButtonColor);

        //     game.SettingsAction(settingsHitbox);
        //     game.PlayAction(rectPlay);
        //     game.ExitAction(exitHitbox);
        // }
        // else if (game.activateGame)
        // {
        //     if (!game.isGameActive)
        //     {
        //         game.UnloadMenu();

        //         game.InitGame();
        //         player.InitPlayer(screenHeight, screenWidth);
        //     }

        //     if (!player.gameOver)
        //     {
        //         player.UpdatePlayer(deltaTime, game.flightArea);

        //         game.RenderBackground();

        //         char stringPlayerScore[15 + sizeof(char)] = "";
        //         sprintf(stringPlayerScore, "Score: %d", player.score);
        //         int scoreStringWidth = MeasureText(stringPlayerScore, 72);
        //         DrawText(stringPlayerScore, (screenWidth - scoreStringWidth) - 50, 50, 72, GREEN);
        //         char stringPlayerHealth[15 + sizeof(char)] = "";
        //         sprintf(stringPlayerHealth, "Health: %d", player.health);
        //         DrawText(stringPlayerHealth, 50, 50, 72, GREEN);
        //         // DrawTexture(player.planeTexture, player.position.x, player.position.y, WHITE);
        //         // DrawTexture(player.planeTexture, cos((player.rotation * DEG2RAD)) * (player.planeTexture.width / 2) - sin((player.rotation * DEG2RAD)) * (player.planeTexture.width / 2), sin((player.rotation * DEG2RAD)) * (player.planeTexture.width / 2) + cos((player.rotation * DEG2RAD)) * (player.planeTexture.width / 2), WHITE);

        //         player.UpdateLeftBullet();
        //         player.UpdateRightBullet();

        //         DrawTextureV(player.playerTexture, player.position, WHITE);
        //         tools.CreateMultipleEnemies(enemyPositions);

        //         if (IsKeyDown(KEY_SPACE))
        //         {
        //             tools.InitSpecialAttack(player.position);
        //         }

        //         if (tools.bullets.size() > 0)
        //         {
        //             for (int i = 0; i < tools.bullets.size(); i++)
        //             {
        //                 tools.bullets[i].UpdateSpecialAttack(player.position);
        //             }
        //         }

        //         for (int i = 0; i < tools.enemies.size(); i++)
        //         {
        //             player.isHit(tools.enemies[i].enemyBullets);
        //         }

        //         for (int i = 0; i < tools.enemies.size(); i++)
        //         {
        //             tools.enemies[i].isHit(player.leftBullets, player.rightBullets, player.score);
        //         }
        //     }
        //     else
        //     {
        //         game.RenderBackground(true);
        //         int textWidth = MeasureText("GAME OVER", 100);
        //         DrawText("GAME OVER", (screenWidth / 2) - (textWidth / 2), 100, 100, RED);

        //         char stringPlayerScore[15 + sizeof(char)] = "";
        //         sprintf(stringPlayerScore, "Score: %d", player.score);
        //         int scoreStringWidth = MeasureText(stringPlayerScore, 100);
        //         DrawText(stringPlayerScore, (screenWidth / 2) - (scoreStringWidth / 2), (screenHeight / 2) - 50, 100, RED);

        //         int subTextWidth = MeasureText("[ENTER: RESTART, BACKSPACE: EXIT TO MAIN MENU]", 48);
        //         DrawText("[ENTER: RESTART, BACKSPACE: EXIT TO MAIN MENU]", (screenWidth / 2) - (subTextWidth / 2), screenHeight - 100, 48, RED);
        //         if (IsKeyPressed(KEY_ENTER))
        //         {
        //             for (int i = 0; i < tools.enemies.size(); i++)
        //             {
        //                 player.leftBullets.clear();
        //                 player.rightBullets.clear();
        //                 tools.enemies[i].ResetDefaultEnenmy(enemyPositions[i]);
        //                 tools.enemies[i].enemyBullets.clear();
        //             }
        //             // tools.enemies.clear();
        //             player.UnloadPlayer();
        //             game.isGameActive = false;
        //             game.LoadGame();
        //         }
        //         if (IsKeyPressed(KEY_BACKSPACE))
        //         {
        //             for (int i = 0; i < tools.enemies.size(); i++)
        //             {
        //                 player.leftBullets.clear();
        //                 player.rightBullets.clear();
        //                 tools.enemies[i].UnloadEnemy();
        //                 tools.enemies[i].ResetDefaultEnenmy(enemyPositions[i]);
        //                 tools.enemies[i].enemyBullets.clear();
        //             }

        //             tools.enemies.clear();
        //             player.UnloadPlayer();
        //             game.UnloadGame();
        //             game.isGameActive = false;
        //             game.LoadMenu();
        //         }
        //     }
        // }
        // else if (game.activateSettings)
        // {
        //     if (!settings.isSettingsActive)
        //     {
        //         game.UnloadMenu();
        //         player.UnloadPlayer();
        //         game.UnloadGame();
        //         settings.InitSettings();
        //     }
        //     game.RenderBackground(true);
        //     settings.DrawSettings();

        //     if (settings.exitSettings)
        //     {
        //         settings.exitSettings = false;
        //         game.LoadMenu();
        //     }
        // }

        // // Update enemy bullets
        // // UpdateDefaultEnemyBullet(defaultEnemyBullets, defaultenemyBulletTexture, enemyPositions, enemyShotTimer);

        // EndDrawing();
    }
    // UnloadTexture(game.gameTexture);
    // UnloadTexture(game.menuTexture);
    // UnloadTexture(player.playerTexture);

    CloseWindow();

    return 0;
}

void DrawGame()
{
}
