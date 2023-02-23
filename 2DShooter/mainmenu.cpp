#include "mainmenu.h"
#include "raylib.h"

MainMenu::MainMenu(float height, float width) : Home{height, width}
{
    isMenuActive = false;
}

MainMenu::~MainMenu()
{
}

void MainMenu::InitMenu()
{
    isMenuActive = true;
    Image background = LoadImage("../mymedia/2d_desert_sprite.png");
    ImageResize(&background, background.width, screenHeight);
    Texture2D backgroundTxr = LoadTextureFromImage(background);

    Vector2 backgroundPos = {(screenWidth - backgroundTxr.width) / 2, 0};
    UnloadImage(background);

    menuTexture = backgroundTxr;
    menuBackgroudPosition = {backgroundPos.x, backgroundPos.y};
}

void MainMenu::PlayAction(Vector2 mousePoint, Rectangle btnBounds)
{
    mousePoint = GetMousePosition();
    // Check button state
    if (CheckCollisionPointRec(mousePoint, btnBounds))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            playButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        else
        {
            playButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            isMenuActive = false;
            LoadGame();
        }
    }
}