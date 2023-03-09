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
    Texture2D enemyTexture;
    Vector2 position;
    std::vector<Bullet> enemyBullets;
    std::vector<Debris> enemyDebris;

    Enemy();
    ~Enemy();
    void update();

    void hover(int position, int hoverRange);

    void EnemyExplosion();
    void FillParticles();
    float Distance(float x, float y);

    void InitDefaultEnemyDefaults(int pos);
    void UpdateEnemyDefaultAttack(int posX, Texture2D &btxtr);
    void ResetDefaultEnenmy();

    void isHit(std::vector<Bullet> &leftBullets, std::vector<Bullet> &rightBullets, int &playerScore);
    void UnloadEnemy();

private:
    bool leftHover;
    bool rightHover;
};

#endif