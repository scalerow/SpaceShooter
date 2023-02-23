#include "mainmenu.h"
#include "raylib.h"

MainMenu::MainMenu(float height, float width) : Home{height, width}
{
    isMenuActive = false;
    shouldExit = false;
}

MainMenu::~MainMenu()
{
}

// Initialize mainmenu
void MainMenu::InitMenu()
{
    isMenuActive = true;
    Image background = LoadImage("../mymedia/2d_desert_sprite.png");
    ImageResize(&background, background.width, screenHeight);
    Texture2D backgroundTxr = LoadTextureFromImage(background);

    Vector2 backgroundPos = {(screenWidth - backgroundTxr.width) / 2, 0};
    UnloadImage(background);

    playButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    exitButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    menuTexture = backgroundTxr;
    menuBackgroudPosition = {backgroundPos.x, backgroundPos.y};
}

// Initialize the playbutton and its actions
void MainMenu::PlayAction(Rectangle btnBounds)
{
    Vector2 mousePoint = GetMousePosition();
    // Check button state
    if (CheckCollisionPointRec(mousePoint, btnBounds))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            playButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        else
        {
            playButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            isMenuActive = false;
            LoadGame();
        }
    }
    else
    {
        playButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    }
}

void MainMenu::SettingsAction(Rectangle btnBounds)
{
    Vector2 mousePoint = GetMousePosition();
    // Check button state
    if (CheckCollisionPointRec(mousePoint, btnBounds))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            settingsButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        else
        {
            settingsButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            settingsButtonColor = ColorAlphaBlend(BLACK, WHITE, RED);
        }
    }
    else
    {
        settingsButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    }
}

void MainMenu::ExitAction(Rectangle btnBounds)
{
    Vector2 mousePoint = GetMousePosition();
    // Check button state
    if (CheckCollisionPointRec(mousePoint, btnBounds))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            exitButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        else
        {
            exitButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            shouldExit = true;
        }
    }
    else
    {
        exitButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    }
}

// Clear remenants of texture from memory
void MainMenu::UnloadMenu()
{
    UnloadTexture(menuTexture);
}