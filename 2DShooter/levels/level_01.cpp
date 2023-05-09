#include "level_01.h"

Level_01::Level_01()
{
}
Level_01::~Level_01()
{
}

void Level_01::SetRandomSpawnProps()
{
    srand(time(NULL));
    int randomPositionIndex = rand() % 4;
    int randomSpawnCountIndex = rand() % 3;

    currentRandomEnemySpawnPosition = randomEnemySpawnPositions[randomPositionIndex];
    //{0, 0}, { GameObjects::CalculateXCoord(100), 0}, {0,  GameObjects::CalculateYCoord(100)}, { GameObjects::CalculateXCoord(100),  GameObjects::CalculateYCoord(100)}
    currentRandomEnemySpawnCount = randomEnemySpawnCount[randomSpawnCountIndex];
}

double Level_01::GetLastEnemySpawnedTime()
{
    return randomEnemySpawnTimer;
}

void Level_01::SetLastEnemySpawnedTime(double lastTime)
{
    randomEnemySpawnTimer = lastTime;
}

void Level_01::CreateRandomSpawn(Vector2 spawnPos, Vector2 mapEdge)
{
    SetLastEnemySpawnedTime(GetTime());

    Enemy randomEnemy;
    randomEnemy.outOufMap = mapEdge;
    randomEnemy.frameCount = 3;
    randomEnemy.position = spawnPos;
    ResetRandomEnemy(randomEnemy);

    randomEnemies.push_back(randomEnemy);
}

void Level_01::RandomEnemySpawn()
{
    double timeNow = GetTime();

    if (!isRandomEnemyTextureLoaded)
    {
        InitRandomEnemyTexture();
        isRandomEnemyTextureLoaded = true;
    }
    if (!isRandomEnemyBulletTextureLoaded)
    {
        InitRandomEnemyBulletTexture();
    }

    if (randomEnemySpawnTimer + 20.00 <= timeNow)
    {
        SetRandomSpawnProps();

        if (currentRandomEnemySpawnPosition.compare("top-left") == 0)
        {
            CreateRandomSpawn({0, 0}, {GameObjects::CalculateXCoord(100), GameObjects::CalculateYCoord(100)});
        }
        else if (currentRandomEnemySpawnPosition.compare("top-right") == 0)
        {
            CreateRandomSpawn({GameObjects::CalculateXCoord(100), 0}, {GameObjects::CalculateXCoord(0), GameObjects::CalculateYCoord(100)});
        }
        else if (currentRandomEnemySpawnPosition.compare("bottom-left") == 0)
        {
            CreateRandomSpawn({0, GameObjects::CalculateYCoord(100)}, {GameObjects::CalculateXCoord(100), GameObjects::CalculateYCoord(0)});
        }
        else if (currentRandomEnemySpawnPosition.compare("bottom-right") == 0)
        {
            CreateRandomSpawn({GameObjects::CalculateXCoord(100), GameObjects::CalculateYCoord(100)}, {0, 0});
        }
    }
}

void Level_01::UpdateRandomEnemies()
{
    if (randomEnemySpawnTimer == 0)
        return;
    for (int i = 0; i < randomEnemies.size(); i++)
    {
        if (!randomEnemies[i].active)
        {
            return;
        }
        else
        {
            if (currentRandomEnemySpawnPosition.compare("top-left") == 0)
            {
                if (randomEnemies[i].position.x > randomEnemies[i].outOufMap.x || randomEnemies[i].position.y > randomEnemies[i].outOufMap.y)
                {
                    randomEnemies[i].active = false;
                    return;
                }
                randomEnemies[i].position.x += (randomEnemies[i].speed * 1.5) * GetFrameTime();
                randomEnemies[i].position.y += randomEnemies[i].speed * GetFrameTime();
            }
            else if (currentRandomEnemySpawnPosition.compare("top-right") == 0)
            {
                if (randomEnemies[i].position.x < randomEnemies[i].outOufMap.x || randomEnemies[i].position.y > randomEnemies[i].outOufMap.y)
                {
                    randomEnemies[i].active = false;
                    return;
                }
                randomEnemies[i].position.x -= (randomEnemies[i].speed * 1.5) * GetFrameTime();
                randomEnemies[i].position.y += randomEnemies[i].speed * GetFrameTime();
            }
            else if (currentRandomEnemySpawnPosition.compare("bottom-left") == 0)
            {
                if (randomEnemies[i].position.x > randomEnemies[i].outOufMap.x || randomEnemies[i].position.y < randomEnemies[i].outOufMap.y)
                {
                    randomEnemies[i].active = false;
                    return;
                }
                randomEnemies[i].position.x += (randomEnemies[i].speed * 1.5) * GetFrameTime();
                randomEnemies[i].position.y -= randomEnemies[i].speed * GetFrameTime();
            }
            else if (currentRandomEnemySpawnPosition.compare("bottom-right") == 0)
            {
                if (randomEnemies[i].position.x < randomEnemies[i].outOufMap.x || randomEnemies[i].position.y < randomEnemies[i].outOufMap.y)
                {
                    randomEnemies[i].active = false;
                    return;
                }
                randomEnemies[i].position.x -= (randomEnemies[i].speed * 1.5) * GetFrameTime();
                randomEnemies[i].position.y -= randomEnemies[i].speed * GetFrameTime();
            }
        }
    }
}

