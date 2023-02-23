#ifndef MAINMENU_H
#define MAINMENU_H

#include "home.h"
#include "raylib.h"

class MainMenu : public Home
{
private:
    /* data */
public:
    Texture2D menuTexture;
    Vector2 menuBackgroudPosition;
    Color playButtonColor;
    Color exitButtonColor;
    Color settingsButtonColor;
    bool shouldExit;
    bool isMenuActive;

    MainMenu(float height, float width);
    ~MainMenu();
    void InitMenu();
    void PlayAction(Rectangle btnBounds);
    void SettingsAction(Rectangle btnBounds);
    void ExitAction(Rectangle btnBounds);
    void UnloadMenu();
};

#endif
