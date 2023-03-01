#include "settings.h"

Settings::Settings()
{
    fullscreen = false;
    soundActive = false;
    InitSettings();
}

Settings::~Settings()
{
}

void Settings::InitSettings()
{
    isSettingsActive = true;
    fullscreen = fullscreen;
    soundActive = soundActive;
    exitSettings = false;
    soundButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    fullscreenButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    backButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
}

void Settings::toggleSound(Rectangle bounds)
{
    Rectangle updatedBnds = {bounds.x, bounds.y, bounds.width, bounds.height};
    Vector2 mousePoint = GetMousePosition();
    // Check button state
    if (CheckCollisionPointRec(mousePoint, updatedBnds))
    {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            soundButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);

            soundActive = IsSoundPlaying(gameSound);
            if (!soundActive)
            {
                gameSound = LoadSound("../");
                PlaySound(gameSound);
                soundActive = IsSoundPlaying(gameSound);
            }
            else if (soundActive)
            {
                StopSound(gameSound);
                UnloadSound(gameSound);
                soundActive = IsSoundPlaying(gameSound);
            }
        }
        else
        {
            soundButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        }
    }
    else
    {
        soundButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    }
}

void Settings::toggleFullscreen(Rectangle bounds)
{
    Rectangle updatedBnds = {bounds.x, bounds.y, bounds.width, bounds.height};
    Vector2 mousePoint = GetMousePosition();
    // Check button state
    if (CheckCollisionPointRec(mousePoint, updatedBnds))
    {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            fullscreenButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
            ToggleFullscreen();
            fullscreen = IsWindowFullscreen();
        }

        else
        {
            fullscreenButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        }
    }
    else
    {
        fullscreenButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    }
}

void Settings::DrawSettings()
{
    float screenHeight = GetScreenHeight();
    float screenWidth = GetScreenWidth();

    // Fullscreen

    int fullscreenStringWidth = MeasureText("FULLSCREEN", 48);
    Rectangle fullscreenButtonRect = {(screenWidth / 2) + (fullscreenStringWidth / 2) + 50, (screenHeight / 2) - 200, 48, 48};

    DrawText("FULLSCREEN", (screenWidth / 2) - (fullscreenStringWidth / 2), (screenHeight / 2) - 200, 48, GREEN);
    if (fullscreen)
    {
        DrawRectangle(fullscreenButtonRect.x, fullscreenButtonRect.y, fullscreenButtonRect.width, fullscreenButtonRect.height, GREEN);
    }
    else if (!fullscreen)
    {
        DrawRectangleLines(fullscreenButtonRect.x, fullscreenButtonRect.y, fullscreenButtonRect.width, fullscreenButtonRect.height, fullscreenButtonColor);
    }

    // Sound
    Rectangle soundButtonRect = {(screenWidth / 2) + (fullscreenStringWidth / 2) + 50, (screenHeight / 2) - 100, 48, 48};
    DrawText("SOUND", (screenWidth / 2) - (fullscreenStringWidth / 2), (screenHeight / 2) - 100, 48, GREEN);

    if (soundActive)
    {
        DrawRectangle(soundButtonRect.x, soundButtonRect.y, soundButtonRect.width, soundButtonRect.height, soundButtonColor);
    }
    else if (!soundActive)
    {
        DrawRectangleLines(soundButtonRect.x, soundButtonRect.y, soundButtonRect.width, soundButtonRect.height, soundButtonColor);
    }

    // Exit
    float backStringWidth = MeasureText("BACK", 72);
    Rectangle backButtonRect = {(screenWidth / 2) - (backStringWidth / 2), screenHeight - 100, backStringWidth, 72};
    DrawText("BACK", backButtonRect.x, backButtonRect.y, backButtonRect.height, backButtonColor);

    toggleSound(soundButtonRect);
    toggleFullscreen(fullscreenButtonRect);
    BackToMenu(backButtonRect);
}

void Settings::BackToMenu(Rectangle bounds)
{
    Rectangle updatedBnds = {bounds.x, bounds.y, bounds.width, bounds.height};
    Vector2 mousePoint = GetMousePosition();
    // Check button state
    if (CheckCollisionPointRec(mousePoint, updatedBnds))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            backButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        else
        {
            backButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            exitSettings = true;
        }
    }
    else
    {
        backButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    }
}