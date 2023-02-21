#include <raylib.h>
#include "game.h"
#include "player.h"

Game::Game()
{
    menuActive = false;
    gameActive = false;
    shotTimerRight = 0;
    shotTimerLeft = 0;
    enemyShotTimer = 0;
    enemyCounter = 0;
    playButtonColor = ColorAlphaBlend(BLACK, WHITE, BLUE);
}

Game::~Game()
{
}

void Game::load(float screenHeight, float screenWidth)
{
    if (gameActive)
    {
        InitGame(screenWidth, screenHeight);
    }
    else if (menuActive)
    {
        InitMenu(screenWidth, screenHeight);
    }
}

void Game::InitGame(float screenWidth, float screenHeight)
{
    Image background = LoadImage("../mymedia/2d_desert_sprite.png");
    ImageResize(&background, background.width, screenHeight);
    Texture2D backgroundTxr = LoadTextureFromImage(background);
    Vector2 backgroundPos = {(screenWidth - backgroundTxr.width) / 2, 0};
    UnloadImage(background);

    backgroundTexture = backgroundTxr;
    backgroudPosition = {backgroundPos.x, backgroundPos.y};
}

void Game::InitMenu(float screenWidth, float screenHeight)
{
    Image background = LoadImage("../mymedia/2d_desert_sprite.png");
    ImageResize(&background, background.width, screenHeight);
    Texture2D backgroundTxr = LoadTextureFromImage(background);
    
    Vector2 backgroundPos = {(screenWidth - backgroundTxr.width) / 2, 0};
    UnloadImage(background);

    backgroundTexture = backgroundTxr;
    backgroudPosition = {backgroundPos.x, backgroundPos.y};

}

void Game::PlayAction(Vector2 mousePoint, Rectangle btnBounds)
{
     mousePoint = GetMousePosition();

    // Check button state
    if (CheckCollisionPointRec(mousePoint, btnBounds))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) playButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN); 
        else {playButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);}

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) 
        {
            menuActive = false;
            gameActive = true;
        }
    }
}
