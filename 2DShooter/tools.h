#ifndef TOOLS_H
#define TOOLS_H

#include <raylib.h>
#include <vector>
#include "enemy.h"
#include "bullet.h"
#include <cmath>

using namespace std;

class Tools
{
private:
public:
    vector<Enemy> enemies;
    vector<Bullet> bullets;
    Texture2D enemyBulletTexture;

    Tools();
    ~Tools();
    void InitEnemyBulletTexture();
    void CreateMultipleEnemies(int xPositions[4]);
    void InitEnemiesAttack(int positionX[4]);
    void InitSpecialAttack(Vector2 position);
};

#endif