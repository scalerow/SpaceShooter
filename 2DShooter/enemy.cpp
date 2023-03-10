#include "enemy.h"

Enemy::Enemy()
{
    health = 100;
    isBoss = false;
    active = false;
    leftHover = false,
    rightHover = true;
}

Enemy::~Enemy() {}

void Enemy::update()
{
    y += speed;
}

void Enemy::hover(int position, int hoverRange)
{
    int range[] = {position - hoverRange, position + hoverRange};

    if (leftHover && x > range[0])
    {
        x -= speed;

        if (x == range[0])
        {
            rightHover = true;
            leftHover = false;
        }
    }

    if (rightHover && x <= range[1])
    {
        x += speed;

        if (x == range[1])
        {
            rightHover = false;
            leftHover = true;
        }
    }
}

// Initialize the plane for the game
void Enemy::InitDefaultEnemyDefaults(int pos)
{

    Image defaultEnemyImg = LoadImage("./media/default_enemy_0.png");
    enemyTexture = LoadTextureFromImage(defaultEnemyImg);
    speed = 2.f;
    spawnPosition = pos;
    UnloadImage(defaultEnemyImg);
}

// Clear remenants of texture from memory
void Enemy::UnloadEnemy()
{
    UnloadTexture(enemyTexture);
}

void Enemy::isHit(std::vector<Bullet> &leftBullets, std::vector<Bullet> &rightBullets, int &playerScore)
{
    if (leftBullets.size() > 0 && rightBullets.size() > 0)
    {
        // Creating enemy hitbox
        Vector2 enemyPos = {(float)x, (float)y};
        Vector2 enemySize = {(float)enemyTexture.width, (float)enemyTexture.height};
        Rectangle enemyRect = {enemyPos.x, enemyPos.y - 50, enemySize.x, enemySize.y};
        Vector2 enemyTrianglePointOne = {enemyPos.x + 4, enemyPos.y + 26};
        Vector2 enemyTrianglePointTwo = {enemyPos.x + 49, enemyPos.y + 106};
        Vector2 enemyTrianglePointThree = {enemyPos.x + 95, enemyPos.y + 26};

        // Determing collision between right playerbullet and enemy
        for (int x = 0; x < rightBullets.size(); x++)
        {
            // Creating bullet hitbox
            Vector2 bulletRightPos = {(float)rightBullets[x].x, (float)rightBullets[x].y};
            Vector2 bulletRightSize = {(float)rightBullets[x].bulletTexture.width, (float)rightBullets[x].bulletTexture.height};
            Rectangle bulletRect = {bulletRightPos.x, bulletRightPos.y, bulletRightSize.x, bulletRightSize.y};
            // Collision determination
            // if (CheckCollisionRecs(enemyRect, bulletRect))
            if (CheckCollisionPointTriangle(Vector2{bulletRightPos.x + 5, bulletRightPos.y}, enemyTrianglePointOne, enemyTrianglePointTwo, enemyTrianglePointThree))
            {
                if (y >= 150)
                {
                    // Inflict damage according to bulletdamage, to enemy if hit and deactivate bullet
                    health -= rightBullets[x].bulletDamage;
                    // DrawCircleGradient(bulletRightPos.x + 5, bulletRightPos.y + 10, 10.f, Fade(WHITE, 0.6f), Fade(WHITE, 0.0f));
                    // DrawCircleV({bulletRightPos.x + 5, bulletRightPos.y + 10}, 4.f, WHITE);

                    for(int i = 3; i --> 0;)
                    {
                        if(i == 0)
                        {
                            
                            DrawCircleGradient(bulletRightPos.x + 5, bulletRightPos.y + 10, 10.f, Fade(GREEN, 0.6f), Fade(GREEN, 0.0f));
                            DrawCircleV({bulletRightPos.x + 5, bulletRightPos.y + 10}, 4.f, GREEN);
                        }
                        else
                        {
                            DrawCircleLines(bulletRightPos.x + 4.f, bulletRightPos.y + 9.f, i * 15, GREEN);
                            DrawCircleLines(bulletRightPos.x + 5.f, bulletRightPos.y + 10.f, i * 15, GREEN);
                        }
                            
                    }

                    rightBullets[x].bulletActive = false;
                }
                rightBullets.erase(rightBullets.begin() + x);

                if (health <= 0 && active)
                {
                    // Deactivates plane to remove it from screen
                    active = false;

                    // Increasing playerscore by whatever points is determined for default enemies
                    playerScore += 110;
                }
            }
        }

        // Determing collision between left playerbullet and enemy
        for (int x = 0; x < leftBullets.size(); x++)
        {
            // Creating bullet hitbox
            Vector2 bulletLeftPos = {(float)leftBullets[x].x, (float)leftBullets[x].y};
            Vector2 bulletLeftSize = {(float)leftBullets[x].bulletTexture.width, (float)leftBullets[x].bulletTexture.height};
            Rectangle bulletRect = {bulletLeftPos.x, bulletLeftPos.y - 16, bulletLeftSize.x, bulletLeftSize.y};

            // Collision determination
            // if (CheckCollisionRecs(enemyRect, bulletRect))
            if (CheckCollisionPointTriangle(Vector2{bulletLeftPos.x + 5, bulletLeftPos.y}, enemyTrianglePointOne, enemyTrianglePointTwo, enemyTrianglePointThree))

            {
                if (y >= 150)
                {
                    // Inflict damage according to bulletdamage, to enemy if hit and deactivate bullet
                    health -= leftBullets[x].bulletDamage;
                    // DrawCircleGradient(bulletLeftPos.x + 5, bulletLeftPos.y + 10, 10.f, Fade(WHITE, 0.6f), Fade(WHITE, 0.0f));
                    // DrawCircleV({bulletLeftPos.x + 5, bulletLeftPos.y + 10}, 4.f, WHITE);
                    
                    for(int i = 3; i --> 0;)
                    {
                        if(i == 0)
                        {
                            
                            DrawCircleGradient(bulletLeftPos.x + 5, bulletLeftPos.y + 10, 10.f, Fade(GREEN, 0.6f), Fade(GREEN, 0.0f));
                            DrawCircleV({bulletLeftPos.x + 5, bulletLeftPos.y + 10}, 4.f, GREEN);
                        }
                        else
                        {
                            DrawCircleLines(bulletLeftPos.x + 4.f, bulletLeftPos.y + 9.f, i * 15, GREEN);
                            DrawCircleLines(bulletLeftPos.x + 5.f, bulletLeftPos.y + 10.f, i * 15, GREEN);
                        }
                            
                    }

                    leftBullets[x].bulletActive = false;
                }
                leftBullets.erase(leftBullets.begin() + x);

                if (health <= 0 && active)
                {
                    // Deactivates plane to remove it from screen
                    active = false;
                    // Increasing playerscore by whatever points is determined for default enemies
                    playerScore += 110;
                }
            }
        }
        if (health <= 0)
        {
            FillDebris(80);
        }
    }
}

