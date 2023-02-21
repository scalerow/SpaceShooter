#include <raylib.h>
#include "enemy.h"
#include "bullet.h"

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

void Enemy::shoot(vector<Bullet> &bullets, int shotTimer, Texture2D &texture) 
{
    if (shotTimer < 12)
    {
        shotTimer++;
    }

    if (shotTimer >= 12)
    {
        Bullet bullet = {};
        bullet.speed = 10;
        bullet.texture = texture;
        bullet.x = x;
        bullet.y = y + 10;
        bullets.push_back(bullet);
        shotTimer = 0;
    }

    for (int i = 0; i < bullets.size(); i++)
    {
        if (!bullets[i].collidesWidth())
        {
            bullets[i].update();
            DrawTexture(bullets[i].texture, bullets[i].x, bullets[i].y, WHITE);
        }
        else
        {
            bullets.erase(bullets.begin() + i);
        }
    }
}

void Enemy::isHit(int bulletDamage) {
    health -= bulletDamage ;
}