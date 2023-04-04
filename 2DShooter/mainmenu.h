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
    //Background used for menu
    Texture2D menuTexture;
    Vector2 menuBackgroudPosition;
    //Color handling of buttons
    Color newGameButtonColor;
    Color loadButtonColor;
    Color exitButtonColor;
    Color settingsButtonColor;
    Color newGameBackButtonColor;
    Color newGameReadyButtonColor;
    //Used for buttonclick events
    Vector2 mousePoint;
    //MenuAction booleans
    bool shouldExit;
    bool isMenuActive;
    bool isNewGameActive;
    bool isLoadGameActive;
    //New game related
    char playerName[6 + 1] = "\0";  
    int letterCount = 0;
    std::vector<Vector4> inputLines;
    //Game saves related
    bool isNewPlayerAllowed;
    std::vector<PlayerData> playerData;


    MainMenu(float &width, float &height);
    ~MainMenu();
    void InitMenu();
    void InitNewGame();

    //MainMenu
    void DrawMainMenu();
    void LoadGameAction(Rectangle btnBounds);
    void NewGameAction(Rectangle btnBounds);
    void PlayAction(Rectangle btnBounds);
    void SettingsAction(Rectangle btnBounds);
    void ExitAction(Rectangle btnBounds);

    //LoadGameMenu
    void DrawLoadGameMenu();
    
    //NewGameMenu
    void DrawNewGameMenu();
    void NewPlayerName();
    void NewGameActions();
    void DrawOverwriteExisting();

    
    void UnloadMenu();
};

#endif
