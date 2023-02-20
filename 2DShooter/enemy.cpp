#include <raylib.h>
#include "enemy.h"

Enemy::Enemy() 
{
    x = 0;
    y = 0;
    health = 100;
    isBoss = false;
    texture = {};
    speed = 0;
    active = false;
}
    

void Enemy::update() 
{
    Vector2 windowsScale = GetWindowScaleDPI();
    if(y < windowsScale.y) {
        y += speed;
    }
    else {
        active = false;
    }
}

void Enemy::isHit(int bulletDamage) {
    health -= bulletDamage ;
}