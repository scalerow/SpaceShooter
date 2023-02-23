#include "tools.h"

Tools::Tools(/* args */)
{
}

Tools::~Tools()
{
}

void Tools::CreateMultipleEnemies(int xPositions[4])
{

    for (int i = 0; i < 4; i++)
    {
        if (enemies.size() < 4)
        {
            Enemy defEnemy;
            defEnemy.InitEnemy();
            defEnemy.speed = 2;
            defEnemy.x = xPositions[i];
            defEnemy.y = -100;
            enemies.push_back(defEnemy);
        }

        if (!enemies[i].active && enemies[i].health >= 0)
            enemies[i].active = true;

        if (enemies[i].health == 0)
        {
            enemies.erase(enemies.begin() + i);
        }

        if (enemies[i].active && enemies[i].health > 0)
        {
            enemies[i].active = true;
            if (enemies[i].y < 150)
                enemies[i].y += enemies[i].speed;
            else
                enemies[i].hover(xPositions[i], 50);
            DrawTexture(enemies[i].enemyTexture, enemies[i].x, enemies[i].y, WHITE);
        }
    }
}