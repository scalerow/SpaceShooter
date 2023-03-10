#include "gameobjects.h"

struct Debris debris;

// Both one percent and one pixel shouldnt be initialized everytime this runs

// For calculating X positions based on percentage
float CalculateXCoord(float x)
{
    float onePercent = (float)GetScreenWidth() / 100.f;

    return onePercent * x;
}

// For calculating Y positions based on percentage
float CalculateYCoord(float y)
{
    float onePercent = (float)GetScreenHeight() / 100.f;

    return onePercent * y;
}

// For calculating X positions based on pixels
float CalculateByPixelsX(float x)
{
    float onePixel = 100.f / (float)GetScreenWidth();

    return CalculateXCoord(onePixel * x);
}

// For calculating Y positions based on pixels
float CalculateByPixelsY(float x)
{
    float onePixel = 100.f / (float)GetScreenHeight();

    return CalculateYCoord(onePixel * x);
}

// For calculating width of objects scaled to selected resolution
float CalculateObjectSizeX(float x)
{
    // Scaling of object stops at 1920x1080
    float maxSize = 100.f / 1920.f;
    float scaling = maxSize * GetScreenWidth();

    return (x / 100) * scaling;
}

// For calculating height of objects scaled to selected resolution
float CalculateObjectSizeY(float y)
{
    // Scaling of object stops at 1920x1080
    float maxSize = 100.f / 1080.f;
    float scaling = maxSize * GetScreenHeight();

    return (y / 100) * scaling;
}
