#include "bullet.h"

Bullet::Bullet()
{
    x = 0;
    y = 0;
    speed = 0;
    damage = 5;
}

Bullet::~Bullet()
{
}

void Bullet::updatePlayerBullet()
{

    y -= speed;
}

void Bullet::updateEnemyBullet()
{

    y += speed;
}

void Bullet::specialAttack(float rotation, float radius)
{
    x = cos(rotation * DEG2RAD) * x - sin(rotation * DEG2RAD) * y;
    y = sin(rotation * DEG2RAD) * x + cos(rotation * DEG2RAD) * y;
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