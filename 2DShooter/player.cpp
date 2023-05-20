#include "player.h"

Player::Player()
{
    playerActive = false;
}

Player::~Player()
{
}

// Initialize the plane for the game
void Player::InitPlayer(float scrnHeight, float scrnWidth, GameObjects::PlayerData &activePlayer)
{

    Image planeImg = LoadImage("./media/space_plane_1.png");
    ImageResize(&planeImg, GameObjects::CalculateObjectSizeX(planeImg.width), GameObjects::CalculateObjectSizeY(planeImg.height));
    Vector2 planePosition = {scrnWidth / 2, GameObjects::CalculateYCoord(100 - 9.26f)};

    Image bulletImg = LoadImage("./media/bullet_0.png");
    ImageResize(&bulletImg, GameObjects::CalculateObjectSizeX(bulletImg.width), GameObjects::CalculateObjectSizeY(bulletImg.height));
    Texture2D bulletTexture = LoadTextureFromImage(bulletImg);

    playerBulletTexture = LoadTextureFromImage(bulletImg);
    playerTexture = LoadTextureFromImage(planeImg);
    position = planePosition;
    rotation = 0.00;
    specialAttackBulletCount = 10;
    gameOver = false;
    leftShotTimer = 0;
    rightShotTimer = 0;
    health = activePlayer.health;
    currentLevel = activePlayer.currentLevel;
    std::strcpy(name, activePlayer.playerName);
    score = 0;
    velocity = {400.f, 300.f};
    acceleration = {0.f, 0.f};
    playerActive = true;
    UnloadImage(planeImg);
    UnloadImage(bulletImg);
}

void Player::UpdateProgress(GameObjects::PlayerData currentPlayer)
{
    currentLevel = currentPlayer.currentLevel;
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

    if (IsKeyDown(KEY_RIGHT) && position.x <= flightArea.z - playerTexture.width)
    {
        if (acceleration.x < 2.f)
            acceleration.x += 0.02f;

        // position.x += 350.f * delta;
        velocity.x += acceleration.x * delta;
        position.x += velocity.x * delta;
    }
    if (IsKeyDown(KEY_LEFT) && position.x >= flightArea.x)
    {
        if (acceleration.x < 2.f)
            acceleration.x += 0.02f;

        velocity.x -= acceleration.x * delta;
        position.x -= velocity.x * delta;
        // position.x -= 350.f * delta;
    }
    else
    {
        if (acceleration.x > 0)
            acceleration.x -= 0.01f;
        else if (acceleration.x < 0)
            acceleration.x = 0.f;
    }
    if (IsKeyDown(KEY_DOWN) && position.y <= flightArea.w - GameObjects::CalculateObjectSizeY(100))
    {
        if (acceleration.y < 2.f)
            acceleration.y += 0.02f;
        // position.y -= 10 * sin((rotation + 270) * DEG2RAD);
        // position.x -= 10 * cos((rotation + 270) * DEG2RAD);
        velocity.y += acceleration.y * delta;
        position.y += velocity.y * delta;
        // position.y += 350.f * delta;
    }

    if (IsKeyDown(KEY_UP) && position.y >= flightArea.y)
    {
        if (acceleration.y < 2.f)
            acceleration.y += 0.02f;
        // position.y += 10 * sin((rotation + 270) * DEG2RAD);
        // position.x += 10 * cos((rotation + 270) * DEG2RAD);
        velocity.y -= acceleration.y * delta;
        position.y -= velocity.y * delta;
        // position.y -= 350.f * delta;
    }
    else
    {
        if (acceleration.y > 0)
            acceleration.y -= 0.01f;
        else if (acceleration.y < 0)
            acceleration.y = 0.f;
    }

    if (playerActive)
        DrawTextureV(playerTexture, position, WHITE);
}

void Player::EnemiesAttackingAction(std::vector<Enemy> &enemies)
{
    for (int i = 0; i < enemies.size(); i++)
    {
        isHit(enemies[i].enemyBullets);
        if (!playerActive)
        {
            leftBullets.clear();
            rightBullets.clear();
            enemies[i].ResetDefaultEnenmy();
            enemies[i].enemyBullets.clear();
        }
    }
}

