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
void Enemy::InitEnemy()
{

    Image defaultEnemyImg = LoadImage("./media/default_enemy_0.png");
    enemyTexture = LoadTextureFromImage(defaultEnemyImg);
    speed = 2.f;
    UnloadImage(defaultEnemyImg);
}

// Clear remenants of texture from memory
void Enemy::UnloadEnemy()
{
    UnloadTexture(enemyTexture);
}

void Enemy::isHit(vector<Bullet> &leftBullets, vector<Bullet> &rightBullets, int &playerScore)
{
    if (leftBullets.size() > 0 && rightBullets.size() > 0)
    {
        Vector2 enemyPos = {(float)x, (float)y};
        Vector2 enemySize = {(float)enemyTexture.width, (float)enemyTexture.height};

        Rectangle enemyRect = {enemyPos.x, enemyPos.y - 50, enemySize.x, enemySize.y};
        for (int x = 0; x < rightBullets.size(); x++)
        {
            Vector2 bulletRightPos = {(float)rightBullets[x].x, (float)rightBullets[x].y};
            Vector2 bulletRightSize = {(float)rightBullets[x].bulletTexture.width, (float)rightBullets[x].bulletTexture.height};
            Rectangle bulletRect = {bulletRightPos.x, bulletRightPos.y, bulletRightSize.x, bulletRightSize.y};
            if (CheckCollisionRecs(enemyRect, bulletRect))
            {
                if (y >= 150)
                {
                    health -= rightBullets[x].bulletDamage;
                    rightBullets[x].bulletActive = false;
                }
                rightBullets.erase(rightBullets.begin() + x);
            }
        }
        for (int x = 0; x < leftBullets.size(); x++)
        {
            Vector2 bulletLeftPos = {(float)leftBullets[x].x, (float)leftBullets[x].y};
            Vector2 bulletLeftSize = {(float)leftBullets[x].bulletTexture.width, (float)leftBullets[x].bulletTexture.height};
            Rectangle bulletRect = {bulletLeftPos.x, bulletLeftPos.y - 16, bulletLeftSize.x, bulletLeftSize.y};
            if (CheckCollisionRecs(enemyRect, bulletRect))
            {
                if (y >= 150)
                {
                    health -= leftBullets[x].bulletDamage;
                    leftBullets[x].bulletActive = false;
                }
                leftBullets.erase(leftBullets.begin() + x);
            }
        }
        if (health <= 0)
            playerScore += 110;
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

void Enemy::ResetDefaultEnenmy(int spawnPositionX)
{
    speed = 2;
    health = 100;
    active = false;
    x = spawnPositionX;
    y = -100;
}