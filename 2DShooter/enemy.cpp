#include "enemy.h"

Enemy::Enemy()
{
    health = 100;
    defaultEnemyHoverRange = 50;
    scoreValue = 110;
    isBoss = false;
    active = false;
    leftHover = false,
    rightHover = true;
}

Enemy::~Enemy() {}

void Enemy::update()
{
    position.y += speed;
}

void Enemy::hover(int enemyPos)
{
    int range[] = {enemyPos - defaultEnemyHoverRange, enemyPos + defaultEnemyHoverRange};

    if (leftHover && position.x > range[0])
    {
        position.x -= speed;

        if (position.x == range[0])
        {
            rightHover = true;
            leftHover = false;
        }
    }

    if (rightHover && position.x <= range[1])
    {
        position.x += speed;

        if (position.x == range[1])
        {
            rightHover = false;
            leftHover = true;
        }
    }
}
Texture2D Enemy::LoadEnemyTexture()
{
    Image defaultEnemyImg = LoadImage("./media/default_enemy_0.png");
    ImageResize(&defaultEnemyImg, GameObjects::CalculateObjectSizeX(defaultEnemyImg.width), GameObjects::CalculateObjectSizeY(defaultEnemyImg.height));
    Texture2D text = LoadTextureFromImage(defaultEnemyImg);
    UnloadImage(defaultEnemyImg);

    return text;
}

void Enemy::InitBoss(float posX, int health, int speed)
{
    enemyTexture = LoadTexture("media\\boss_2.png");
    health = health;
    position = {posX, 0};
    health = health;
    speed = speed;
}

// Initialize the plane for the game
void Enemy::InitDefaultEnemyDefaults(int pos, Texture2D &texture)
{
    enemyTexture = texture;
    speed = 2.f;
    spawnPosition = pos;
}

// Clear remenants of texture from memory
void Enemy::UnloadEnemy()
{
    UnloadTexture(enemyTexture);
    enemyBullets.clear();
    enemyDebris.clear();
}

