#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include "game.h"
#include "bullet.h"
#include "vector"

class Player
{
private:
    /* data */
public:
    Vector2 position;
    float rotation;
    float radius;
    float speed;
    bool canShoot;
    float health;
    Texture2D planeTexture;
    int specialAttackBulletCount;
    int shotTimer;

    Player();
    ~Player();

    void InitPlayer(float screenHeight, float screenWidth);
    void UpdatePlayer(float delta, Vector4 flightArea);
    void FireSpecialAttack();
    void Fire();
    void UnloadPlayer();
};

#endif