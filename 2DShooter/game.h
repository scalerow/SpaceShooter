#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "MainMenu.h"

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

    Game(float heightP, float widthP);
    virtual ~Game();

    void InitGame();
};

#endif
