#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include "game.h"

class Player
{
private:
    /* data */
public:
    Vector2 position;
    int rotation;
    float speed;
    bool canShoot;
    float health;
    Texture2D planeTexture;

    Player();
    ~Player();

    void InitPlayer(float screenHeight, float screenWidth);
    void UpdatePlayer(float delta, Vector4 flightArea);
    void UnloadPlayer();
};

#endif