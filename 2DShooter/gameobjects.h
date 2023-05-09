#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include <raylib.h>
#include <time.h>
#include <stdio.h>

namespace GameObjects
{
    struct ScreenSize
    {
        float width = 0;
        float height = 0;
    };

    struct Debris
    {
        Vector2 Velocity;
        Vector2 Position;
    };

    struct PlayerData
    {
        int health = 150;
        int currentLevel = 1;
        int playerId;
        char playerName[6 + 1] = "\0";
        char lastSaved[80];
    };

    void SetScreenSize(float width, float height);

    float CalculateXCoord(float x);
    float CalculateYCoord(float y);
    float CalculateByPixelsX(float x);
    float CalculateByPixelsY(float y);
    float CalculateObjectSizeX(float x);
    float CalculateObjectSizeY(float y);
    char *GetDateTimeNow();

    Texture2D LoadDefaultEnemyTexture();
    Texture2D InitDefaultEnemyBulletTexture();
}
#endif