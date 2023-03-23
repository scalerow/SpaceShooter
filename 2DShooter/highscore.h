#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <raylib.h>
#include <vector>
#include <algorithm>
#include "gameobjects.h"

class HighScore
{
private:
    void save();
    void load();
    void update();


public:
    bool newHighscoreEntry;
    bool highscoreUpdated;
    std::vector<int> highScores;

    HighScore();
    ~HighScore();
    void UpdateHighscores(int score);
};

#endif