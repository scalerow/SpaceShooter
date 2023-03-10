#ifndef MAINMENU_H
#define MAINMENU_H

#include "home.h"
#include <raylib.h>
#include "gameobjects.h"

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

    MainMenu(float &width, float &height);
    ~MainMenu();
    void InitMenu();
    void PlayAction(Rectangle btnBounds);
    void SettingsAction(Rectangle btnBounds);
    void ExitAction(Rectangle btnBounds);
    void UnloadMenu();
};

#endif
