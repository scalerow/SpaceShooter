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
    int x;
    int y;
    int health;
    bool active;
    int speed;
    bool isBoss;
    int defaultShotTimer;
    int spawnPosition;
    Texture2D enemyTexture = {0, 0, 0, 0};
    bool textureLoaded;
    Vector2 position;
    std::vector<Bullet> enemyBullets;
    std::vector<Debris> enemyDebris;

    Enemy();
    ~Enemy();
    void update();

    void hover(int position, int hoverRange);

    void EnemyExplosion(float explosionArea, float debrisSize);
    void FillDebris(int particleAmount);

    void InitDefaultEnemyDefaults(int pos);
    Texture2D LoadEnemyTexture();
    void UpdateEnemyDefaultAttack(int posX, Texture2D &btxtr);
    void ResetDefaultEnenmy();

    void isHit(std::vector<Bullet> &leftBullets, std::vector<Bullet> &rightBullets, int &playerScore);
    void UnloadEnemy();

private:
    bool leftHover;
    bool rightHover;
};

#endif