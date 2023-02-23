#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include "game.h"

class Player : public Game
{
private:
    /* data */
public:
    Vector2 position;
    float speed;
    bool canShoot;
    float health;
    Texture2D planeTexture;

    Player() : Game() {};
    ~Player();

    void InitPlayer();
    void UpdatePlayer(float delta);
};

#endif