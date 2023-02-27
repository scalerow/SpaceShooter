#ifndef BULLET_H
#define BULLET_H

#include <raylib.h>
#include <cmath>

class Bullet
{
public:
    float x;
    float y;
    Texture2D texture;
    float speed;
    int damage;
    bool active;
    float specialAttckPoints;
    float rotation;

    Bullet();
    ~Bullet();

    void specialAttack(float rotation, float radius);
    void updatePlayerBullet();
    void updateEnemyBullet();
    bool playerBulletCollides();
    bool enemyBulletCollides();
};

#endif
