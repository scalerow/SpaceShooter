#include <raylib.h>
#include "game.h"

Game::Game(float &widthP, float &heightP) : MainMenu{widthP, heightP}
{
    shotTimerRight = 0;
    shotTimerLeft = 0;
    enemyShotTimer = 0;
    enemyCounter = 0;
    isGameActive = false;
}

Game::~Game()
{
}

// Initialize the game
void Game::InitGame()
{
    isGameActive = true;

    Image background = LoadImage("./media/space_background.png");
    ImageResize(&background, CalculateObjectSizeX(background.width), CalculateObjectSizeY(background.height));
    Texture2D backgroundTxr = LoadTextureFromImage(background);
    gameBackgroudPosition = {0, 0};
    UnloadImage(background);

    flightArea = {gameBackgroudPosition.x, gameBackgroudPosition.y, screenWidth, screenHeight};
    gameTexture = backgroundTxr;
}

void Game::RenderBackground(bool menu)
{
    if (!menu)
    {
        DrawTexture(gameTexture, gameBackgroudPosition.x, gameBackgroudPosition.y, RAYWHITE);
    }
    else
    {
        BeginBlendMode(BLEND_ALPHA);
        DrawTexture(menuTexture, menuBackgroudPosition.x, menuBackgroudPosition.y, DARKGRAY);
        EndBlendMode();
    }
}

// Clear remenants of texture from memory
void Game::UnloadGame()
{
    UnloadTexture(gameTexture);
}