void Player::isHit(std::vector<Bullet> &bullets)
{

    if (bullets.size() > 0 && playerActive)
    {
        int bulletTextureWidth = bullets[0].frameCount == 0 ? bullets[0].bulletTexture.width : bullets[0].bulletTexture.width / bullets[0].frameCount;
        Vector2 playerSize = {(float)playerTexture.width, (float)playerTexture.height};

        Vector2 playerMainTrianglePointOne = {position.x + GameObjects::CalculateObjectSizeX(4), position.y + GameObjects::CalculateObjectSizeY(61)};
        Vector2 playerMainTrianglePointTwo = {position.x + GameObjects::CalculateObjectSizeX(51), position.y + GameObjects::CalculateObjectSizeY(15)};
        Vector2 playerMainTrianglePointThree = {position.x + GameObjects::CalculateObjectSizeX(99), position.y + GameObjects::CalculateObjectSizeY(61)};

        Vector2 playerTipTrianglePointOne = {position.x + GameObjects::CalculateObjectSizeX(30), position.y + GameObjects::CalculateObjectSizeY(33)};
        Vector2 playerTipTrianglePointTwo = {position.x + GameObjects::CalculateObjectSizeX(51), position.y + GameObjects::CalculateObjectSizeY(0)};
        Vector2 playerTipTrianglePointThree = {position.x + GameObjects::CalculateObjectSizeX(74), position.y + GameObjects::CalculateObjectSizeY(33)};

        Rectangle playerLeftGun = {position.x, position.y + GameObjects::CalculateObjectSizeY(8), GameObjects::CalculateObjectSizeX(8), GameObjects::CalculateObjectSizeY(63)};
        Rectangle playerRightGun = {position.x + GameObjects::CalculateObjectSizeX(96), position.y + GameObjects::CalculateObjectSizeY(8), GameObjects::CalculateObjectSizeX(8), GameObjects::CalculateObjectSizeY(63)};

        Rectangle playerRect = {position.x, position.y - GameObjects::CalculateObjectSizeY(75), playerSize.x, playerSize.y};
        for (int x = 0; x < bullets.size(); x++)
        {
            Vector2 bulletPos = {(float)bullets[x].x, (float)bullets[x].y};
            Vector2 bulletSize = {(float)bulletTextureWidth, (float)bullets[x].bulletTexture.height};
            Rectangle bulletRect = {bulletPos.x, bulletPos.y, bulletSize.x, bulletSize.y};

            bool gunleftCol = CheckCollisionRecs(playerLeftGun, bulletRect);
            bool gunRightCol = CheckCollisionRecs(playerRightGun, bulletRect);
            bool leftCornerBulletPlayerTip = CheckCollisionPointTriangle(Vector2{bulletPos.x, bulletPos.y}, playerTipTrianglePointOne, playerTipTrianglePointTwo, playerTipTrianglePointThree);
            bool rightCornerBulletPlayerTip = CheckCollisionPointTriangle(Vector2{bulletPos.x + bulletSize.x, bulletPos.y + bulletSize.y}, playerTipTrianglePointOne, playerTipTrianglePointTwo, playerTipTrianglePointThree);
            bool leftCornerBulletPlayerMain = CheckCollisionPointTriangle(Vector2{bulletPos.x, bulletPos.y}, playerMainTrianglePointOne, playerMainTrianglePointTwo, playerMainTrianglePointThree);
            bool rightCornerBulletPlayerMain = CheckCollisionPointTriangle(Vector2{bulletPos.x + bulletSize.x, bulletPos.y + bulletSize.y}, playerMainTrianglePointOne, playerMainTrianglePointTwo, playerMainTrianglePointThree);

            if (gunleftCol || gunRightCol || leftCornerBulletPlayerMain || rightCornerBulletPlayerMain || leftCornerBulletPlayerTip || rightCornerBulletPlayerTip)
            {
                health -= bullets[x].bulletDamage;
                bullets[x].bulletActive = false;
                bullets.erase(bullets.begin() + x);

                for (int i = 3; i-- > 0;)
                {
                    if (i == 0)
                    {

                        DrawCircleGradient(bulletPos.x + GameObjects::CalculateObjectSizeX(5), bulletPos.y + GameObjects::CalculateObjectSizeY(10), GameObjects::CalculateObjectSizeY(10.f), Fade(RED, 0.6f), Fade(RED, 0.0f));
                        DrawCircleV({bulletPos.x + GameObjects::CalculateObjectSizeX(5), bulletPos.y + GameObjects::CalculateObjectSizeY(10.f)}, GameObjects::CalculateObjectSizeY(4.f), RED);
                    }
                    else
                    {
                        DrawCircleLines(bulletPos.x + GameObjects::CalculateObjectSizeX(4.f), bulletPos.y + GameObjects::CalculateObjectSizeY(9.f), GameObjects::CalculateObjectSizeY(i * 15), RED);
                        DrawCircleLines(bulletPos.x + GameObjects::CalculateObjectSizeX(5.f), bulletPos.y + GameObjects::CalculateObjectSizeY(10.f), GameObjects::CalculateObjectSizeY(i * 15), RED);
                    }
                }
                if (health <= 0)
                {
                    playerActive = false;
                    FillDebris(200);
                }
            }
        }
    }
    else if (health <= 0)
        PlayerExplosion(GameObjects::CalculateObjectSizeY(700.f), GameObjects::CalculateObjectSizeY(8.f));
}

