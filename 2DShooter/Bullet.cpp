#include "Bullet.h"
#include <raylib.h>

Bullet::Bullet()
{
    x = 0;
    y = 0;
    speed = 0;
    texture = {};
}

void Bullet::updatePlayer()
{

    y -= speed;
}

void Bullet::updateEnemy()
{

    y += speed;
}

bool Bullet::playerBulletCollides()
{
    if (y <= 0)
    {
        return true;
    }
    else
        return false;
}

bool Bullet::enemyBulletCollides()
{
    if (y <= 0)
    {
        return true;
    }
    else
        return false;
}