#include "bullet.h"

Bullet::Bullet()
{
    x = 0;
    y = 0;
    speed = 0;
    damage=1;
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