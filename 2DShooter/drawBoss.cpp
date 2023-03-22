#include <raylib.h>

int test()
{
    Texture2D firstBoss = LoadTexture("media/boss_1.png");
    float frameWidth = (float)(firstBoss.width / 15); // Sprite one frame rectangle width
    float frameHeight = (float)(firstBoss.height);    // Sprite one frame rectangle height
    int currentFrame = 0;
    int framesCounter = 0;
    Rectangle frameRec = {1920 / 2, 1080 / 2, frameWidth, frameHeight};
    while (!WindowShouldClose())
    {

        framesCounter++;

        if (framesCounter > 2)
        {
            currentFrame++;

            if (currentFrame >= 15)
            {
                currentFrame = 0;
            }

            framesCounter = 0;
        }

        frameRec.x = frameWidth * currentFrame;
        frameRec.y = frameHeight;
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTextureRec(firstBoss, frameRec, {1920 / 2, 1080 / 2}, WHITE);
        EndDrawing();
        // DrawGame();
    }
}