void Level_01::DrawRandomEnemies(Player &player)
{
    if (randomEnemySpawnTimer == 0)
    {
        return;
    }

    float frameWidth = (float)(randomEnemyTexture.width / 3); // Sprite one frame rectangle width
    float frameHeight = (float)(randomEnemyTexture.height);   // Sprite one frame rectangle height

    for (int i = 0; i < randomEnemies.size(); i++)
    {
        randomEnemies[i].frameCounter++;
        if (randomEnemies[i].frameCounter >= 5)
        {
            randomEnemies[i].frameCounter = 0;
            randomEnemies[i].currentFrame++;
        }

        // Hover and draw default enenmy movements
        if (randomEnemies[i].active && randomEnemies[i].health > 0)
        {
            Rectangle frameRec = {randomEnemies[i].position.x, randomEnemies[i].position.y, frameWidth, frameHeight};
            frameRec.x = frameWidth * randomEnemies[i].currentFrame;
            frameRec.y = frameHeight;
            randomEnemies[i].UpdateEnemyAttack(randomEnemies[i].position.x, randomEnemies[i].position.y, randomEnemyBulletTexture, 20, 11, 3);
            DrawTextureRec(randomEnemies[i].enemyTexture, frameRec, {randomEnemies[i].position.x, randomEnemies[i].position.y}, WHITE);
        }

        // Checking if enemy is hit
        if (randomEnemies[i].health > 0 && randomEnemies[i].active)
        {
            randomEnemies[i].isCircleHit(player.leftBullets, player.rightBullets, player.score);
        }

        // Enemy killed and removed, explosion
        if (randomEnemies[i].health <= 0 && !randomEnemies[i].active)
        {
            randomEnemies[i].EnemyExplosion(GameObjects::CalculateObjectSizeY(200.f), GameObjects::CalculateObjectSizeY(8.f));
        }

        // Remove random enemy from list when inactive/dead
        if (!randomEnemies[i].active && randomEnemies[i].enemyDebris.empty())
        {
            randomEnemies.erase(randomEnemies.begin() + i);
            return;
        }
    }
}

void Level_01::InitRandomEnemyBulletTexture()
{
    Image randomBulletImg = LoadImage("./media/randomSpawnBullet.png");
    ImageResize(&randomBulletImg, GameObjects::CalculateObjectSizeX(randomBulletImg.width), GameObjects::CalculateObjectSizeY(randomBulletImg.height));
    randomEnemyBulletTexture = LoadTextureFromImage(randomBulletImg);
    isRandomEnemyBulletTextureLoaded = true;
    UnloadImage(randomBulletImg);
}

void Level_01::InitRandomEnemyTexture()
{
    Image randomEnemyImg = LoadImage("./media/randomEnemy1.png");
    ImageResize(&randomEnemyImg, GameObjects::CalculateObjectSizeX(randomEnemyImg.width), GameObjects::CalculateObjectSizeY(randomEnemyImg.height));
    randomEnemyTexture = LoadTextureFromImage(randomEnemyImg);
    UnloadImage(randomEnemyImg);
}

