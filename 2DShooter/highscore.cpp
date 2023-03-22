#include "highscore.h"

HighScore::HighScore()
{
    
}

HighScore::~HighScore()
{
}

void HighScore::UpdateHighscores(int score)
{
    for(int i = 0; i <= highScores.size(); i++)
    {
        if(highScores.size() < 5 && !highscoreUpdated)
        {            
            highScores.push_back(score);
            std::sort(highScores.begin(), highScores.end());
            highscoreUpdated = true;
            newHighscoreEntry = true;
        }
        else if(highScores[i] < score && !highscoreUpdated)
        {
            highScores.push_back(score);
            std::sort(highScores.begin(), highScores.end());
            if(highScores.size() > 5) highScores.pop_back();
            highscoreUpdated = true;
            newHighscoreEntry = true;
        } 
        else 
        {
            highscoreUpdated = true;
            newHighscoreEntry =  false;
        }
    }
}

