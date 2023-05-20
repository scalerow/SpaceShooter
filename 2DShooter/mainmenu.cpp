#include "mainmenu.h"
#include <memory>

using namespace GameObjects;

MainMenu::MainMenu(float &width, float &height) : Home{width, height}
{
    isMenuActive = false;
    shouldExit = false;
    isNewGameActive = false;
    isLoadSelectGameActive = false;
}

MainMenu::~MainMenu()
{
}

///////////////////////////////////////////
///////// MainMenu related  ///////////////
///////////////////////////////////////////
#pragma region mainmenu

// Initialize mainmenu
void MainMenu::InitMenu()
{
    activePlayer = {};
    letterCount = 0;
    isMenuActive = true;
    Image background = LoadImage("./media/space_background_menu.png");
    ImageResize(&background, CalculateObjectSizeX(background.width), CalculateObjectSizeY(background.height));
    Texture2D backgroundTxr = LoadTextureFromImage(background);

    Vector2 backgroundPos = {0, 0};
    UnloadImage(background);

    newGameButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    loadButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    settingsButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    exitButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    newGameBackButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    newGameReadyButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    menuTexture = backgroundTxr;
    menuBackgroudPosition = {backgroundPos.x, backgroundPos.y};
}

void MainMenu::DrawMainMenu()
{
    // Play button
    Rectangle startButtonPos = {CalculateXCoord((100 / 2.f) - 13.f), CalculateYCoord(100 / 2.f), CalculateObjectSizeX(500), CalculateObjectSizeY(120)};
    // DrawRectangleLinesEx(startButtonPos, 10, playButtonColor);
    Vector2 startButtonTextPos = {50.f - 6.5f, 50.f + 1.3f};
    int newGameWidth = MeasureText("NEW GAME", CalculateObjectSizeY(96.f));
    Rectangle newGameButton = {CalculateXCoord(100.f / 2.f) - (CalculateObjectSizeX(newGameWidth) / 2), CalculateYCoord(100.f / 2.f), CalculateObjectSizeX(newGameWidth), CalculateObjectSizeY(96.f)};
    DrawText("NEW GAME", newGameButton.x, newGameButton.y, newGameButton.height, newGameButtonColor);
    // Rectangle newGameRec = {newGameButton.x - CalculateObjectSizeX(20), newGameButton.y - CalculateObjectSizeY(20) ,newGameButton.width + CalculateObjectSizeX(40), newGameButton.height + CalculateObjectSizeY(40)};
    // DrawRectangleLinesEx(newGameRec, 10, playButtonColor);
    NewGameAction(newGameButton);

    int loadGameWidth = MeasureText("LOAD GAME", CalculateObjectSizeY(96.f));
    Rectangle loadGameButton = {CalculateXCoord(100.f / 2.f) - (CalculateObjectSizeX(loadGameWidth) / 2), CalculateYCoord(100.f / 2.f) + CalculateObjectSizeY(115), CalculateObjectSizeX(loadGameWidth), CalculateObjectSizeY(96.f)};
    DrawText("LOAD GAME", loadGameButton.x, loadGameButton.y, loadGameButton.height, loadButtonColor);
    // Rectangle loadGameRec = {loadGameButton.x - CalculateObjectSizeX(20), loadGameButton.y - CalculateObjectSizeY(20) ,loadGameButton.width + CalculateObjectSizeX(40), loadGameButton.height + CalculateObjectSizeY(40)};
    // DrawRectangleLinesEx(loadGameRec, 10, playButtonColor);
    LoadGameAction(loadGameButton);

    // Settings button
    float settingsWidth = MeasureText("SETTINGS", CalculateObjectSizeY(72));
    Rectangle rectSettings = Rectangle{(screenWidth / 2.f) - (settingsWidth / 2), (screenHeight / 2.f) + CalculateYCoord(27.77f), settingsWidth, CalculateObjectSizeY(72.f)};
    Rectangle settingsHitbox = Rectangle{rectSettings.x, rectSettings.y, rectSettings.width, rectSettings.height};
    DrawText("SETTINGS", rectSettings.x, rectSettings.y, CalculateObjectSizeY(72), settingsButtonColor);
    SettingsAction(settingsHitbox);
#ifndef PLATFORM_WEB
    // Exit button
    float exitWidth = MeasureText("EXIT", CalculateObjectSizeY(72));
    Rectangle rectExit = Rectangle{(screenWidth / 2.f) - (exitWidth / 2), (screenHeight / 2.f) + CalculateYCoord(37.03f), exitWidth, CalculateObjectSizeY(72)};
    Rectangle exitHitbox = Rectangle{rectExit.x, rectExit.y, rectExit.width, rectExit.height};
    DrawText("EXIT", rectExit.x, rectExit.y, CalculateObjectSizeY(72), exitButtonColor);
    ExitAction(exitHitbox);
#endif
    Rectangle menuRec = {loadGameButton.x - CalculateObjectSizeX(40), newGameButton.y - CalculateObjectSizeY(40), loadGameButton.width + CalculateObjectSizeX(80), CalculateObjectSizeY(550.f)};
    DrawRectangleLinesEx(menuRec, 10.f, GREEN);
}

