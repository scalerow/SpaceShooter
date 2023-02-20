#ifndef BULLET_H
#define BULLET_H

#include <raylib.h>

class Bullet
{
public:
    int x;
    int y;
    Texture2D texture;
    int speed;

    Bullet();

    void update();

    bool collidesWidth();
};

#endif