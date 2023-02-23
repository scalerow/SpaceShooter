#ifndef GAME_H
#define GAME_H

#define MAX_ENEMIES 4

#include "raylib.h"
#include "player.h"
#include "home.h"

class Game : public Home
{
private:
public:
    
    int shotTimerRight;
    int shotTimerLeft;
    int enemyShotTimer;
    int enemyCounter;
    Texture2D backgroundTexture;
    Vector2 backgroudPosition;
    Vector4 flightArea;
    bool active;

    Game() : Home() {};
    ~Game();

    void InitGame();
};

#endif
