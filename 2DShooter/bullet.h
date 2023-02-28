#ifndef BULLET_H
#define BULLET_H

#include <raylib.h>
#include <cmath>

class Bullet
{
public:
    float x;
    float y;
    Texture2D bulletTexture;
    float speed;
    int damage;
    bool active;
    float specialAttckPoints;
    float rotation;
    float radius;

    Bullet();
    ~Bullet();

    void InitSpecialAttack(Vector2 pos);
    void updatePlayerBullet();
    void updateEnemyBullet();
    bool playerBulletCollides();
    bool enemyBulletCollides();
    void ResetSpecialAttack(Vector2 spawnPos);
};

#endif
