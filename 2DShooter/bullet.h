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

    // Player related

    void InitSpecialAttackBullet(Vector2 pos);
    void UpdateSpecialAttack(Vector2 playerPos);
    void ResetSpecialAttack(Vector2 spawnPos);
    void updatePlayerBullet();
    bool playerBulletCollides();

    // Enemy related

    void InitEnemyBullet(int positionX, Texture2D &btxtr);
    void updateEnemyBullet();
    bool enemyBulletCollides();
};

#endif
