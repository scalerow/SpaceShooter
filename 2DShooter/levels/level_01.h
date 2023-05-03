#ifndef LEVEL_01
#define LEVEL_01

#include <raylib.h>
#include "..\enemy.h"
#include "..\player.h"
#include "..\gameobjects.h"
#include <vector>

class Level_01
{
private:
    void InitDefaultEnemyBulletTexture();

public:
    std::vector<Enemy> enemies;
    Texture2D defaultEnemyTexture;
    Texture2D defaultEnemyBulletTexture;
    Enemy boss;

    Level_01();
    ~Level_01();

    void DrawMultipleEnemies(std::vector<int> &xPositions, Player &player);
    void UnloadMultipleEnemies();
    void SpawnBoss();
    void UpdateBoss();
    void isBossHit();
    void LevelComplete();
};

#endif