#pragma endregion

///////////////////////////////////////////
///////// MainMenu actions  ///////////////
///////////////////////////////////////////

#pragma region mainmenu_actions

// Initialize the playbutton and its actions
void MainMenu::NewGameAction(Rectangle btnBounds)
{
    mousePoint = GetMousePosition();

    // Check button state
    if (CheckCollisionPointRec(mousePoint, btnBounds))
    {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            Vector4 inputStart = {CalculateXCoord(100 / 2) - CalculateObjectSizeX(300), CalculateYCoord(100 / 2) + CalculateObjectSizeY(80), CalculateXCoord(100 / 2) - CalculateObjectSizeX(210), CalculateYCoord(100 / 2) + CalculateObjectSizeY(80)};
            inputLines.push_back(inputStart);
            newGameButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
            isMenuActive = false;
            for (int i = 0; i <= 6; i++)
            {
                activePlayer.playerName[i] = '\0';
            }
            NewGame();
        }
        else
        {
            newGameButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        }
    }
    else
    {
        newGameButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    }
}

// Initialize the playbutton and its actions
void MainMenu::LoadGameAction(Rectangle btnBounds)
{
    mousePoint = GetMousePosition();

    if (playerData.size() != 0)
    {
        // Check button state
        if (CheckCollisionPointRec(mousePoint, btnBounds))
        {
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                loadButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
                isMenuActive = false;
                LoadSelectGame();
            }
            else
            {
                loadButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
            }
        }
        else
        {
            loadButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
        }
    }
    else
    {
        loadButtonColor = loadButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGRAY);
    }
}

// Initialize the playbutton and its actions
void MainMenu::PlayAction(Rectangle btnBounds)
{
    mousePoint = GetMousePosition();

    // Check button state
    if (CheckCollisionPointRec(mousePoint, btnBounds))
    {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            newGameButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        else
        {
            newGameButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            isMenuActive = false;
            LoadGame();
        }
    }
    else
    {
        newGameButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    }
}

void MainMenu::SettingsAction(Rectangle btnBounds)
{
    mousePoint = GetMousePosition();

    // Check button state
    if (CheckCollisionPointRec(mousePoint, btnBounds))
    {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            settingsButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
            isMenuActive = false;
            LoadSettings();
        }
        else
        {
            settingsButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        }
    }
    else
    {
        settingsButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    }
}

void MainMenu::ExitAction(Rectangle btnBounds)
{
    mousePoint = GetMousePosition();
    // Check button state
    if (CheckCollisionPointRec(mousePoint, btnBounds))
    {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            exitButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        else
        {
            exitButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            shouldExit = true;
        }
    }
    else
    {
        exitButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    }
}
#pragma endregion

