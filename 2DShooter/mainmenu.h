#ifndef MAINMENU_H
#define MAINMENU_H

#include "home.h"
#include <raylib.h>
#include <string>
#include "gameobjects.h"
#include <vector>
#include <ctype.h>

class MainMenu : public Home
{
private:
    /* data */
public:
    Texture2D menuTexture;
    Vector2 menuBackgroudPosition;
    Color newGameButtonColor;
    Color loadButtonColor;
    Color exitButtonColor;
    Color settingsButtonColor;
    bool shouldExit;
    bool isMenuActive;
    bool isNewGameActive;
    bool isLoadGameActive;
    Vector2 mousePoint;
    char playerName[6 + 1] = "\0";  
    int letterCount = 0;
    std::vector<Vector4> inputLines;


    MainMenu(float &width, float &height);
    ~MainMenu();
    void InitMenu();
    void InitNewGame();

    void DrawMainMenu();
    void DrawLoadGameMenu();
    void DrawNewGameMenu();

    void NewPlayerName();

    void LoadGameAction(Rectangle btnBounds);
    void NewGameAction(Rectangle btnBounds);
    void PlayAction(Rectangle btnBounds);
    void SettingsAction(Rectangle btnBounds);
    void ExitAction(Rectangle btnBounds);
    void UnloadMenu();
};

#endif
