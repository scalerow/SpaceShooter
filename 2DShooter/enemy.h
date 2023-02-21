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

    void hover(int position, int hoverRange);

    void isHit(int bulletDamage);

    void shoot(vector<Bullet> &bullets, int shotTimer, Texture2D &texture);

private: 
    bool leftHover;
    bool rightHover;
};


#endif