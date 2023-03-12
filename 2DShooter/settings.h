#ifndef SETTINGS_H
#define SETTINGS_H

#include <raylib.h>
#include "gameobjects.h"

class Settings
{
private:
    bool fullscreen;
    bool soundActive;
    Sound gameSound;
    Color fullscreenButtonColor;
    Color soundButtonColor;
    Color backButtonColor;

public:
    bool isSettingsActive;
    bool exitSettings;

    Settings();
    ~Settings();

    void InitSettings();

    void toggleSound(Rectangle bounds);
    void toggleFullscreen(Rectangle bounds);
    void fullscreen_enter();
    void fullscreen_exit();
    bool is_fullscreen();

    void DrawSettings();

    void BackToMenu(Rectangle bounds);
};

#endif