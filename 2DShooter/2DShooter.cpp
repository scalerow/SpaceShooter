#include <raylib.h>
#include <iostream>

#define PLAYER_HOR_SPD 350.0f
#define PLAYER_MAX_SHOTS 5

typedef struct PlanePlayer
{
    Vector2 position;
    float speed;
    bool canShoot;
    float health = 100.f;
    Texture2D planeTexture;
} PlanePlayer;

typedef struct BulletPlayer
{
    Vector2 position;
    float speed;
    float radius;
    bool active;
    Color color;
    float lifespawn;
} BulletPlayer;

typedef struct BulletPlayerRight
{
    Vector2 position;
    float speed;
    float radius;
    bool active;
    Color color;
    float lifespawn;
} BulletPlayerRight;

void UpdatePlane(PlanePlayer *player, float delta, int width, int height);
void UpdateLeftBullet(BulletPlayer (*bullet)[PLAYER_MAX_SHOTS], Vector2 position, float delta);
void UpdateRightBullet(BulletPlayerRight (*bullet)[PLAYER_MAX_SHOTS], Vector2 position, float delta);

int main(void)
{
    static BulletPlayer bullet[PLAYER_MAX_SHOTS] = {0};
    static BulletPlayerRight bulletRight[PLAYER_MAX_SHOTS] = {0};

    bool left;
    bool right;

    float screenWidth = 1024.f;
    float screenHeight = 1024.f;
    InitWindow(1024, 1024, "Ett program");

    Image background = LoadImage("../mymedia/2d_desert_sprite.png");
    ImageResize(&background, background.width, background.height);
    Texture2D texture = LoadTextureFromImage(background);
    UnloadImage(background);

    Image planeImg = LoadImage("../mymedia/plane_100_0.png");
    Vector2 planePosition = {screenWidth / 2, screenHeight / 2};
    PlanePlayer planePlayer = {0};
    planePlayer.planeTexture = LoadTextureFromImage(planeImg);
    planePlayer.position = planePosition;
    planePlayer.speed = 8.f;
    planePlayer.canShoot = true;
    UnloadImage(planeImg);

    // Starting positions of bullets
    Vector2 bulletStartPos = {planePosition.x + 16, planePosition.y + 4};
    Vector2 bulletRightStartPos = {planePosition.x + 80, planePosition.y + 4};
    //

    for (int i = 0; i < PLAYER_MAX_SHOTS; i++)
    {
        Vector2 bulletPosition = {bulletStartPos.x, bulletStartPos.y - 20};
        bullet[i].position = bulletPosition;
        bullet[i].speed = 1700.f;
        bullet[i].radius = 10;
        bullet[i].color = RED;
        bullet[i].active = false;
        bullet[i].lifespawn = 0;
    }

    for (int i = 0; i < PLAYER_MAX_SHOTS; i++)
    {
        Vector2 bulletPosition = {bulletRightStartPos.x, bulletRightStartPos.y - 20};
        bulletRight[i].speed = 1700.f;
        bulletRight[i].radius = 10;
        bulletRight[i].color = RED;
        bulletRight[i].active = false;
        bulletRight[i].lifespawn = 0;
    }

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        // Move player around
        UpdatePlane(&planePlayer, deltaTime, background.width, background.height);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(texture, 0, 0, RAYWHITE);
        DrawTexture(planePlayer.planeTexture, planePlayer.position.x, planePlayer.position.y, WHITE);

        UpdateLeftBullet(&bullet, planePlayer.position, deltaTime);
        UpdateRightBullet(&bulletRight, planePlayer.position, deltaTime);
        // DrawText("Dette er ett spill", screenWidth / 2, screenHeight / 2, 45, GREEN);
        EndDrawing();
    }
    UnloadTexture(planePlayer.planeTexture);
    UnloadTexture(texture);
    CloseWindow();

    return 0;
}

void UpdatePlane(PlanePlayer *player, float delta, int width, int height)
{
    if (IsKeyDown(KEY_RIGHT) && player->position.x <= width - 100)
        player->position.x += PLAYER_HOR_SPD * delta;
    if (IsKeyDown(KEY_LEFT) && player->position.x >= 0)
        player->position.x -= PLAYER_HOR_SPD * delta;
    if (IsKeyDown(KEY_DOWN) && player->position.y <= height - 100)
        player->position.y += PLAYER_HOR_SPD * delta;
    if (IsKeyDown(KEY_UP) && player->position.y >= 0)
        player->position.y -= PLAYER_HOR_SPD * delta;
}

void UpdateLeftBullet(BulletPlayer (*bullet)[PLAYER_MAX_SHOTS], Vector2 position, float delta)
{

    for (int i = 0; i < PLAYER_MAX_SHOTS; i++)
    {
        if (!bullet[i]->active)
        {
            bullet[i]->position = Vector2{position.x + 16, position.y};
            bullet[i]->active = true;
            break;
        }
    }

    for (int i = 0; i < PLAYER_MAX_SHOTS; i++)
    {
        if (bullet[i]->active)
        {
            bullet[i]->position.y -= bullet[i]->speed * delta;

            if (bullet[i]->position.y < 0)
                bullet[i]->active = false;

            if (bullet[i]->active)
                DrawRectangle(bullet[i]->position.x, bullet[i]->position.y, 5, 20, bullet[i]->color);
        }
    }
}

void UpdateRightBullet(BulletPlayerRight (*bullet)[PLAYER_MAX_SHOTS], Vector2 position, float delta)
{

    for (int i = 0; i < PLAYER_MAX_SHOTS; i++)
    {
        if (!bullet[i]->active)
        {
            bullet[i]->position = Vector2{position.x + 80, position.y};
            bullet[i]->active = true;
            break;
        }
    }

    for (int i = 0; i < PLAYER_MAX_SHOTS; i++)
    {
        if (bullet[i]->active)
        {
            bullet[i]->position.y -= bullet[i]->speed * delta;

            if (bullet[i]->position.y < 0)
                bullet[i]->active = false;

            if (bullet[i]->active)
                DrawRectangle(bullet[i]->position.x, bullet[i]->position.y, 5, 20, bullet[i]->color);
        }
    }
}