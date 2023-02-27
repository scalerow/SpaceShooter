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

    Image planeImg = LoadImage("../mymedia/space_plane_0.png");
    Vector2 planePosition = {screenWidth / 2, screenHeight - 100};
    planeTexture = LoadTextureFromImage(planeImg);
    position = planePosition;
    rotation = 0.00;
    speed = 8.f;
    canShoot = true;
    specialAttackBulletCount = 10;

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
    if (IsKeyPressed(KEY_SPACE))
    {
        FireSpecialAttack();
    }

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

void Player::Fire()
{
}

void Player::FireSpecialAttack()
{
    Image img = LoadImage("../mymedia/bullet_0.png");
    Texture2D texture = LoadTextureFromImage(img);
    UnloadImage(img);

    int bulletCounter = 0;
    int rangeCurrent = 0;
    int rangeEnd = 500;

    std::vector<Bullet> bullets;
    for (int i = 0; i < rangeEnd; i++)
    {
        bulletCounter++;

        if (rangeCurrent != rangeEnd)
            rangeCurrent++;

        if (bullets.size() <= 10)
        {
            for (int x = 0; x <= 10; x++)
            {
                Bullet bullet;
                bullet.texture = texture;
                bullet.active = true;
                bullet.damage = 10;
                bullet.x = position.x + 75;
                bullet.y = position.y - 50;
                bullets.push_back(bullet);
            }
        }
        if (rangeCurrent == 488)
        {
            int l = 1;
        }
        bullets[bulletCounter].specialAttack(36.f, rangeCurrent);
        DrawTexture(bullets[bulletCounter].texture, bullets[bulletCounter].x, bullets[bulletCounter].y, WHITE);
        if (bulletCounter <= 10)
            bulletCounter = 0;

        // cos((rotation * DEG2RAD)) * 50 - sin((rotation * DEG2RAD) * 10) * bullets[bulletCounter].y, sin((rotation * DEG2RAD) * 10) * bullets[bulletCounter].x + cos((rotation * DEG2RAD) * 10) * bullets[bulletCounter].y
    }
}

// Clear remenants of texture from memory
void Player::UnloadPlayer()
{
    UnloadTexture(planeTexture);
}