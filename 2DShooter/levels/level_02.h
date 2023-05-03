#ifndef LEVEL_02
#define LEVEL_02

#include <raylib.h>
#include "..\enemy.h"
#include "..\player.h"
#include "..\gameobjects.h"
#include <vector>

class Level_02
{
private:
    Texture2D background;

public:
    bool levelActive = false;

    Level_02();
    ~Level_02();

    void InitLevel2();
    void RenderBackground();
};

#endif
