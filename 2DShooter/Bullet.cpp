#include "bullet.h"
#include <raylib.h>

Bullet::Bullet()
{
    x = 0;
    y = 0;
    speed = 0;
    texture = {};
}

Bullet::~Bullet() {}

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
    if (y >= 1080)
    {
        return true;
    }
    else
        return false;
}