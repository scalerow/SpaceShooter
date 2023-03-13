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
    ImageResize(&defaultEnemyBulletImg, CalculateObjectSizeX(defaultEnemyBulletImg.width), CalculateObjectSizeY(defaultEnemyBulletImg.height));
    Texture2D defaultenemyBulletTexture = LoadTextureFromImage(defaultEnemyBulletImg);
    UnloadImage(defaultEnemyBulletImg);
    enemyBulletTexture = defaultenemyBulletTexture;
}

void Tools::CreateMultipleEnemies(std::vector<int> &xPositions)
{
    if (enemies.size() <= 0)
    {
        defaultEnemyTexture = LoadEnemyTexture();
        InitEnemyBulletTexture();
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
        enemies[i].UpdateEnemyDefaultAttack(enemies[i].x, enemyBulletTexture);

    }
}

// void Tools::FillParticles(std::vector<Debris> &debris)
// {
//     for(int i = 0; i < 100; i++)
//     {
//         float speed = (float)GetRandomValue(50, 300);
//         mt19937 rng;
//         rng.seed(random_device()());
//         uniform_real_distribution<float> dist(0.0f, 2.0f * PI);
//         float direction = dist(rng);

//         debris.push_back(
//             Debris{
//                 Vector2 {speed * cos(direction), speed * sin(direction)},
//                 Vector2 {(float)GetScreenWidth() /2.0f, (float)GetScreenHeight() /2.0f}
//             }
//         );
//     }
// }

// float Tools::Distance(float x, float y)
// {
//     return (float)sqrt((x*x) + (y*y));
// }

void Tools::InitSpecialAttack(Vector2 position)
{
    if (bullets.size() < 6)
    {

        Bullet bullet;
        bullet.InitSpecialAttackBullet(position);
        bullets.push_back(bullet);
    }
}
