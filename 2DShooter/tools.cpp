#include "tools.h"

Tools::Tools(/* args */)
{
}

Tools::~Tools()
{
}

void Tools::InitEnemyBulletTexture()
{
    Image defaultEnemyBulletImg = LoadImage("./media/bullet_enemy_0.png");
    Texture2D defaultenemyBulletTexture = LoadTextureFromImage(defaultEnemyBulletImg);
    UnloadImage(defaultEnemyBulletImg);
    enemyBulletTexture = defaultenemyBulletTexture;
}

void Tools::CreateMultipleEnemies(int xPositions[4])
{
    if (enemyBulletTexture.width != 10)
    {
        InitEnemyBulletTexture();
    }

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
            enemies[i].UpdateEnemyDefaultAttack(enemies[i].x, enemyBulletTexture);
        }
    }
}

void Tools::InitSpecialAttack(Vector2 position)
{
    if (bullets.size() < 6)
    {

        Bullet bullet;
        bullet.InitSpecialAttackBullet(position);
        bullets.push_back(bullet);
    }
}
