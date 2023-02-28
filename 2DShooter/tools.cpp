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
            defEnemy.ResetDefaultEnenmy(xPositions[i]);
            enemies.push_back(defEnemy);
        }

        if (!enemies[i].active && enemies[i].health >= 0)
            enemies[i].active = true;

        if (enemies[i].health <= 0)
        {
            enemies[i].ResetDefaultEnenmy(xPositions[i]);
            return;
        }

        if (enemies[i].active && enemies[i].health > 0)
        {
            if (enemies[i].y <= 150)
                enemies[i].y += enemies[i].speed;
            else
                enemies[i].hover(xPositions[i], 50);
            DrawTexture(enemies[i].enemyTexture, enemies[i].x, enemies[i].y, WHITE);
        }
    }
}

void Tools::CreateSpecialAttack(Vector2 position) 
{  
    if(bullets.size() < 10)
    {

        Bullet bullet;
        bullet.InitSpecialAttack(position);
        bullets.push_back(bullet);
    }      
    
    for (int x = 0; x < bullets.size(); x++)
    {        
            bullets[x].rotation += 5;
            bullets[x].radius += 1;
            bullets[x].x += cos(bullets[x].rotation * DEG2RAD) * bullets[x].radius;
            bullets[x].y -=  sin(bullets[x].rotation * DEG2RAD) * bullets[x].radius;
            //DrawTexture(bullets[x].texture, bullets[x].x, bullets[x].y, WHITE);
            DrawTexture(bullets[x].bulletTexture, bullets[x].x,bullets[x].y, WHITE);
            if (bullets[x].radius < 100)
                bullets[x].radius += bullets[x].speed;
            
                
    }
}