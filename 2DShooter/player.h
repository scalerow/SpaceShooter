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
    float speed;
    bool canShoot;
    float health;
    Texture2D planeTexture;

    Player();
    ~Player();

    void InitPlayer(Vector2 screenSize);
    void UpdatePlayer(float delta, Vector4 flightArea);
};

#endif