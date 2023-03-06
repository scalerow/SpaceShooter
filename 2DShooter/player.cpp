#include "player.h"
#include <raylib.h>
#include <cmath>

Player::Player()
{
}

Player::~Player()
{
}

// Initialize the plane for the game
void Player::InitPlayer(float screenHeight, float screenWidth)
{

    Image planeImg = LoadImage("./media/space_plane_0.png");
    Vector2 planePosition = {screenWidth / 2, screenHeight - 100};

    Image bulletImg = LoadImage("./media/bullet_0.png");
    Texture2D bulletTexture = LoadTextureFromImage(bulletImg);

    playerBulletTexture = LoadTextureFromImage(bulletImg);
    playerTexture = LoadTextureFromImage(planeImg);
    position = planePosition;
    rotation = 0.00;
    speed = 8.f;
    specialAttackBulletCount = 10;
    gameOver = false;
    leftShotTimer = 0;
    rightShotTimer = 0;
    health = 150;
    score = 0;
    UnloadImage(planeImg);
    UnloadImage(bulletImg);
}

// Update the planes position with keyboard keys
void Player::UpdatePlayer(float delta, Vector4 flightArea)
{
    // if (IsKeyDown(KEY_LEFT))
    // {
    //     rotation -= 4.f;
    // }
    // if (IsKeyDown(KEY_RIGHT))
    // {
    //     rotation += 4.f;
    // }

    if (IsKeyDown(KEY_RIGHT) && position.x <= flightArea.z - 100)
    {
        position.x += 350.f * delta;
    }
    if (IsKeyDown(KEY_LEFT) && position.x >= flightArea.x)
    {
        position.x -= 350.f * delta;
    }
    if (IsKeyDown(KEY_DOWN) && position.y <= flightArea.w - 100)
    {
        // position.y -= 10 * sin((rotation + 270) * DEG2RAD);
        // position.x -= 10 * cos((rotation + 270) * DEG2RAD);
        position.y += 350.f * delta;
    }

    if (IsKeyDown(KEY_UP) && position.y >= flightArea.y)
    {
        // position.y += 10 * sin((rotation + 270) * DEG2RAD);
        // position.x += 10 * cos((rotation + 270) * DEG2RAD);
        position.y -= 350.f * delta;
    }
}

void Player::isHit(std::vector<Bullet> &bullets)
{
    if (bullets.size() > 0)
    {
        Vector2 playerPos = {(float)position.x, (float)position.y};
        Vector2 playerSize = {(float)playerTexture.width, (float)playerTexture.height};

        Rectangle playerRect = {playerPos.x, playerPos.y - 75, playerSize.x, playerSize.y};
        for (int x = 0; x < bullets.size(); x++)
        {
            Vector2 bulletPos = {(float)bullets[x].x, (float)bullets[x].y};
            Vector2 bulletSize = {(float)bullets[x].bulletTexture.width, (float)bullets[x].bulletTexture.height};
            Rectangle bulletRect = {bulletPos.x, bulletPos.y, bulletSize.x, bulletSize.y};
            if (CheckCollisionRecs(playerRect, bulletRect))
            {

                health -= bullets[x].bulletDamage;
                bullets[x].bulletActive = false;
                bullets.erase(bullets.begin() + x);
                if (health <= 0)
                    gameOver = true;
            }
        }
    }
}

void Player::UpdateLeftBullet()
{
    if (leftShotTimer < 15)
    {
        leftShotTimer++;
    }
    if (leftShotTimer >= 15)
    {
        Bullet bullet = {};
        bullet.bulletSpeed = 7.f;
        bullet.bulletTexture = playerBulletTexture;
        bullet.x = position.x + 0.5;
        bullet.y = position.y;
        bullet.bulletActive = true;
        leftBullets.push_back(bullet);
        leftShotTimer = 0;
    }

    for (int i = 0; i < leftBullets.size(); i++)
    {
        if (!leftBullets[i].playerBulletCollides())
        {
            leftBullets[i].updatePlayerBullet();
            DrawTextureV(leftBullets[i].bulletTexture, {leftBullets[i].x, leftBullets[i].y}, WHITE);
        }
        else
        {
            leftBullets.erase(leftBullets.begin() + i);
        }
    }
}

void Player::UpdateRightBullet()
{
    if (rightShotTimer < 15)
    {
        rightShotTimer++;
    }
    if (rightShotTimer >= 15)
    {
        Bullet bullet = {};
        bullet.bulletSpeed = 7.f;
        bullet.bulletTexture = playerBulletTexture;
        bullet.x = position.x + 149.5;
        bullet.y = position.y;
        bullet.bulletActive = true;
        rightBullets.push_back(bullet);
        rightShotTimer = 0;
    }

    for (int i = 0; i < rightBullets.size(); i++)
    {
        if (rightBullets[i].bulletActive)
        {
            rightBullets[i].updatePlayerBullet();
            DrawTextureV(rightBullets[i].bulletTexture, {rightBullets[i].x, rightBullets[i].y}, WHITE);
        }
        else
        {
            rightBullets.erase(rightBullets.begin() + i);
        }
    }
}

// Clear remenants of texture from memory
void Player::UnloadPlayer()
{
    UnloadTexture(playerTexture);
    UnloadTexture(playerBulletTexture);
}