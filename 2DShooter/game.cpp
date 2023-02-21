#include <raylib.h>
#include "game.h"
#include "player.h"

Game::Game()
{
    menuActive;
    gameActive;
    shotTimerRight;
    shotTimerLeft;
    enemyShotTimer;
    enemyCounter;
    backgroundTexture;
    backgroudPosition;
}

Game::~Game()
{
}

void Game::load(float &screenHeight, float &screenWidth)
{
    Game game;

    if (game.gameActive)
    {
        game.InitGame(screenWidth, screenHeight);
    }
    else if (game.menuActive)
    {
        game.InitMenu();
    }
}

void Game::InitGame(float &screenWidth, float &screenHeight)
{
    Image background = LoadImage("../mymedia/2d_desert_sprite.png");
    ImageResize(&background, background.width, screenHeight);
    Texture2D backgroundTxr = LoadTextureFromImage(background);
    Vector2 backgroundPos = {(screenWidth - backgroundTxr.width) / 2, 0};
    UnloadImage(background);

    backgroundTexture = backgroundTxr;
    backgroudPosition = {backgroundPos.x, backgroundPos.y};
}

void Game::InitMenu()
{
}
