#include "player.h"
#include <raylib.h>
#include <cmath>

Player::Player()
{
    shotTimer = 0;
    rotation = 0.f;
    radius = 10.f;
}

Player::~Player()
{
}

// Initialize the plane for the game
void Player::InitPlayer(float screenHeight, float screenWidth)
{

    Image planeImg = LoadImage("../mymedia/space_plane_0.png");
    Vector2 planePosition = {screenWidth / 2, screenHeight - 100};
    planeTexture = LoadTextureFromImage(planeImg);
    position = planePosition;
    rotation = 0.00;
    speed = 8.f;
    canShoot = true;
    specialAttackBulletCount = 10;
    gameOver = false;
    health = 100;
    score = 0;
    UnloadImage(planeImg);
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
        Vector2 playerSize = {(float)planeTexture.width, (float)planeTexture.height};

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

// Clear remenants of texture from memory
void Player::UnloadPlayer()
{
    UnloadTexture(planeTexture);
}