#include "bullet.h"

Bullet::Bullet()
{
    x = 0;
    y = 0;
    bulletSpeed = 0;
    bulletDamage = 5;
}

Bullet::~Bullet()
{
}

// Player related

void Bullet::updatePlayerBullet()
{

    y -= bulletSpeed;
}

void Bullet::InitSpecialAttackBullet(Vector2 pos)
{
    Image bulletimg = LoadImage("./media/bullet_0.png");
    Texture2D texture = LoadTextureFromImage(bulletimg);
    UnloadImage(bulletimg);
    bulletTexture = texture;
    bulletSpeed = 5;
    spRotation = 0;
    spRadius = 20;
    x = pos.x + 75;
    y = pos.y - 50;
    bulletActive = true;
    bulletDamage = 10;
    spActive = true;
    // x +=  cos(rotation * DEG2RAD) * radius;
    // y +=  sin(rotation * DEG2RAD) * radius;
}

void Bullet::UpdateSpecialAttack(Vector2 playerPos)
{

    int bulletRotation = 270 + spRotation;
    spRotation += 20;
    x += cos(spRotation * DEG2RAD) * spRadius;
    y -= sin(spRotation * DEG2RAD) * spRadius;
    // DrawTexture(bullets[x].texture, bullets[x].x, bullets[x].y, WHITE);
    DrawTextureEx(bulletTexture, {x, y}, bulletRotation, 1, RAYWHITE);

    if (y < 0)
        ResetSpecialAttack(playerPos);
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

void Bullet::ResetSpecialAttack(Vector2 spawnPos)
{
    spRotation = 0;
    spRadius = 10;
    x = spawnPos.x;
    y = spawnPos.y;
    bulletActive = true;
    bulletDamage = 10;
    spActive = false;
}

// Enemy related

void Bullet::InitEnemyBullet(int positionX, Texture2D &bTxtr)
{
    bulletSpeed = 5.f;
    bulletTexture = bTxtr;
    x = positionX;
    y = 250;
    bulletDamage = 10;
    bulletActive = true;
}

void Bullet::updateEnemyBullet()
{

    y += bulletSpeed;
}

bool Bullet::enemyBulletCollides()
{
    if (y >= GetScreenHeight())
    {
        return true;
    }
    else
        return false;
}

void Bullet::UnloadBullet()
{
    UnloadTexture(bulletTexture);
}
