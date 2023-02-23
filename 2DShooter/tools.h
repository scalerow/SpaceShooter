#ifndef TOOLS_H
#define TOOLS_H

#include <raylib.h>
#include <vector>
#include "enemy.h"

using namespace std;

class Tools
{
private:
public:
    vector<Enemy> enemies;

    Tools();
    ~Tools();
    void CreateMultipleEnemies(int xPositions[4]);
};

#endif