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

void Bullet::InitSpecialAttack(Vector2 pos)
{
    Image bulletimg = LoadImage("../mymedia/bullet_0.png");
    Texture2D texture = LoadTextureFromImage(bulletimg);
    UnloadImage(bulletimg);
    bulletTexture = texture;
    speed = 5;
    rotation = 0;
    radius = 10;
    x = pos.x;
    y = pos.y;
    active = true;
    damage = 10;
    // x +=  cos(rotation * DEG2RAD) * radius;
    // y +=  sin(rotation * DEG2RAD) * radius;
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

void Bullet::ResetSpecialAttack(Vector2 spawnPos)
{
    rotation = 0;
    radius = 10;
    x = spawnPos.x;
    y = spawnPos.y;
    active = true;
    damage = 10;
}