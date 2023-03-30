#include "level_01.h"

void Level_01::SpawnBoss()
{
    boss.InitBoss(CalculateXCoord(100/2), 500, 2);

}

void Level_01::DrawMultipleEnemies(std::vector<int> &xPositions)
{
     if (enemies.size() <= 0)
    {
        defaultEnemyTexture = LoadDefaultEnemyTexture();
        defaultEnemyBulletTexture = InitDefaultEnemyBulletTexture();
    }
    for (int i = 0; i < 4; i++)
    {
        // First spawn,initiating 4 enemies
        if (enemies.size() < 4)
        {
            Enemy defEnemy;
            defEnemy.InitDefaultEnemyDefaults(xPositions[i], defaultEnemyTexture);
            defEnemy.ResetDefaultEnenmy();
            enemies.push_back(defEnemy);
        }

        // Activate new enemy
        if (!enemies[i].active && enemies[i].health >= 100)
            enemies[i].active = true;

        // Enemy killed and removed, explosion
        if (enemies[i].health <= 0 && !enemies[i].active)
        {
            enemies[i].EnemyExplosion(CalculateObjectSizeY(200.f), CalculateObjectSizeY(8.f));
        }

        // Hover and draw default enenmy movements
        if (enemies[i].active && enemies[i].health > 0)
        {
            if (enemies[i].y <= 150)
                enemies[i].y += enemies[i].speed;
            else
                enemies[i].hover(CalculateByPixelsX(xPositions[i]));

            DrawTexture(enemies[i].enemyTexture, enemies[i].x, enemies[i].y, WHITE);
        }
        enemies[i].UpdateEnemyDefaultAttack(enemies[i].x, defaultEnemyBulletTexture);

    }
}

void Level_01::UnloadMultipleEnemies()
{
    for (int i = 0; i < enemies.size(); i++)
    {
        
        enemies[i].UnloadEnemy();
        enemies[i].ResetDefaultEnenmy();
        enemies[i].enemyBullets.clear();
    }
    enemies.clear();

}

void Level_01::UpdateBoss() 
{

}

void Level_01::isBossHit()
{}

void Level_01::LevelComplete()
{}