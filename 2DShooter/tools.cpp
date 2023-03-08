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
    enemyBulletTexture = &defaultenemyBulletTexture;
}

void Tools::CreateMultipleEnemies(int xPositions[4])
{
    if (enemyBulletTexture->width != 10)
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
            enemies[i].EnemyExplosion();
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
            enemies[i].UpdateEnemyDefaultAttack(enemies[i].x, *enemyBulletTexture);
        }
    }
}

void Tools::FillParticles(vector<Debris> &debris)
{
    for(int i = 0; i < 100; i++)
    {
        float speed = (float)GetRandomValue(50, 300);
        mt19937 rng;
        rng.seed(random_device()());
        uniform_real_distribution<float> dist(0.0f, 2.0f * PI);
        float direction = dist(rng);

        debris.push_back(
            Debris{
                Vector2 {speed * cos(direction), speed * sin(direction)},
                Vector2 {(float)GetScreenWidth() /2.0f, (float)GetScreenHeight() /2.0f} 
            }
        );
    }
}

float Tools::Distance(float x, float y)
{
    return (float)sqrt((x*x) + (y*y));
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