///////////////////////////////////////////
///////// New Game related  ///////////////
///////////////////////////////////////////
#pragma region new_game

// Init new game menu
void MainMenu::InitNewGame()
{
    isNewGameActive = true;
    isNewPlayerAllowed = true;
}

// This should be made into a reusable component, to utilize it in arcade mode when getting a highscore
void MainMenu::DrawNewGameMenu()
{
    if (!isNewPlayerAllowed)
    {
        DrawOverwriteExisting();
    }
    else
    {

        int enterNameWidth = MeasureText("ENTER NAME:", CalculateObjectSizeY(120.f));
        DrawText("ENTER NAME:", CalculateXCoord(100 / 2) - CalculateObjectSizeX(enterNameWidth / 2), CalculateYCoord(100 / 8), CalculateObjectSizeY(120.f), GREEN);
        int measureNameWidth = MeasureText(activePlayer.playerName, CalculateObjectSizeY(96));

        DrawRectangleLinesEx({CalculateObjectSizeX(inputLines[0].x) - CalculateObjectSizeX(50), CalculateYCoord(100 / 2) - CalculateObjectSizeY(50), CalculateObjectSizeX(700), CalculateObjectSizeY(196)}, 10, GREEN);
        DrawTextEx(GetFontDefault(), activePlayer.playerName, {CalculateObjectSizeX(inputLines[0].x) + CalculateObjectSizeX(15), CalculateYCoord(100 / 2)}, CalculateObjectSizeY(96.f), CalculateObjectSizeX(45.f), GREEN);
        for (int i = 0; i < 6; i++)
        {
            if (inputLines.size() <= 6 && i != 0)
            {
                Vector4 inputLine;
                inputLine.x = inputLines[i - 1].x + CalculateObjectSizeX(100);
                inputLine.z = inputLines[i - 1].z + CalculateObjectSizeX(100);
                inputLine.y = inputLines[i - 1].y;
                inputLine.w = inputLines[i - 1].w;
                inputLines.push_back(inputLine);
            }

            if (!std::isalpha(activePlayer.playerName[i]))
            {
                DrawLineEx({CalculateObjectSizeX(inputLines[i].x), CalculateObjectSizeY(inputLines[i].y)}, {CalculateObjectSizeX(inputLines[i].z), CalculateObjectSizeY(inputLines[i].w)}, 10, GREEN);
            }
        }

        int readyStringWidth = MeasureText("READY", CalculateObjectSizeY(96));

        // ReadyButton
        DrawText("READY", CalculateXCoord((100 / 4) * 3) - readyStringWidth, CalculateYCoord((100 / 8) * 7), CalculateObjectSizeY(96), newGameReadyButtonColor);

        // BackButton
        DrawText("BACK", CalculateXCoord(100 / 4), CalculateYCoord((100 / 8) * 7), CalculateObjectSizeY(96), newGameBackButtonColor);
    }
}

