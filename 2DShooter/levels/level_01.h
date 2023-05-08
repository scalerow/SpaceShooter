#ifndef LEVEL_01
#define LEVEL_01

#include <raylib.h>
#include "..\enemy.h"
#include "..\player.h"
#include "..\gameobjects.h"
#include <vector>
#include <iostream>
#include <time.h>

class Level_01
{
private:
    void InitDefaultEnemyBulletTexture();
    double randomEnemySpawnTimer = 0;

    Texture2D randomEnemyTexture;
    Texture2D randomEnemyBulletTexture;
    Texture2D defaultEnemyTexture;
    Texture2D defaultEnemyBulletTexture;

    bool isRandomEnemyBulletTextureLoaded = false;
    bool isRandomEnemyTextureLoaded = false;

    const int randomEnemySpawnCount[3] = {1, 2, 3};
    const int randomSpawnDelay = 40;
    const std::string randomEnemySpawnPositions[4] = {"top-left", "top-right", "bottom-left", "bottom-right"};
    int currentRandomEnemySpawnCount;
    std::string currentRandomEnemySpawnPosition;

    void SetRandomSpawnProps();
    void CreateRandomSpawn(Vector2 spawnPos, Vector2 mapEdge);

public:
    std::vector<Enemy> defaultEnemies;
    std::vector<Enemy> randomEnemies;

    Enemy boss;

    Level_01();
    ~Level_01();

    double GetLastEnemySpawnedTime();
    void SetLastEnemySpawnedTime(double lastTime);
    void RandomEnemySpawn();
    void UpdateRandomEnemies();
    void DrawRandomEnemies(Player &player);
    void InitRandomEnemyTexture();
    void InitRandomEnemyBulletTexture();
    void ResetRandomEnemy(Enemy &randomEnemy);

    void DrawMultipleEnemies(std::vector<int> &xPositions, Player &player);
    void UnloadMultipleEnemies();

    void SpawnBoss();
    void UpdateBoss();
    void isBossHit();

    void LevelComplete();
    void UnloadLevel1();
};

#endif
