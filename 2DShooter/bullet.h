#ifndef BULLET_H
#define BULLET_H

#include <raylib.h>
#include "player.h"
#include "enemy.h"

class Bullet : public Player, public Enemy
{
public:
    int x;
    int y;
    Texture2D texture;
    int speed;

    Bullet();
    ~Bullet();

    void updatePlayer();
    void updateEnemy();

    bool playerBulletCollides();
    bool enemyBulletCollides();
};

#endif
