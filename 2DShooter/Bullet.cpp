#include "Bullet.h"
#include <raylib.h>

Bullet::Bullet()
{
    x = 0;
    y = 0;
    speed = 0;
    texture = {};
}

void Bullet::update()
{

    y -= speed;
}

bool Bullet::collidesWidth()
{
    if (y <= 0)
    {
        return true;
    }
    else
        return false;
}