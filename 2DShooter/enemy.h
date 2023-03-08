#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include <raylib.h>
#include "bullet.h"
#include "tools.h"
#include "gameobjects.h"

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
    int defaultShotTimer;
    Texture2D enemyTexture;
    Vector2 position;
    vector<Bullet> enemyBullets;

    Enemy();
    ~Enemy();
    void update();

    void hover(int position, int hoverRange);

    void EnemyExplosion();
    void FillParticles(vector<Debris> &debris);
    float Distance(float x, float y);

    void InitEnemy();
    void UpdateEnemyDefaultAttack(int posX, Texture2D &btxtr);
    void ResetDefaultEnenmy(int spawnPositionX);

    void isHit(vector<Bullet> &leftBullets, vector<Bullet> &rightBullets, int &playerScore);
    void UnloadEnemy();

private:
    bool leftHover;
    bool rightHover;
};

#endif