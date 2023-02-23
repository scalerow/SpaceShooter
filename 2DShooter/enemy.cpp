#include <raylib.h>
#include "enemy.h"

Enemy::Enemy()
{
    health = 100;
    isBoss = false;
    active = false;
    leftHover = false,
    rightHover = true;
}

Enemy::~Enemy() {}

void Enemy::update()
{
    y += speed;
}

void Enemy::hover(int position, int hoverRange)
{
    int range[] = {position - hoverRange, position + hoverRange};

    if (leftHover && x > range[0])
    {
        x -= speed;

        if (x == range[0])
        {
            rightHover = true;
            leftHover = false;
        }
    }

    if (rightHover && x <= range[1])
    {
        x += speed;

        if (x == range[1])
        {
            rightHover = false;
            leftHover = true;
        }
    }
}

// Initialize the plane for the game
void Enemy::InitEnemy()
{

    Image defaultEnemyImg = LoadImage("../mymedia/default_enemy_0.png");
    enemyTexture = LoadTextureFromImage(defaultEnemyImg);
    speed = 2.f;
    UnloadImage(defaultEnemyImg);
}

// Update the planes position with keyboard keys
void CreateDefaultEnemies(int xPositions[4])
{
}

// Clear remenants of texture from memory
void Enemy::UnloadEnemy()
{
    UnloadTexture(enemyTexture);
}

void Enemy::isHit(Rectangle enemyBndBox, Rectangle bulletBndBox)
{
    CheckCollisionRecs(enemyBndBox, bulletBndBox);
}