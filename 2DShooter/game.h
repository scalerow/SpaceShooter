#ifndef GAME_H
#define GAME_H

#define MAX_ENEMIES 4

#include "raylib.h"
#include "player.h"

class Game
{
private:
public:
    bool menuActive;
    bool gameActive;
    int shotTimerRight;
    int shotTimerLeft;
    int enemyShotTimer;
    int enemyCounter;
    Texture2D backgroundTexture;
    Vector2 backgroudPosition;
    Game(/* args */);
    ~Game();

    void load(float screenHeight, float screenWidth);
    void InitGame(float screenWidth, float screenHeight);
    void InitMenu();
};

#endif
