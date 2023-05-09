#ifndef MAINMENU_H
#define MAINMENU_H

#include "home.h"
#include <raylib.h>
#include <string>
#include "gameobjects.h"
#include <vector>
#include <ctype.h>
#include "components.h"
#include <algorithm>
#include <cstring>

class MainMenu : public Home
{
protected:
    // PlayerDataRelated
    void OverwritePlayerDataInList(std::vector<GameObjects::PlayerData> &playerData, GameObjects::PlayerData &currentPlayer, int &selectedEntry);
    void UpdatePlayerDataList(std::vector<GameObjects::PlayerData> &playerData, GameObjects::PlayerData &currentPlayer);

private:
    std::vector<Components::ListObject> savedGamesList = {};
    Components::ListBox listBox;
    Components::ListObject overWriteSelected;

    void ReplaceSavedGameAction();
    int IncrementPlayerId();
    void ClearListData();
    void SetActivePlayer(int &selectedKey);

public:
    // Background used for menu
    Texture2D menuTexture;
    Vector2 menuBackgroudPosition;
    // Color handling of buttons
    Color newGameButtonColor;
    Color loadButtonColor;
    Color exitButtonColor;
    Color settingsButtonColor;
    Color newGameBackButtonColor;
    Color newGameReadyButtonColor;
    Color loadGameBackButtonColor;
    // Used for buttonclick events
    Vector2 mousePoint;
    // MenuAction booleans
    bool shouldExit;
    bool isMenuActive;
    bool isNewGameActive;
    bool isLoadSelectGameActive;
    // New game related
    GameObjects::PlayerData activePlayer;
    int letterCount = 0;
    std::vector<Vector4> inputLines;
    // Game saves related
    bool isNewPlayerAllowed = false;
    std::vector<GameObjects::PlayerData> playerData;

    MainMenu(float &width, float &height);
    ~MainMenu();
    void InitMenu();
    void InitNewGame();

    // MainMenu
    void DrawMainMenu();
    void LoadGameAction(Rectangle btnBounds);
    void NewGameAction(Rectangle btnBounds);
    void PlayAction(Rectangle btnBounds);
    void SettingsAction(Rectangle btnBounds);
    void ExitAction(Rectangle btnBounds);

    // LoadGameMenu
    void DrawLoadSelectGameMenu();
    void LoadSelectGameActions();
    void InitLoadSelectedGame();
    void UnloadLoadSelectGame();

    // NewGameMenu
    void DrawNewGameMenu();
    void NewPlayerName();
    void NewGameActions();
    void DrawOverwriteExisting();

    void UnloadMenu();
};

#endif
