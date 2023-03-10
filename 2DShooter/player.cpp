#include "player.h"


Player::Player()
{
    playerActive = false;
}

Player::~Player()
{
}

// Initialize the plane for the game
void Player::InitPlayer(float screenHeight, float screenWidth)
{

    Image planeImg = LoadImage("./media/space_plane_0.png");
    Vector2 planePosition = {screenWidth / 2, screenHeight - 100};

    Image bulletImg = LoadImage("./media/bullet_0.png");
    Texture2D bulletTexture = LoadTextureFromImage(bulletImg);

    playerBulletTexture = LoadTextureFromImage(bulletImg);
    playerTexture = LoadTextureFromImage(planeImg);
    position = planePosition;
    rotation = 0.00;
    speed = 8.f;
    specialAttackBulletCount = 10;
    gameOver = false;
    leftShotTimer = 0;
    rightShotTimer = 0;
    health = 150;
    score = 0;
    playerActive = true;
    UnloadImage(planeImg);
    UnloadImage(bulletImg);
}

// Update the planes position with keyboard keys
void Player::UpdatePlayer(float delta, Vector4 flightArea)
{
    // if (IsKeyDown(KEY_LEFT))
    // {
    //     rotation -= 4.f;
    // }
    // if (IsKeyDown(KEY_RIGHT))
    // {
    //     rotation += 4.f;
    // }

    if (IsKeyDown(KEY_RIGHT) && position.x <= flightArea.z - 100)
    {
        position.x += 350.f * delta;
    }
    if (IsKeyDown(KEY_LEFT) && position.x >= flightArea.x)
    {
        position.x -= 350.f * delta;
    }
    if (IsKeyDown(KEY_DOWN) && position.y <= flightArea.w - 100)
    {
        // position.y -= 10 * sin((rotation + 270) * DEG2RAD);
        // position.x -= 10 * cos((rotation + 270) * DEG2RAD);
        position.y += 350.f * delta;
    }

    if (IsKeyDown(KEY_UP) && position.y >= flightArea.y)
    {
        // position.y += 10 * sin((rotation + 270) * DEG2RAD);
        // position.x += 10 * cos((rotation + 270) * DEG2RAD);
        position.y -= 350.f * delta;
    }

    if(playerActive)
        DrawTextureV(playerTexture,position, WHITE);

}

void Player::isHit(std::vector<Bullet> &bullets)
{
    if (bullets.size() > 0 && playerActive)
    {
        Vector2 playerPos = {(float)position.x, (float)position.y};
        Vector2 playerSize = {(float)playerTexture.width, (float)playerTexture.height};

        Rectangle playerRect = {playerPos.x, playerPos.y - 75, playerSize.x, playerSize.y};
        for (int x = 0; x < bullets.size(); x++)
        {
            Vector2 bulletPos = {(float)bullets[x].x, (float)bullets[x].y};
            Vector2 bulletSize = {(float)bullets[x].bulletTexture.width, (float)bullets[x].bulletTexture.height};
            Rectangle bulletRect = {bulletPos.x, bulletPos.y, bulletSize.x, bulletSize.y};
            if (CheckCollisionRecs(playerRect, bulletRect))
            {

                health -= bullets[x].bulletDamage;
                bullets[x].bulletActive = false;
                bullets.erase(bullets.begin() + x);
                if(health <= 0)
                {
                    playerActive = false;
                    FillDebris(300);
                }
                    

            }
        }
    }
    else if (health <= 0)
        PlayerExplosion(700.f, 8.f);
}

void Player::UpdateLeftBullet()
{
    if(playerActive)
    {
        if (leftShotTimer < 15)
        {
            leftShotTimer++;
        }
        if (leftShotTimer >= 15)
        {
            Bullet bullet = {};
            bullet.bulletSpeed = 7.f;
            bullet.bulletTexture = playerBulletTexture;
            bullet.x = position.x + 0.5;
            bullet.y = position.y;
            bullet.bulletActive = true;
            leftBullets.push_back(bullet);
            leftShotTimer = 0;
        }

        for (int i = 0; i < leftBullets.size(); i++)
        {
            if (leftBullets[i].bulletActive && !leftBullets[i].playerBulletCollides())
            {
                leftBullets[i].updatePlayerBullet();
                DrawTextureV(leftBullets[i].bulletTexture, {leftBullets[i].x, leftBullets[i].y}, WHITE);
            }
            else
            {
                leftBullets.erase(leftBullets.begin() + i);
            }
        }
    }
}

void Player::UpdateRightBullet()
{
    if(playerActive)
    {
        if (rightShotTimer < 15)
        {
            rightShotTimer++;
        }
        if (rightShotTimer >= 15)
        {
            Bullet bullet = {};
            bullet.bulletSpeed = 7.f;
            bullet.bulletTexture = playerBulletTexture;
            bullet.x = position.x + 149.5;
            bullet.y = position.y;
            bullet.bulletActive = true;
            rightBullets.push_back(bullet);
            rightShotTimer = 0;
        }

        for (int i = 0; i < rightBullets.size(); i++)
        {
            if (rightBullets[i].bulletActive && !rightBullets[i].playerBulletCollides())
            {
                rightBullets[i].updatePlayerBullet();
                DrawTextureV(rightBullets[i].bulletTexture, {rightBullets[i].x, rightBullets[i].y}, WHITE);
            }
            else
            {
                rightBullets.erase(rightBullets.begin() + i);
            }
        }
    }
}

void Player::PlayerExplosion(float explosionArea, float debrisSize)
{

    float bloom = 8.f;
    for (int i = 0; i < playerDebris.size(); i++)
    {
        Debris &debri = playerDebris[i];
        DrawCircleGradient(debri.Position.x, debri.Position.y-8.f, debrisSize, Fade(SKYBLUE, 0.6f), Fade(SKYBLUE, 0.0f));
        DrawCircle(debri.Position.x, debri.Position.y - 8.f, debrisSize/4, SKYBLUE);
        debri.Position.x += debri.Velocity.x * GetFrameTime();
        debri.Position.y += debri.Velocity.y * GetFrameTime();

        bool xRange;
        bool yRange;
        
        xRange =  debri.Position.x < position.x - explosionArea || debri.Position.x > position.x + explosionArea;
        yRange = debri.Position.y < position.y - explosionArea || debri.Position.y > position.y + explosionArea;
                
        if (xRange || yRange)
        {
            playerDebris.erase(playerDebris.begin() + i);
        }
        if (playerDebris.empty())
        {
            gameOver = true;
        }
    }
}

void Player::FillDebris(int particleAmount)
{
    for (int i = 0; i < particleAmount; i++)
    {
        float debriSpeed = (float)GetRandomValue(50, 300);
        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_real_distribution<float> dist(0.0f, 2.0f * PI);
        float direction = dist(rng);

        playerDebris.push_back(
            Debris{
                Vector2{debriSpeed * std::cos(direction), debriSpeed * std::sin(direction)},
                Vector2{position.x + (playerTexture.width /2), position.y + (playerTexture.height / 2)}});
    }
}

// Clear remenants of texture from memory
void Player::UnloadPlayer()
{
    UnloadTexture(playerTexture);
    UnloadTexture(playerBulletTexture);
}