#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include <raylib.h>
#include "bullet.h"
#include <random>
#include "gameobjects.h"

class Enemy
{
public:
    int health;
    bool active;
    int speed;
    bool isBoss;
    int scoreValue;
    int frameCount = 0;
    int frameCounter = 0;
    int currentFrame = 0;
    int defaultShotTimer;
    int spawnPosition;
    int defaultEnemyHoverRange;
    Texture2D enemyTexture = {0, 0, 0, 0};
    bool textureLoaded;
    Vector2 position;
    Vector2 outOufMap;
    std::vector<Bullet> enemyBullets;
    std::vector<GameObjects::Debris> enemyDebris;

    Enemy();
    ~Enemy();
    void update();

    void hover(int enemyPos);

    void EnemyExplosion(float explosionArea, float debrisSize);
    void FillDebris(int particleAmount);

    void InitBoss(float posX, int health, int speed);

    void InitDefaultEnemyDefaults(int pos, Texture2D &texture);
    Texture2D LoadEnemyTexture();
    void UpdateEnemyDefaultAttack(int posX, Texture2D &btxtr);
    void UpdateEnemyAttack(int posX, int posY, Texture2D &btxtr, int shotTimer, int frameCount, int frameCap);
    void ResetDefaultEnenmy();

    void isTriangleHit(std::vector<Bullet> &leftBullets, std::vector<Bullet> &rightBullets, int &playerScore);
    void isCircleHit(std::vector<Bullet> &leftBullets, std::vector<Bullet> &rightBullets, int &playerScore);
    void UnloadEnemy();

private:
    bool leftHover;
    bool rightHover;
};

#endif