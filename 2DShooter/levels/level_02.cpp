#include "level_02.h"

Level_02::Level_02()
{
}
Level_02::~Level_02()
{
}

void Level_02::InitLevel2()
{
    levelActive = true;
    Image backgroundImage = LoadImage("./media/level_2.png");
    background = LoadTextureFromImage(backgroundImage);
}

void Level_02::RenderBackground()
{
    DrawTexture(background, 0, 0, RAYWHITE);
}