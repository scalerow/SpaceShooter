#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include <raylib.h>

struct Debris
{
    Vector2 Velocity;
    Vector2 Position;
};

struct PlayerData 
{
    int health;
    int currentLevel;
    int playerNumber;
    char playerName[6 + 1] = "\0";
};

float CalculateXCoord(float x);
float CalculateYCoord(float y);
float CalculateByPixelsX(float x);
float CalculateByPixelsY(float y);
float CalculateObjectSizeX(float x);
float CalculateObjectSizeY(float y);

Texture2D LoadDefaultEnemyTexture();
Texture2D InitDefaultEnemyBulletTexture();

#endif