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
    int currentFrame;
    int frameCounter;

    Bullet();
    ~Bullet();

    // Player related

    void InitSpecialAttackBullet(Vector2 pos);
    void UpdateSpecialAttack(Vector2 playerPos);
    void ResetSpecialAttack(Vector2 spawnPos);
    void updatePlayerBullet();
    bool playerBulletOutOfScreen();

    // Enemy related

    void InitEnemyBullet(int positionX, Texture2D &btxtr);
    void updateEnemyBullet();
    void UpdateAnimatedEnemyBullet(int &framesCount, int &frameCap);
    bool enemyBulletCollides();

    void UnloadBullet();
};

#endif
