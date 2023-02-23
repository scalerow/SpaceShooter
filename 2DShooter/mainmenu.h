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
    bool isMenuActive;

    MainMenu(float height, float width);
    ~MainMenu();
    void InitMenu();
    void PlayAction(Vector2 mousePoint, Rectangle btnBounds);
};

#endif