void Enemy::EnemyExplosion(float explosionArea, float debrisSize)
{

    float bloom = 8.f;
    for (int i = 0; i < enemyDebris.size(); i++)
    {
        Debris &debri = enemyDebris[i];
        DrawCircleGradient(debri.Position.x, debri.Position.y-8.f, debrisSize, Fade(WHITE, 0.6f), Fade(WHITE, 0.0f));
        DrawCircle(debri.Position.x, debri.Position.y - 8.f, debrisSize/4, WHITE);
        debri.Position.x += debri.Velocity.x * GetFrameTime();
        debri.Position.y += debri.Velocity.y * GetFrameTime();

        bool xRange;
        bool yRange;

        xRange =  debri.Position.x < x - explosionArea || debri.Position.x > x + explosionArea;
        yRange = debri.Position.y < y - explosionArea || debri.Position.y > y + explosionArea;
       
        if (xRange || yRange)
        {
            enemyDebris.erase(enemyDebris.begin() + i);
        }
        if (enemyDebris.empty())
        {
            ResetDefaultEnenmy();
        }
    }
}

void Enemy::FillDebris(int particleAmount)
{
    for (int i = 0; i < particleAmount; i++)
    {
        float debriSpeed = (float)GetRandomValue(50, 300);
        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_real_distribution<float> dist(0.0f, 2.0f * PI);
        float direction = dist(rng);

        enemyDebris.push_back(
            Debris{
                Vector2{debriSpeed * std::cos(direction), debriSpeed * std::sin(direction)},
                Vector2{(float)x, (float)y}});
    }
}

void Enemy::UpdateEnemyDefaultAttack(int posX, Texture2D &btxtr)
{
    if (defaultShotTimer < 80)
    {
        defaultShotTimer++;
    }
    if (defaultShotTimer >= 80 && active == true && y >= 150)
    {
        Bullet bullet;
        bullet.InitEnemyBullet(posX + (enemyTexture.width / 2), btxtr);
        enemyBullets.push_back(bullet);
        defaultShotTimer = 0;
    }

    for (int i = 0; i < enemyBullets.size(); i++)
    {

        if (!enemyBullets[i].enemyBulletCollides() && enemyBullets[i].bulletActive)
        {
            enemyBullets[i].updateEnemyBullet();
            DrawTexture(enemyBullets[i].bulletTexture, enemyBullets[i].x, enemyBullets[i].y, WHITE);
        }
        else
        {
            enemyBullets.erase(enemyBullets.begin() + i);
        }
    }
}

void Enemy::ResetDefaultEnenmy()
{
    health = 100;
    active = false;
    y = -100;
    x = spawnPosition;
}