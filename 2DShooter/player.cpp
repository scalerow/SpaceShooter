#include "player.h"
#include <raylib.h>

Player::Player()
{
    position;
    speed;
    canShoot;
    health;
    planeTexture;
}

Player::~Player()
{
}

void Player::InitPlayer(Vector2 screenSize)
{

    Image planeImg = LoadImage("../mymedia/plane_100_0.png");
    Vector2 planePosition = {screenSize.x / 2, screenSize.y - 100};
    planeTexture = LoadTextureFromImage(planeImg);
    position = planePosition;
    speed = 8.f;
    canShoot = true;
    UnloadImage(planeImg);
}

void Player::UpdatePlayer(float delta, Vector4 flightArea)
{
    if (IsKeyDown(KEY_RIGHT) && position.x <= flightArea.z - 100)
        position.x += 350.f * delta;
    if (IsKeyDown(KEY_LEFT) && position.x >= flightArea.x)
        position.x -= 350.f * delta;
    if (IsKeyDown(KEY_DOWN) && position.y <= flightArea.w - 100)
        position.y += 350.f * delta;
    if (IsKeyDown(KEY_UP) && position.y >= flightArea.y)
        position.y -= 350.f * delta;
}