void MainMenu::NewGameActions()
{
    mousePoint = GetMousePosition();

    int backStringWidth = MeasureText("BACK", CalculateObjectSizeY(96));
    Rectangle backRec = {CalculateXCoord(100 / 4), CalculateYCoord((100 / 8) * 7), (float)backStringWidth, CalculateObjectSizeY(96)};

    int readyStringWidth = MeasureText("READY", CalculateObjectSizeY(96));
    Rectangle readyRec = {CalculateXCoord((100 / 4) * 3) - (float)readyStringWidth, CalculateYCoord((100 / 8) * 7), (float)readyStringWidth, CalculateObjectSizeY(96)};

    if (!isNewPlayerAllowed)
    {
        for (int i = 0; i < listBox.data.size(); i++)
        {
            if (listBox.data[i].eventType.click)
            {
                overWriteSelected = listBox.data[i];
                ReplaceSavedGameAction();
            }
        }
    }

    // KEYBOARD ACTIONS
    // BACK BUTTON
    if (IsKeyReleased(KEY_ESCAPE))
    {
        newGameBackButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        if (isNewPlayerAllowed)
        {
            // Returns to mainmenu unless "Overwrite save" popup is active
            LoadMenu();
        }
        else
        {
            // Closes "Overwrite save" popup
            isNewPlayerAllowed = true;
        }
    }
    // READY BUTTON
    if (IsKeyReleased(KEY_ENTER))
    {
        newGameReadyButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        if (playerData.size() == 5) // == 5
        {
            isNewPlayerAllowed = false;
        }
        else
        {
            std::strcpy(activePlayer.lastSaved, GetDateTimeNow());
            if (playerData.size() == 0)
            {
                activePlayer.playerId = 0;
            }
            else
            {
                activePlayer.playerId = IncrementPlayerId();
            }
            ClearListData();
            playerData.push_back(activePlayer);
            LoadGame();
        }
    }

    // MOUSE ACTIONS
    // BACK BUTTON
    if (CheckCollisionPointRec(mousePoint, backRec))
    {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            // Back to mainmenu
            newGameBackButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
            LoadMenu();
        }
        else
        {
            // Sets hovercolor
            newGameBackButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        }
    }
    else
    {
        newGameBackButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    }

    // READY BUTTON
    if (CheckCollisionPointRec(mousePoint, readyRec))
    {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            newGameReadyButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
            if (playerData.size() == 5) // == 5
            {
                isNewPlayerAllowed = false;
            }
            else
            {
                std::strcpy(activePlayer.lastSaved, GetDateTimeNow());
                if (playerData.size() == 0)
                {
                    activePlayer.playerId = 0;
                }
                else
                {
                    activePlayer.playerId = IncrementPlayerId();
                }
                ClearListData();
                playerData.push_back(activePlayer);
                LoadGame();
            }
        }
        else
        {
            // Sets hovercolor
            newGameReadyButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        }
    }
    else
    {
        newGameReadyButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    }
}

void MainMenu::DrawOverwriteExisting()
{

    DrawRectangle(CalculateXCoord(100 / 4), CalculateYCoord(100 / 4), CalculateXCoord(100 / 2), CalculateYCoord(100 / 2), BLACK);
    DrawRectangleLines(CalculateXCoord(100 / 4), CalculateYCoord(100 / 4), CalculateXCoord(100 / 2), CalculateYCoord(100 / 2), RED);
    int headerStringWidth = MeasureText("You have five saved games", CalculateObjectSizeY(48));
    int headerSecondLineWidth = MeasureText("please remove one to continue", CalculateObjectSizeY(48));
    DrawText("You have five saved games", CalculateXCoord(100 / 2) - (headerStringWidth / 2), CalculateYCoord(100 / 4), CalculateObjectSizeY(48), RED);
    DrawText("please remove one to continue", CalculateXCoord(100 / 2) - (headerSecondLineWidth / 2), CalculateYCoord(100 / 4) + CalculateObjectSizeY(55), CalculateObjectSizeY(48), RED);
    DrawLineEx({CalculateXCoord((100 / 32) * 9), CalculateYCoord(100 / 4) + CalculateObjectSizeY(110)}, {CalculateXCoord((100 / 32) * 24), CalculateYCoord(100 / 4) + CalculateObjectSizeY(110)}, CalculateObjectSizeY(5), RED);
    for (int i = 0; savedGamesList.size() < playerData.size() && playerData.size(); i++)
    {
        if (savedGamesList.size() < playerData.size())
        {
            Components::ListObject overwriteItem;
            overwriteItem.key = playerData[i].playerId;
            std::string playerName = playerData[i].playerName;
            overwriteItem.value = playerName + "  " + playerData[i].lastSaved;
            savedGamesList.push_back(overwriteItem);
        }
        if (savedGamesList.size() == playerData.size())
        {
            listBox = Components::ListBox(savedGamesList, CalculateObjectSizeX((screenWidth / 2) - 50), CalculateObjectSizeY(48), {CalculateXCoord((100 / 8) * 2.2), CalculateYCoord(100 / 2.5)}, true);
            listBox.outlineColor = BLANK;
            listBox.textColor = RED;
            listBox.textActionColor = CLITERAL(Color){140, 0, 9, 255};
            listBox.ListBoxInitialize();
        }
    }

    if (playerData.size() == listBox.data.size() && playerData.size() != 0)
    {
        listBox.HandleListBox();
    }
}

