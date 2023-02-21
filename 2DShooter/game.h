#ifndef GAME_H
#define GAME_H

#define MAX_ENEMIES 4

#include "raylib.h"
#include "player.h"

class Game
{
private:
public:
    bool menuActive = !gameActive;
    bool gameActive = !menuActive;
    int shotTimerRight = 0;
    int shotTimerLeft = 0;
    int enemyShotTimer = 0;
    int enemyCounter = 0;
    Texture2D backgroundTexture;
    Vector2 backgroudPosition;
    Game(/* args */);
    ~Game();

    void load(float &screenHeight, float &screenWidth);
    void InitGame(float &screenWidth, float &screenHeight);
    void InitMenu();
};

#endif