void Player::UpdateLeftBullet()
{
    if (playerActive)
    {
        if (leftShotTimer < 10)
        {
            leftShotTimer++;
        }
        if (leftShotTimer >= 10)
        {
            Bullet bullet = {};
            bullet.bulletSpeed = 550.f;
            bullet.bulletTexture = playerBulletTexture;
            bullet.x = position.x + GameObjects::CalculateObjectSizeX(32.f);
            bullet.y = position.y;
            bullet.bulletActive = true;
            bullet.bulletDamage = 8;
            leftBullets.push_back(bullet);
            leftShotTimer = 0;
        }

        for (int i = 0; i < leftBullets.size(); i++)
        {
            if (leftBullets[i].bulletActive && !leftBullets[i].playerBulletOutOfScreen())
            {
                leftBullets[i].updatePlayerBullet();
                PlaySound(sound);
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
    if (playerActive)
    {
        if (rightShotTimer < 10)
        {
            rightShotTimer++;
        }
        if (rightShotTimer >= 10)
        {
            Bullet bullet = {};
            bullet.bulletSpeed = 550.f;
            bullet.bulletTexture = playerBulletTexture;
            bullet.x = position.x + GameObjects::CalculateObjectSizeX(62.f);
            bullet.y = position.y;
            bullet.bulletActive = true;
            bullet.bulletDamage = 8;
            rightBullets.push_back(bullet);
            rightShotTimer = 0;
        }

        for (int i = 0; i < rightBullets.size(); i++)
        {
            if (rightBullets[i].bulletActive && !rightBullets[i].playerBulletOutOfScreen())
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
        GameObjects::Debris &debri = playerDebris[i];
        DrawCircleGradient(debri.Position.x, debri.Position.y - 8.f, debrisSize, Fade({242, 229, 170, 255}, 0.6f), Fade({242, 229, 170, 255}, 0.0f));
        DrawCircle(debri.Position.x, debri.Position.y - 8.f, debrisSize / 4, {242, 229, 170, 255});
        debri.Position.x += debri.Velocity.x * GetFrameTime();
        debri.Position.y += debri.Velocity.y * GetFrameTime();

        bool xRange;
        bool yRange;

        xRange = debri.Position.x < position.x - explosionArea || debri.Position.x > position.x + explosionArea;
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
            GameObjects::Debris{
                Vector2{debriSpeed * std::cos(direction), debriSpeed * std::sin(direction)},
                Vector2{position.x + (playerTexture.width / 2), position.y + (playerTexture.height / 2)}});
    }
}

// Clear remenants of texture from memory
void Player::UnloadPlayer()
{
    leftBullets.clear();
    rightBullets.clear();
    UnloadTexture(playerTexture);
    UnloadTexture(playerBulletTexture);
}