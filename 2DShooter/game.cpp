#include <raylib.h>
#include "game.h"
#include "player.h"

Game::Game()
{
    Home();
    shotTimerRight = 0;
    shotTimerLeft = 0;
    enemyShotTimer = 0;
    enemyCounter = 0;
}

Game::~Game()
{
}



void Game::InitGame()
{
    active = true;

    Image background = LoadImage("../mymedia/2d_desert_sprite.png");
    ImageResize(&background, background.width, screenHeight);
    Texture2D backgroundTxr = LoadTextureFromImage(background);
    Vector2 backgroundPos = {(screenWidth - backgroundTxr.width) / 2, 0};
    UnloadImage(background);

    backgroudPosition = {(screenWidth - backgroundTxr.width) / 2,0};
    flightArea= {backgroudPosition.x,backgroudPosition.y,backgroudPosition.x + backgroundTxr.width,screenHeight};
    backgroundTexture = backgroundTxr;
    backgroudPosition = {backgroundPos.x, backgroundPos.y};
}




