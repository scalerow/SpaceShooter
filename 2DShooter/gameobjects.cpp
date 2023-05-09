#include "gameobjects.h"

struct GameObjects::Debris debris;
struct GameObjects::PlayerData playerData;
struct GameObjects::ScreenSize screenSize;

void GameObjects::SetScreenSize(float width, float height)
{
    screenSize.height = height;
    screenSize.width = width;
}

// Both one percent and one pixel shouldnt be initialized everytime this runs
// For calculating X positions based on percentage
float GameObjects::CalculateXCoord(float x)
{
    float onePercent = screenSize.width / 100.f;

    return onePercent * x;
}

// For calculating Y positions based on percentage
float GameObjects::CalculateYCoord(float y)
{
    float onePercent = screenSize.height / 100.f;

    return onePercent * y;
}

// For calculating X positions based on pixels
float GameObjects::CalculateByPixelsX(float x)
{
    float onePixel = 100.f / screenSize.width;

    return CalculateXCoord(onePixel * x);
}

// For calculating Y positions based on pixels
float GameObjects::CalculateByPixelsY(float x)
{
    float onePixel = 100.f / screenSize.height;

    return CalculateYCoord(onePixel * x);
}

// For calculating width of objects scaled to selected resolution
float GameObjects::CalculateObjectSizeX(float x)
{
    // Scaling of object stops at 1920x1080
    float maxSize = 100.f / 1920.f;
    float scaling = maxSize * screenSize.width;

    return (x / 100) * scaling;
}

// For calculating height of objects scaled to selected resolution
float GameObjects::CalculateObjectSizeY(float y)
{
    // Scaling of object stops at 1920x1080
    float maxSize = 100.f / 1080.f;
    float scaling = maxSize * screenSize.height;

    return (y / 100) * scaling;
}

char *GameObjects::GetDateTimeNow()
{
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, 80, "%x %X", timeinfo);
    puts(buffer);

    return buffer;
}

Texture2D GameObjects::LoadDefaultEnemyTexture()
{
    Image defaultEnemyImg = LoadImage("./media/default_enemy_0.png");
    ImageResize(&defaultEnemyImg, CalculateObjectSizeX(defaultEnemyImg.width), CalculateObjectSizeY(defaultEnemyImg.height));
    Texture2D text = LoadTextureFromImage(defaultEnemyImg);
    UnloadImage(defaultEnemyImg);

    return text;
}
