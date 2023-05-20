#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "mainmenu.h"
#include "player.h"
#include "highscore.h"
#include "settings.h"

class Game : public MainMenu
{
private:
    bool isGameSaved;

public:
    int shotTimerRight;
    int shotTimerLeft;
    int enemyShotTimer;
    int enemyCounter;
    Texture2D gameTexture;
    Vector2 gameBackgroudPosition;
    Vector4 flightArea;
    bool isGameActive;
    bool paused;
    Rectangle resumeRec;
    Rectangle backRec;
    Color resumeColor;
    Color backColor;

    Game(float &widthP, float &heightP);
    virtual ~Game();

    void InitGame();
    void PauseGame();
    void DrawGameUI(int &currentHealth, int &totalHealth, int &score);
    void DrawPauseGame();
    void DrawGameOver(HighScore &highscores, Settings &settings, int &score);
    void DrawLevelComplete(HighScore &highscores, Settings &settings, int &score);
    void RenderBackground(bool menu = false);

    void UpdatePauseGame();

    void ResetGame();
    void UnloadGame();
};

#endif
