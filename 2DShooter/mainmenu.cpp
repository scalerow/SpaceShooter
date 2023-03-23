#include "mainmenu.h"

MainMenu::MainMenu(float &width, float &height) : Home{width, height}
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
    Image background = LoadImage("./media/space_background_menu.png");
    ImageResize(&background, CalculateObjectSizeX(background.width), CalculateObjectSizeY(background.height));
    Texture2D backgroundTxr = LoadTextureFromImage(background);

    Vector2 backgroundPos = {0, 0};
    UnloadImage(background);

    playButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    exitButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    menuTexture = backgroundTxr;
    menuBackgroudPosition = {backgroundPos.x, backgroundPos.y};
}

void MainMenu::DrawMainMenu()
{
    // Play button
        Rectangle startButtonPos = {CalculateXCoord((100 / 2.f) - 13.f), CalculateYCoord(100 / 2.f), CalculateObjectSizeX(500), CalculateObjectSizeY(120)};
        DrawRectangleLinesEx(startButtonPos, 10, playButtonColor);
        Vector2 startButtonTextPos = {50.f - 6.5f, 50.f + 1.3f};
        DrawText("PLAY", CalculateXCoord(startButtonTextPos.x), CalculateYCoord(startButtonTextPos.y), CalculateObjectSizeY(96.f), playButtonColor);
        PlayAction(startButtonPos);
        // Settings button
        float settingsWidth = MeasureText("SETTINGS", CalculateObjectSizeY(72));
        Rectangle rectSettings = Rectangle{(screenWidth / 2.f) - (settingsWidth / 2), (screenHeight / 2.f) + CalculateYCoord(27.77f), settingsWidth, CalculateObjectSizeY(72.f)};
        Rectangle settingsHitbox = Rectangle{rectSettings.x, rectSettings.y, rectSettings.width, rectSettings.height};
        DrawText("SETTINGS", rectSettings.x, rectSettings.y, CalculateObjectSizeY(72), settingsButtonColor);
        SettingsAction(settingsHitbox);
#ifndef PLATFORM_WEB
        // Exit button
        float exitWidth = MeasureText("EXIT", CalculateObjectSizeY(72));
        Rectangle rectExit = Rectangle{(screenWidth / 2.f) - (exitWidth / 2), (screenHeight / 2.f) + CalculateYCoord(37.03f), exitWidth, CalculateObjectSizeY(72)};
        Rectangle exitHitbox = Rectangle{rectExit.x, rectExit.y, rectExit.width, rectExit.height};
        DrawText("EXIT", rectExit.x, rectExit.y, CalculateObjectSizeY(72), exitButtonColor);
        ExitAction(exitHitbox);
#endif
}

// Initialize the playbutton and its actions
void MainMenu::PlayAction(Rectangle btnBounds)
{
    mousePoint = GetMousePosition();

    // Check button state
    if (CheckCollisionPointRec(mousePoint, btnBounds))
    {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
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
     mousePoint = GetMousePosition();

    // Check button state
    if (CheckCollisionPointRec(mousePoint, btnBounds))
    {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            settingsButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
            isMenuActive = false;
            LoadSettings();
        }
        else
        {
            settingsButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        }
    }
    else
    {
        settingsButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    }
}

void MainMenu::ExitAction(Rectangle btnBounds)
{
    mousePoint = GetMousePosition();
    // Check button state
    if (CheckCollisionPointRec(mousePoint, btnBounds))
    {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
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