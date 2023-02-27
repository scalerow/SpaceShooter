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

    Image planeImg = LoadImage("../mymedia/plane_100_0.png");
    Vector2 planePosition = {screenWidth / 2, screenHeight - 100};
    planeTexture = LoadTextureFromImage(planeImg);
    position = planePosition;
    speed = 8.f;
    canShoot = true;
    UnloadImage(planeImg);
}

// Update the planes position with keyboard keys
void Player::UpdatePlayer(float delta, Vector4 flightArea)
{
    if(IsKeyDown(KEY_A))
        rotation += 5;
    if (IsKeyDown(KEY_RIGHT) && position.x <= flightArea.z - 100)
        position.x += 350.f * delta;
    if (IsKeyDown(KEY_LEFT) && position.x >= flightArea.x)
        position.x -= 350.f * delta;
    if (IsKeyDown(KEY_DOWN) && position.y <= flightArea.w - 100)
        position.y += 350.f * delta;
    if (IsKeyDown(KEY_UP) && position.y >= flightArea.y)
    {
        position.y += 10 * sin(rotation * DEG2RAD);
        position.x += 10 * cos(rotation * DEG2RAD);
        //position.y -= 350.f * delta;
    }
        
}

// Clear remenants of texture from memory
void Player::UnloadPlayer()
{
    UnloadTexture(planeTexture);
}