void MainMenu::ReplaceSavedGameAction()
{

    activePlayer.playerId = IncrementPlayerId();
    std::strcpy(activePlayer.lastSaved, GetDateTimeNow());
    // Find playerData with the same playerId as the clicked item in list
    OverwritePlayerDataInList(playerData, activePlayer, overWriteSelected.key);
    isNewPlayerAllowed = true;
    savedGamesList = {};
    listBox = {};
    LoadGame();
}

void MainMenu::NewPlayerName()
{
    int key = GetCharPressed();

    // Check if more characters have been pressed on the same frame
    while (key > 0)
    {
        // NOTE: Only allow keys in range [32..125]
        if ((key >= 32) && (key <= 125) && (letterCount < 6))
        {
            activePlayer.playerName[letterCount] = (char)key;
            activePlayer.playerName[letterCount + 1] = '\0'; // Add null terminator at the end of the string.
            letterCount++;
        }

        key = GetCharPressed(); // Check next character in the queue
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        letterCount--;
        if (letterCount < 0)
            letterCount = 0;
        activePlayer.playerName[letterCount] = '\0';
    }
}
#pragma endregion

///////////////////////////////////////////
///////// Load Game related  //////////////
///////////////////////////////////////////
#pragma region load_game

void MainMenu::InitLoadSelectedGame()
{
    loadGameBackButtonColor = GREEN;
    if (savedGamesList.size() < playerData.size())
    {
        for (int i = 0; i < playerData.size(); i++)
        {
            Components::ListObject obj;
            obj.key = playerData[i].playerId;
            std::string playerName = playerData[i].playerName;
            obj.value = playerName + "  " + playerData[i].lastSaved;
            savedGamesList.push_back(obj);
        }
    }
    listBox = Components::ListBox(savedGamesList, CalculateXCoord(100 / 2), CalculateObjectSizeY(48), {CalculateXCoord(100 / 4), CalculateYCoord((100 / 5) * 2)}, true);
    listBox.fillColor = BLACK;
    isLoadSelectGameActive = true;
}

void MainMenu::DrawLoadSelectGameMenu()
{
    // Alternative rectangle around everything
    // Rectangle rect = {CalculateXCoord((100 / 8) * 1.2), CalculateYCoord(100 / 16), CalculateXCoord((100 / 8) * 6), CalculateYCoord((100 / 16) * 15)};
    //  DrawRectangleRec(rect, BLACK);
    // DrawRectangleLinesEx(rect, 10, GREEN);

    int headerTextWidth = MeasureText("Load Game", CalculateObjectSizeY(120));
    DrawText("Load Game", CalculateXCoord(100 / 2) - (headerTextWidth / 2), CalculateYCoord(100 / 8), CalculateObjectSizeY(120), GREEN);

    // List
    listBox.HandleListBox();

    // BackButton
    int backWidth = MeasureText("BACK", CalculateObjectSizeY(96));
    DrawText("BACK", CalculateXCoord(100 / 2) - (backWidth / 2), CalculateYCoord((100 / 8) * 7), CalculateObjectSizeY(96), loadGameBackButtonColor);
}

