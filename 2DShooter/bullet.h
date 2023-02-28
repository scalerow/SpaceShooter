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
    float bulletSpeed;
    int bulletDamage;
    bool bulletActive;
    bool spActive;
    float spRotation;
    float spRadius;

    Bullet();
    ~Bullet();

    void InitSpecialAttackBullet(Vector2 pos);
    void UpdateSpecialAttack(Vector2 playerPos);
    void updatePlayerBullet();
    void updateEnemyBullet();
    bool playerBulletCollides();
    bool enemyBulletCollides();
    void ResetSpecialAttack(Vector2 spawnPos);
};

#endif