void Level_01::ResetRandomEnemy(Enemy &randomEnemy)
{
    randomEnemy.health = 200;
    randomEnemy.active = true;
    randomEnemy.enemyTexture = randomEnemyTexture;
    randomEnemy.speed = 100;
    randomEnemy.scoreValue = 250;
    randomEnemy.frameCounter = 0;
    randomEnemy.currentFrame = 0;
}

// DEFAULT ENEMY
void Level_01::InitDefaultEnemyBulletTexture()
{
    Image defaultEnemyBulletImg = LoadImage("./media/bullet_enemy_0.png");
    ImageResize(&defaultEnemyBulletImg, GameObjects::CalculateObjectSizeX(defaultEnemyBulletImg.width), GameObjects::CalculateObjectSizeY(defaultEnemyBulletImg.height));
    Texture2D loadedDefaultenemyBulletTexture = LoadTextureFromImage(defaultEnemyBulletImg);
    UnloadImage(defaultEnemyBulletImg);
    defaultEnemyBulletTexture = loadedDefaultenemyBulletTexture;
}

void Level_01::DrawMultipleEnemies(std::vector<int> &xPositions, Player &player)
{
    if (defaultEnemies.size() <= 0)
    {
        defaultEnemyTexture = GameObjects::LoadDefaultEnemyTexture();
        InitDefaultEnemyBulletTexture();
    }
    for (int i = 0; i < 4; i++)
    {
        // First spawn,initiating 4 enemies
        if (defaultEnemies.size() < 4)
        {
            Enemy defEnemy;
            defEnemy.InitDefaultEnemyDefaults(xPositions[i], defaultEnemyTexture);
            defEnemy.ResetDefaultEnenmy();
            defaultEnemies.push_back(defEnemy);
        }

        // Activate new enemy
        if (!defaultEnemies[i].active && defaultEnemies[i].health >= 100)
            defaultEnemies[i].active = true;

        // Enemy killed and removed, explosion
        if (defaultEnemies[i].health <= 0 && !defaultEnemies[i].active)
        {
            defaultEnemies[i].EnemyExplosion(GameObjects::CalculateObjectSizeY(200.f), GameObjects::CalculateObjectSizeY(8.f));
            if (defaultEnemies[i].enemyDebris.empty())
            {
                defaultEnemies[i].ResetDefaultEnenmy();
            }
        }

        // Hover and draw default enenmy movements
        if (defaultEnemies[i].active && defaultEnemies[i].health > 0)
        {
            if (defaultEnemies[i].position.y <= 150)
                defaultEnemies[i].position.y += defaultEnemies[i].speed;
            else
                defaultEnemies[i].hover(GameObjects::CalculateByPixelsX(xPositions[i]));

            DrawTexture(defaultEnemies[i].enemyTexture, defaultEnemies[i].position.x, defaultEnemies[i].position.y, WHITE);
        }

        // Update enemy attack (draw and update bullet status)
        defaultEnemies[i].UpdateEnemyDefaultAttack(defaultEnemies[i].position.x, defaultEnemyBulletTexture);

        // Checking if enemies is hit
        if (defaultEnemies[i].health > 0 && defaultEnemies[i].active)
        {
            if (defaultEnemies[i].position.y >= 150)
            {
                defaultEnemies[i].isTriangleHit(player.leftBullets, player.rightBullets, player.score);
            }
        }
    }
}

void Level_01::UnloadMultipleEnemies()
{
    for (int i = 0; i < defaultEnemies.size(); i++)
    {

        defaultEnemies[i].UnloadEnemy();
        defaultEnemies[i].ResetDefaultEnenmy();
    }
}
//

// BOSS
void Level_01::SpawnBoss()
{
    boss.InitBoss(GameObjects::CalculateXCoord(100 / 2), 500, 2);
}

void Level_01::UpdateBoss()
{
}

void Level_01::isBossHit()
{
}
//
void Level_01::LevelComplete()
{
}

void Level_01::UnloadLevel1()
{
    UnloadTexture(randomEnemyTexture);
    UnloadTexture(defaultEnemyBulletTexture);
    UnloadTexture(defaultEnemyTexture);
    UnloadTexture(randomEnemyBulletTexture);

    isRandomEnemyTextureLoaded = false;
    isRandomEnemyBulletTextureLoaded = false;

    randomEnemies.clear();
    defaultEnemies.clear();
}
