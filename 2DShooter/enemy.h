#ifndef ENEMY_H
#define ENEMY_H

#include <raylib.h>

class Enemy
{
public:
    int x;
    int y;
    int health;
    bool active;
    int speed;
    bool isBoss;
    Texture2D texture;
    
    Enemy();

    void update();

    void isHit(int bulletDamage);
};


#endif