void Enemy::isTriangleHit(std::vector<Bullet> &leftBullets, std::vector<Bullet> &rightBullets, int &playerScore)
{
    int enemyTextureWidth = frameCount == 0 ? enemyTexture.width : enemyTexture.width / frameCount;

    if (leftBullets.size() > 0 && rightBullets.size() > 0)
    {
        // Creating enemy hitbox
        Vector2 enemyPos = {(float)position.x, (float)position.y};
        Vector2 enemySize = {(float)enemyTextureWidth, (float)enemyTexture.height};
        Vector2 enemyTrianglePointOne = {enemyPos.x + GameObjects::CalculateObjectSizeX(4), enemyPos.y + GameObjects::CalculateObjectSizeY(26)};
        Vector2 enemyTrianglePointTwo = {enemyPos.x + GameObjects::CalculateObjectSizeX(49), enemyPos.y + GameObjects::CalculateObjectSizeY(106)};
        Vector2 enemyTrianglePointThree = {enemyPos.x + GameObjects::CalculateObjectSizeX(95), enemyPos.y + GameObjects::CalculateObjectSizeY(26)};

        // Determing collision between right playerbullet and enemy
        for (int x = 0; x < rightBullets.size(); x++)
        {
            // For verifying hitbox, comment out when done
            // DrawTriangle(enemyTrianglePointOne, enemyTrianglePointTwo, enemyTrianglePointThree, RED);
            //  Creating bullet hitbox
            Vector2 bulletRightPos = {(float)rightBullets[x].x, (float)rightBullets[x].y};
            Vector2 bulletRightSize = {(float)rightBullets[x].bulletTexture.width, (float)rightBullets[x].bulletTexture.height};
            Rectangle bulletRect = {bulletRightPos.x, bulletRightPos.y, bulletRightSize.x, bulletRightSize.y};
            // Collision determination
            bool leftCornerBullet = CheckCollisionPointTriangle(Vector2{bulletRightPos.x, bulletRightPos.y}, enemyTrianglePointOne, enemyTrianglePointTwo, enemyTrianglePointThree);
            bool rightCornerBullet = CheckCollisionPointTriangle(Vector2{bulletRightPos.x + bulletRightSize.x, bulletRightPos.y}, enemyTrianglePointOne, enemyTrianglePointTwo, enemyTrianglePointThree);
            if (leftCornerBullet || rightCornerBullet)
            {
                // Inflict damage according to bulletdamage, to enemy if hit and deactivate bullet
                health -= rightBullets[x].bulletDamage;
                // DrawCircleGradient(bulletRightPos.x + 5, bulletRightPos.y + 10, 10.f, Fade(RED, 0.6f), Fade(RED, 0.0f));
                // DrawCircleV({bulletRightPos.x + 5, bulletRightPos.y + 10}, 4.f, RED);

                for (int i = 3; i-- > 0;)
                {
                    if (i == 0)
                    {

                        DrawCircleGradient(bulletRightPos.x + GameObjects::CalculateObjectSizeX(5), bulletRightPos.y + GameObjects::CalculateObjectSizeY(10), GameObjects::CalculateObjectSizeY(10.f), Fade(RED, 0.6f), Fade(RED, 0.0f));
                        DrawCircleV({bulletRightPos.x + GameObjects::CalculateObjectSizeX(5), bulletRightPos.y + GameObjects::CalculateObjectSizeY(10.f)}, GameObjects::CalculateObjectSizeY(4.f), RED);
                    }
                    else
                    {
                        DrawCircleLines(bulletRightPos.x + GameObjects::CalculateObjectSizeX(4.f), bulletRightPos.y + GameObjects::CalculateObjectSizeY(9.f), GameObjects::CalculateObjectSizeY(i * 15), RED);
                        DrawCircleLines(bulletRightPos.x + GameObjects::CalculateObjectSizeX(5.f), bulletRightPos.y + GameObjects::CalculateObjectSizeY(10.f), GameObjects::CalculateObjectSizeY(i * 15), RED);
                    }
                }

                rightBullets[x].bulletActive = false;

                rightBullets.erase(rightBullets.begin() + x);

                if (health <= 0 && active)
                {
                    // Deactivates plane to remove it from screen
                    active = false;

                    // Increasing playerscore by whatever points is determined for default enemies
                    playerScore += scoreValue;
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
            bool leftCornerBullet = CheckCollisionPointTriangle(Vector2{bulletLeftPos.x, bulletLeftPos.y}, enemyTrianglePointOne, enemyTrianglePointTwo, enemyTrianglePointThree);
            bool rightCornerBulllet = CheckCollisionPointTriangle(Vector2{bulletLeftPos.x + bulletLeftSize.x, bulletLeftPos.y}, enemyTrianglePointOne, enemyTrianglePointTwo, enemyTrianglePointThree);
            if (leftCornerBullet || rightCornerBulllet)
            {
                // Inflict damage according to bulletdamage, to enemy if hit and deactivate bullet
                health -= leftBullets[x].bulletDamage;
                // DrawCircleGradient(bulletLeftPos.x + 5, bulletLeftPos.y + 10, 10.f, Fade(RED, 0.6f), Fade(RED, 0.0f));
                // DrawCircleV({bulletLeftPos.x + 5, bulletLeftPos.y + 10}, 4.f, RED);

                for (int i = 3; i-- > 0;)
                {
                    if (i == 0)
                    {

                        DrawCircleGradient(bulletLeftPos.x + GameObjects::CalculateObjectSizeX(5), bulletLeftPos.y + GameObjects::CalculateObjectSizeY(10), GameObjects::CalculateObjectSizeY(10.f), Fade(RED, 0.6f), Fade(RED, 0.0f));
                        DrawCircleV({bulletLeftPos.x + GameObjects::CalculateObjectSizeX(5), bulletLeftPos.y + GameObjects::CalculateObjectSizeY(10.f)}, GameObjects::CalculateObjectSizeY(4.f), RED);
                    }
                    else
                    {
                        DrawCircleLines(bulletLeftPos.x + GameObjects::CalculateObjectSizeX(4.f), bulletLeftPos.y + GameObjects::CalculateObjectSizeY(9.f), GameObjects::CalculateObjectSizeY(i * 15), RED);
                        DrawCircleLines(bulletLeftPos.x + GameObjects::CalculateObjectSizeX(5.f), bulletLeftPos.y + GameObjects::CalculateObjectSizeY(10.f), GameObjects::CalculateObjectSizeY(i * 15), RED);
                    }
                }

                leftBullets[x].bulletActive = false;

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
            FillDebris(40);
        }
    }
}

void Enemy::isCircleHit(std::vector<Bullet> &leftBullets, std::vector<Bullet> &rightBullets, int &playerScore)
{
    int enemyTextureWidth = frameCount == 0 ? enemyTexture.width : enemyTexture.width / frameCount;
    if (leftBullets.size() > 0 && rightBullets.size() > 0)
    {
        // Creating enemy hitbox
        Vector2 enemyCenter = {position.x + (enemyTextureWidth / 2), position.y + (enemyTexture.height / 2)};
        float enemyRadius = enemyTextureWidth / 2;

        // Determing collision between right playerbullet and enemy
        for (int x = 0; x < rightBullets.size(); x++)
        {
            // For verifying hitbox, comment out when done
            // DrawTriangle(enemyTrianglePointOne, enemyTrianglePointTwo, enemyTrianglePointThree, RED);
            //  Creating bullet hitbox
            Vector2 bulletRightPos = {(float)rightBullets[x].x, (float)rightBullets[x].y};
            Vector2 bulletRightSize = {(float)rightBullets[x].bulletTexture.width, (float)rightBullets[x].bulletTexture.height};
            Rectangle bulletRect = {bulletRightPos.x, bulletRightPos.y, bulletRightSize.x, bulletRightSize.y};

            // Collision determination
            bool bulletHit = CheckCollisionCircleRec(enemyCenter, enemyRadius, bulletRect);

            if (bulletHit)
            {
                // Inflict damage according to bulletdamage, to enemy if hit and deactivate bullet
                health -= rightBullets[x].bulletDamage;
                // DrawCircleGradient(bulletRightPos.x + 5, bulletRightPos.y + 10, 10.f, Fade(RED, 0.6f), Fade(RED, 0.0f));
                // DrawCircleV({bulletRightPos.x + 5, bulletRightPos.y + 10}, 4.f, RED);

                for (int i = 3; i-- > 0;)
                {
                    if (i == 0)
                    {

                        DrawCircleGradient(bulletRightPos.x + GameObjects::CalculateObjectSizeX(5), bulletRightPos.y + GameObjects::CalculateObjectSizeY(10), GameObjects::CalculateObjectSizeY(10.f), Fade(RED, 0.6f), Fade(RED, 0.0f));
                        DrawCircleV({bulletRightPos.x + GameObjects::CalculateObjectSizeX(5), bulletRightPos.y + GameObjects::CalculateObjectSizeY(10.f)}, GameObjects::CalculateObjectSizeY(4.f), RED);
                    }
                    else
                    {
                        DrawCircleLines(bulletRightPos.x + GameObjects::CalculateObjectSizeX(4.f), bulletRightPos.y + GameObjects::CalculateObjectSizeY(9.f), GameObjects::CalculateObjectSizeY(i * 15), RED);
                        DrawCircleLines(bulletRightPos.x + GameObjects::CalculateObjectSizeX(5.f), bulletRightPos.y + GameObjects::CalculateObjectSizeY(10.f), GameObjects::CalculateObjectSizeY(i * 15), RED);
                    }
                }

                rightBullets[x].bulletActive = false;

                rightBullets.erase(rightBullets.begin() + x);

                if (health <= 0 && active)
                {
                    // Deactivates plane to remove it from screen
                    active = false;

                    // Increasing playerscore by whatever points is determined for default enemies
                    playerScore += scoreValue;
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
            bool bulletHit = CheckCollisionCircleRec(enemyCenter, enemyRadius, bulletRect);

            if (bulletHit)
            {
                // Inflict damage according to bulletdamage, to enemy if hit and deactivate bullet
                health -= leftBullets[x].bulletDamage;
                // DrawCircleGradient(bulletLeftPos.x + 5, bulletLeftPos.y + 10, 10.f, Fade(RED, 0.6f), Fade(RED, 0.0f));
                // DrawCircleV({bulletLeftPos.x + 5, bulletLeftPos.y + 10}, 4.f, RED);

                for (int i = 3; i-- > 0;)
                {
                    if (i == 0)
                    {

                        DrawCircleGradient(bulletLeftPos.x + GameObjects::CalculateObjectSizeX(5), bulletLeftPos.y + GameObjects::CalculateObjectSizeY(10), GameObjects::CalculateObjectSizeY(10.f), Fade(RED, 0.6f), Fade(RED, 0.0f));
                        DrawCircleV({bulletLeftPos.x + GameObjects::CalculateObjectSizeX(5), bulletLeftPos.y + GameObjects::CalculateObjectSizeY(10.f)}, GameObjects::CalculateObjectSizeY(4.f), RED);
                    }
                    else
                    {
                        DrawCircleLines(bulletLeftPos.x + GameObjects::CalculateObjectSizeX(4.f), bulletLeftPos.y + GameObjects::CalculateObjectSizeY(9.f), GameObjects::CalculateObjectSizeY(i * 15), RED);
                        DrawCircleLines(bulletLeftPos.x + GameObjects::CalculateObjectSizeX(5.f), bulletLeftPos.y + GameObjects::CalculateObjectSizeY(10.f), GameObjects::CalculateObjectSizeY(i * 15), RED);
                    }
                }

                leftBullets[x].bulletActive = false;

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
            FillDebris(40);
        }
    }
}

void Enemy::EnemyExplosion(float explosionArea, float debrisSize)
{

    float delta = GetFrameTime();
    float bloom = 8.f;
    for (int i = 0; i < enemyDebris.size(); i++)
    {
        GameObjects::Debris &debri = enemyDebris[i];
        DrawCircleGradient(debri.Position.x, debri.Position.y - 8.f, debrisSize, Fade({242, 229, 170, 255}, 0.6f), Fade({242, 229, 170, 255}, 0.0f));
        DrawCircle(debri.Position.x, debri.Position.y - 8.f, debrisSize / 4, {242, 229, 170, 255});
        debri.Position.x += debri.Velocity.x * delta;
        debri.Position.y += debri.Velocity.y * delta;

        bool xRange;
        bool yRange;

        xRange = debri.Position.x < position.x - explosionArea || debri.Position.x > position.x + explosionArea;
        yRange = debri.Position.y < position.y - explosionArea || debri.Position.y > position.y + explosionArea;

        if (xRange || yRange)
        {
            enemyDebris.erase(enemyDebris.begin() + i);
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
            GameObjects::Debris{
                Vector2{debriSpeed * std::cos(direction), debriSpeed * std::sin(direction)},
                Vector2{position.x, position.y}});
    }
}

void Enemy::UpdateEnemyDefaultAttack(int posX, Texture2D &btxtr)
{
    if (defaultShotTimer < 80)
    {
        defaultShotTimer++;
    }
    if (defaultShotTimer >= 80 && active == true && position.y >= 150)
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

void Enemy::UpdateEnemyAttack(int posX, int posY, Texture2D &btxtr, int shotTimer, int frameCount, int frameCap)
{
    if (defaultShotTimer < shotTimer)
    {
        defaultShotTimer++;
    }
    if (defaultShotTimer >= shotTimer && active == true)
    {
        Bullet bullet;
        bullet.InitEnemyBullet(posX + 50, btxtr);
        bullet.y = posY + (enemyTexture.height);
        bullet.bulletSpeed = 500;
        bullet.frameCount = frameCount;
        bullet.bulletDamage = 15;
        enemyBullets.push_back(bullet);
        defaultShotTimer = 0;
    }

    for (int i = 0; i < enemyBullets.size(); i++)
    {

        if (!enemyBullets[i].enemyBulletCollides() && enemyBullets[i].bulletActive)
        {
            if (frameCount == 0 || frameCap == 0)
            {
                enemyBullets[i].updateEnemyBullet();
                DrawTexture(enemyBullets[i].bulletTexture, enemyBullets[i].x, enemyBullets[i].y, WHITE);
            }
            else
            {
                enemyBullets[i].UpdateAnimatedEnemyBullet(frameCap);
            }
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
    position.y = -100;
    position.x = spawnPosition;
}