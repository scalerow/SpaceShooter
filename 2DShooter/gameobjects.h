#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include <raylib.h>

struct Debris
{
    Vector2 Velocity;
    Vector2 Position;
};

float CalculateXCoord(float x);
float CalculateYCoord(float y);
float CalculateByPixelsX(float x);
float CalculateByPixelsY(float y);
float CalculateObjectSizeX(float x);
float CalculateObjectSizeY(float y);

#endif