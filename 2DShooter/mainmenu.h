#ifndef MAINMENU_H
#define MAINMENU_H

#include "home.h"
#include "raylib.h"

class MainMenu :  public Home
{
private:
    /* data */
public:
    Texture2D backgroundTexture;
    Vector2 backgroudPosition;
    Color playButtonColor;
    bool active;

    MainMenu() : Home(){};
    ~MainMenu();
    void InitMenu();
    void PlayAction(Vector2 mousePoint, Rectangle btnBounds);

};

#endif