#include <raylib.h>
#include "game.h"

Game::Game(float heightP, float widthP) : MainMenu{heightP, widthP}
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

    Image background = LoadImage("../mymedia/2d_desert_sprite.png");
    ImageResize(&background, background.width, screenHeight);
    Texture2D backgroundTxr = LoadTextureFromImage(background);
    Vector2 backgroundPos = {(screenWidth - backgroundTxr.width) / 2, 0};
    UnloadImage(background);

    flightArea = {backgroundPos.x, backgroundPos.y, backgroundPos.x + backgroundTxr.width, screenHeight};
    gameTexture = backgroundTxr;
    gameBackgroudPosition = {backgroundPos.x, backgroundPos.y};
}

// Clear remenants of texture from memory
void Game::UnloadGame()
{
    UnloadTexture(gameTexture);
}