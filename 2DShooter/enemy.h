#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include <raylib.h>

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
    void CreateEnemies(float delta, Vector4 flightArea);
    void UnloadEnemy();

    void isHit(Rectangle enemyBndBox, Rectangle bulletBndBox);

private:
    bool leftHover;
    bool rightHover;
};

#endif