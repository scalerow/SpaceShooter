#include "highscore.h"

HighScore::HighScore()
{
}

HighScore::~HighScore()
{
}

void HighScore::UpdateHighscores(int score)
{
    for (int i = 0; i <= highScores.size(); i++)
    {
        if (highScores.size() < 5 && !highscoreUpdated)
        {
            highScores.push_back(score);
            std::sort(highScores.begin(), highScores.end(), std::greater<int>());
            highscoreUpdated = true;
            newHighscoreEntry = true;
            return;
        }
        else if (highScores[i] < score && !highscoreUpdated)
        {

            highScores.push_back(score);
            std::sort(highScores.begin(), highScores.end(), std::greater<int>());
            highScores.pop_back();

            highscoreUpdated = true;
            newHighscoreEntry = true;
            return;
        }
        else if (highScores.size() == i)
        {
            highscoreUpdated = true;
            newHighscoreEntry = false;
            return;
        }
    }
}
