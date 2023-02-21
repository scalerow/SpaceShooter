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
    leftHover=false,
    rightHover=true;
}
    

void Enemy::update() 
{
        y += speed;
 
}

void Enemy::hover(int position, int hoverRange) 
{
    int range[] = {position - hoverRange, position + hoverRange};
    
    if(leftHover && x > range[0]) 
    {
        x-=speed;
        
        if(x == range[0]) {
            rightHover = true;
            leftHover=false;
        }
    }
    
    if(rightHover && x <= range[1])
    {
        x+=speed;

        if(x == range[1]) {
            rightHover = false;
            leftHover=true;
        }
    }
 
}

void Enemy::isHit(int bulletDamage) {
    health -= bulletDamage ;
}