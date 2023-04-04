#include "mainmenu.h"

MainMenu::MainMenu(float &width, float &height) : Home{width, height}
{
    isMenuActive = false;
    shouldExit = false;
    isNewGameActive = false;
    isLoadGameActive = false;
}

MainMenu::~MainMenu()
{
}

// Initialize mainmenu
void MainMenu::InitMenu()
{
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

void MainMenu::InitNewGame() 
{
    isNewGameActive = true;
    isNewPlayerAllowed = true;
}

void MainMenu::DrawMainMenu()
{
    // Play button
    Rectangle startButtonPos = {CalculateXCoord((100 / 2.f) - 13.f), CalculateYCoord(100 / 2.f), CalculateObjectSizeX(500), CalculateObjectSizeY(120)};
    //DrawRectangleLinesEx(startButtonPos, 10, playButtonColor);
    Vector2 startButtonTextPos = {50.f - 6.5f, 50.f + 1.3f};
    int newGameWidth = MeasureText("NEW GAME", CalculateObjectSizeY(96.f));
    Rectangle newGameButton = {CalculateXCoord(100.f / 2.f) - (CalculateObjectSizeX(newGameWidth)/2), CalculateYCoord(100.f / 2.f) , CalculateObjectSizeX(newGameWidth), CalculateObjectSizeY(96.f)};
    DrawText("NEW GAME", newGameButton.x, newGameButton.y, newGameButton.height, newGameButtonColor);
    // Rectangle newGameRec = {newGameButton.x - CalculateObjectSizeX(20), newGameButton.y - CalculateObjectSizeY(20) ,newGameButton.width + CalculateObjectSizeX(40), newGameButton.height + CalculateObjectSizeY(40)};
    // DrawRectangleLinesEx(newGameRec, 10, playButtonColor);
    NewGameAction(newGameButton);

    int loadGameWidth = MeasureText("LOAD GAME", CalculateObjectSizeY(96.f));
    Rectangle loadGameButton = {CalculateXCoord(100.f / 2.f) - (CalculateObjectSizeX(loadGameWidth)/2), CalculateYCoord(100.f / 2.f) + CalculateObjectSizeY(115), CalculateObjectSizeX(loadGameWidth), CalculateObjectSizeY(96.f)};
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

void MainMenu::DrawNewGameMenu() 
{
    if(!isNewPlayerAllowed)
    {
        DrawOverwriteExisting();
    }
    else 
    {

        int enterNameWidth = MeasureText("ENTER NAME:", CalculateObjectSizeY(120.f));
        DrawText("ENTER NAME:",CalculateXCoord(100/2) - CalculateObjectSizeX(enterNameWidth/2), CalculateYCoord(100/8), CalculateObjectSizeY(120.f), GREEN);
        int measureNameWidth = MeasureText(playerName, CalculateObjectSizeY(96));

        DrawRectangleLinesEx({CalculateObjectSizeX(inputLines[0].x - 50), CalculateYCoord(100/2) - CalculateObjectSizeY(50), CalculateObjectSizeX(700), CalculateObjectSizeY(196)}, 10, GREEN);    
        DrawTextEx(GetFontDefault(), playerName, {CalculateObjectSizeX(inputLines[0].x + 15), CalculateYCoord(100/2)}, CalculateObjectSizeY(96.f),CalculateObjectSizeX(45.f), GREEN);
        for(int i = 0; i < 6; i++)
        {
            if(inputLines.size() <= 6 && i != 0)
            {
                Vector4 inputLine;
                inputLine.x = inputLines[i-1].x + CalculateObjectSizeX(100);
                inputLine.z = inputLines[i-1].z + CalculateObjectSizeX(100);
                inputLine.y = inputLines[i-1].y;
                inputLine.w = inputLines[i-1].w;
                inputLines.push_back(inputLine);
            }

            if(!std::isalpha(playerName[i]))
            {
                DrawLineEx({CalculateObjectSizeX(inputLines[i].x), CalculateObjectSizeY(inputLines[i].y)}, {CalculateObjectSizeX(inputLines[i].z), CalculateObjectSizeY(inputLines[i].w)}, 10, GREEN);
            }
        }

        int readyStringWidth = MeasureText("READY", CalculateObjectSizeY(96));

        //ReadyButton
        DrawText("READY", CalculateXCoord((100/4) * 3) - readyStringWidth, CalculateYCoord((100/8) * 7), CalculateObjectSizeY(96), newGameReadyButtonColor);

        //BackButton
        DrawText("BACK", CalculateXCoord(100/4), CalculateYCoord((100/8) * 7), CalculateObjectSizeY(96), newGameBackButtonColor);
    }
}

void MainMenu::NewGameActions()
{   
    mousePoint = GetMousePosition();

    int backStringWidth = MeasureText("BACK", CalculateObjectSizeY(96));
    Rectangle backRec = {CalculateXCoord(100/4), CalculateYCoord((100/8) * 7), (float)backStringWidth, CalculateObjectSizeY(96)};

    int readyStringWidth = MeasureText("READY", CalculateObjectSizeY(96));
    Rectangle readyRec = {CalculateXCoord((100/4) * 3) - (float)readyStringWidth, CalculateYCoord((100/8) * 7), (float)readyStringWidth, CalculateObjectSizeY(96)};

    if(CheckCollisionPointRec(mousePoint, backRec))
    {
         if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            newGameBackButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
            LoadMenu();
        }
        else
        {
            newGameBackButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        }
    }
    else  newGameBackButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    if(CheckCollisionPointRec(mousePoint,readyRec))
    {
         if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            newGameReadyButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
            if(playerData.size() == 1) // == 5
            {
                isNewPlayerAllowed = false;
            }
            else LoadGame();
        }
        else
        {
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
    DrawRectangle(CalculateXCoord(100/4), CalculateYCoord(100/4), CalculateXCoord(100/2), CalculateYCoord(100/2), BLACK);
    DrawRectangleLines(CalculateXCoord(100/4), CalculateYCoord(100/4), CalculateXCoord(100/2), CalculateYCoord(100/2), RED);
    int headerStringWidth = MeasureText("You have five saved games", CalculateObjectSizeY(48)); 
    int headerSecondLineWidth = MeasureText("please remove one to continue", CalculateObjectSizeY(48));
    DrawText("You have five saved games", CalculateXCoord(100/2) -  (headerStringWidth/2), CalculateYCoord(100/4),CalculateObjectSizeY(48),RED);
    DrawText("please remove one to continue", CalculateXCoord(100/2) -  (headerSecondLineWidth/2), CalculateYCoord(100/4) + CalculateObjectSizeY(55),CalculateObjectSizeY(48),RED);
    DrawLineEx({CalculateXCoord((100/32) * 9),CalculateYCoord(100/4) + CalculateObjectSizeY(110)},{CalculateXCoord((100/32) * 24),CalculateYCoord(100/4) + CalculateObjectSizeY(110)},CalculateObjectSizeY(5),RED);
    for(int i = 0; i < playerData.size(); i++)
    {
        char playerNumber[3 + sizeof(char)] = "";
        sprintf(playerNumber, "%d.", playerData[i].playerNumber);
        //DrawText(playerData[i].playerName, CalculateXCoord(100/2) - (MeasureText(playerData[i].playerName, CalculateObjectSizeY(72))/2),CalculateYCoord(100/3) + (i * CalculateObjectSizeY(80)), CalculateObjectSizeY(72),RED);
        int playerNameWidth = MeasureText(playerData[i].playerName, CalculateObjectSizeY(48));
        DrawText(playerData[i].playerName, CalculateXCoord((100/8) * 3) - (playerNameWidth/2),CalculateYCoord(100/2.5) + (i * CalculateObjectSizeY(60)), CalculateObjectSizeY(48),RED);
        DrawText(playerNumber, CalculateXCoord(100/4) + CalculateObjectSizeX(10),CalculateYCoord(100/2.5) + (i * CalculateObjectSizeY(60)), CalculateObjectSizeY(48),RED);
        int savedDateWidth = MeasureText(playerData[i].lastSaved, CalculateObjectSizeY(48));        
        DrawText(playerData[i].lastSaved, CalculateXCoord((100/4) * 3) - CalculateObjectSizeX(savedDateWidth + 10),CalculateYCoord(100/2.5) + (i * CalculateObjectSizeY(60)), CalculateObjectSizeY(48),RED);
    }
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
                    playerName[letterCount] = (char)key;
                    playerName[letterCount+1] = '\0'; // Add null terminator at the end of the string.
                    letterCount++;
                }

                key = GetCharPressed();  // Check next character in the queue
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                playerName[letterCount] = '\0';
            }

}

void MainMenu::DrawLoadGameMenu() 
{

}

// Initialize the playbutton and its actions
void MainMenu::NewGameAction(Rectangle btnBounds)
{
    mousePoint = GetMousePosition();

    // Check button state
    if (CheckCollisionPointRec(mousePoint, btnBounds))
    {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            Vector4 inputStart = {CalculateXCoord(100/2) - CalculateObjectSizeX(300), CalculateYCoord(100/2) + CalculateObjectSizeY(80), CalculateXCoord(100/2) - CalculateObjectSizeX(210), CalculateYCoord(100/2) +  CalculateObjectSizeY(80)};
            inputLines.push_back(inputStart);
            newGameButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
            isMenuActive = false;
            for(int i=0; i <= 6; i++)
            {
                playerName[i] =  '\0';
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

    // Check button state
    if (CheckCollisionPointRec(mousePoint, btnBounds))
    {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            loadButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        else
        {
            loadButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            isMenuActive = false;
            LoadGame();
        }
    }
    else
    {
        loadButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
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

// Clear remenants of texture from memory
void MainMenu::UnloadMenu()
{
    UnloadTexture(menuTexture);
}