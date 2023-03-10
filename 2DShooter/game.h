#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "mainmenu.h"
#include "player.h"

class Game : public MainMenu
{
private:
public:
    int shotTimerRight;
    int shotTimerLeft;
    int enemyShotTimer;
    int enemyCounter;
    Texture2D gameTexture;
    Vector2 gameBackgroudPosition;
    Vector4 flightArea;
    bool isGameActive;

    Game(float &widthP, float &heightP);
    virtual ~Game();

    void InitGame();
    void RenderBackground(bool menu = false);
    void UnloadGame();
};

#endif
