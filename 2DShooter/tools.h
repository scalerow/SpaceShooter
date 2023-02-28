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

    Tools();
    ~Tools();
    void CreateMultipleEnemies(int xPositions[4]);
    void CreateSpecialAttack(Vector2 position);
};

#endif