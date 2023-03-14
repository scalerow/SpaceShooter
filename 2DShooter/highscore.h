#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <raylib.h>
#include <vector>
#include "gameobjects.h"

class HighScore
{
private:
   void save();
   void load();
   void update();

public:
    std::vector<int> highScore;

    HighScore();
    ~HighScore();
};

#endif