void MainMenu::LoadSelectGameActions()
{
    mousePoint = GetMousePosition();
    // KEYBOARD ACTIONS
    // BACK BUTTON
    if (IsKeyReleased(KEY_ESCAPE))
    {
        loadGameBackButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        UnloadLoadSelectGame();
        LoadMenu();
    }

    int backWidth = MeasureText("BACK", CalculateObjectSizeY(96));
    // MOUSE ACTIONS
    // BACK BUTTON
    Rectangle backHitBox = {CalculateXCoord(100 / 2) - (backWidth / 2), CalculateYCoord((100 / 8) * 7), (float)backWidth, CalculateObjectSizeY(96)};
    if (CheckCollisionPointRec(mousePoint, backHitBox))
    {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            UnloadLoadSelectGame();
            loadGameBackButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
            LoadMenu();
        }
        else
        {
            // Sets hovercolor
            loadGameBackButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        }
    }
    else
    {
        loadGameBackButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    }

    for (int i = 0; i < listBox.data.size(); i++)
    {
        if (listBox.data[i].eventType.click)
        {
            SetActivePlayer(listBox.data[i].key);
            UnloadLoadSelectGame();
            LoadGame();
        }
    }
}

void MainMenu::UnloadLoadSelectGame()
{
    isLoadSelectGameActive = false;
    ClearListData();
}

#pragma endregion

///////////////////////////////////////////
/////////Tools for submenues///////////////
///////////////////////////////////////////

#pragma region sumenu_tools

void MainMenu::OverwritePlayerDataInList(std::vector<PlayerData> &playerData, PlayerData &currentPlayer, int &selectedEntry)
{
    auto matchPlayer = std::find_if(playerData.begin(), playerData.end(), [&](const PlayerData &obj)
                                    { return obj.playerId == selectedEntry; });

    // If theres a match, replace the player with the newly created player
    if (matchPlayer != playerData.end())
    {
        matchPlayer->currentLevel = currentPlayer.currentLevel;
        matchPlayer->health = currentPlayer.health;
        matchPlayer->playerId = currentPlayer.playerId;
        std::strcpy(matchPlayer->lastSaved, currentPlayer.lastSaved);
        std::strcpy(matchPlayer->playerName, currentPlayer.playerName);
    }
}

// Update entry of Playerdatas
void MainMenu::UpdatePlayerDataList(std::vector<PlayerData> &playerData, PlayerData &currentPlayer)
{
    auto matchPlayer = std::find_if(playerData.begin(), playerData.end(), [&](const PlayerData &obj)
                                    { return obj.playerId == currentPlayer.playerId; });

    // If theres a match, replace the player with the newly created player
    if (matchPlayer != playerData.end())
    {
        matchPlayer->currentLevel = currentPlayer.currentLevel;
        matchPlayer->health = currentPlayer.health;
        matchPlayer->playerId = currentPlayer.playerId;
        std::strcpy(matchPlayer->playerName, currentPlayer.playerName);
    }
}

// Select active player from playerData
void MainMenu::SetActivePlayer(int &selectedKey)
{
    auto matchPlayer = std::find_if(playerData.begin(), playerData.end(), [&](const PlayerData &obj)
                                    { return obj.playerId == selectedKey; });

    // If theres a match, replace the player with the newly created player
    if (matchPlayer != playerData.end())
    {
        activePlayer.currentLevel = matchPlayer->currentLevel;
        activePlayer.health = matchPlayer->health;
        activePlayer.playerId = matchPlayer->playerId;
        std::strcpy(activePlayer.lastSaved, matchPlayer->lastSaved);
        std::strcpy(activePlayer.playerName, matchPlayer->playerName);
    }
}

// Sorting in asc order based on int prop in ListObject
int MainMenu::IncrementPlayerId()
{
    std::sort(playerData.begin(), playerData.end(), [](const PlayerData &a, const PlayerData &b)
              { return a.playerId < b.playerId; });
    int newPlayerId = playerData[playerData.size() - 1].playerId + 1;

    return newPlayerId;
}

void MainMenu::ClearListData()
{
    savedGamesList = {};
    listBox = {};
}

#pragma endregion

// Clear remenants of texture from memory
void MainMenu::UnloadMenu()
{
    UnloadTexture(menuTexture);
}