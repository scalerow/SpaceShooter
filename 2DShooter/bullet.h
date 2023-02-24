#ifndef BULLET_H
#define BULLET_H

#include <raylib.h>

class Bullet 
{
public:
    int x;
    int y;
    Texture2D texture;
    int speed;
    int damage;
    bool active;


    Bullet();
    ~Bullet();

    void updatePlayer();
    void updateEnemy();

    bool playerBulletCollides();
    bool enemyBulletCollides();
};

#endif
