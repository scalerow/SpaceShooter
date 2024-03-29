#ifndef TOOLS_H
#define TOOLS_H

#include <raylib.h>
#include <vector>
#include "enemy.h"
#include "bullet.h"
#include <cmath>
#include "gameobjects.h"
// #include <random>

class Tools
{
private:
public:
    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;
    Texture2D enemyBulletTexture;
    Texture2D defaultEnemyTexture;

    Tools();
    ~Tools();
    void InitEnemyBulletTexture();
    void CreateMultipleEnemies(std::vector<int> &xPositions);
    void UnloadMultipleEnemies();
    void InitSpecialAttack(Vector2 position);
    // void FillParticles(vector<Debris> &debris);
    // float Distance(float x, float y);
};

#endif