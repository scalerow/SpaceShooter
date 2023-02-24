#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include <raylib.h>
#include "bullet.h"

using namespace std;

class Enemy
{
public:
    int x;
    int y;
    int health;
    bool active;
    int speed;
    bool isBoss;
    Texture2D enemyTexture;
    Vector2 position;

    Enemy();
    ~Enemy();
    void update();

    void hover(int position, int hoverRange);

    void InitEnemy();
    
    void ResetDefaultEnenmy(int spawnPositionX);
    
    void isHit(vector<Bullet> &leftBullets, vector<Bullet> &rightBullets);
    void UnloadEnemy();

private:
    bool leftHover;
    bool rightHover;
};

#endif