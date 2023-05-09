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

    y -= bulletSpeed * GetFrameTime();
}

void Bullet::InitSpecialAttackBullet(Vector2 pos)
{
    // Image bulletimg = LoadImage("./media/bullet_0.png");
    // Texture2D texture = LoadTextureFromImage(bulletimg);
    // UnloadImage(bulletimg);
    // bulletTexture = texture;
    // bulletSpeed = 5;
    // spRotation = 0;
    // spRadius = 20;
    // x = pos.x + 75;
    // y = pos.y - 50;
    // bulletActive = true;
    // bulletDamage = 10;
    // spActive = true;
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

bool Bullet::playerBulletOutOfScreen()
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
    frameCounter = 0;
    currentFrame = 0;
}

void Bullet::UpdateAnimatedEnemyBullet(int &frameCap)
{
    float frameWidth = frameCount != 0 ? (float)(bulletTexture.width / frameCount) : (float)bulletTexture.width; // Sprite one frame rectangle width
    float frameHeight = (float)(bulletTexture.height);

    frameCounter++;
    if (frameCounter >= frameCap)
    {
        frameCounter = 0;
        currentFrame++;
    }
    Rectangle frameRec = {x, y, frameWidth, frameHeight};
    frameRec.x = frameWidth * currentFrame;
    frameRec.y = frameHeight;
    DrawTextureRec(bulletTexture, frameRec, {x, y}, WHITE);
    y += bulletSpeed * GetFrameTime();
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
