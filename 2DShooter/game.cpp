#include <raylib.h>
#include "game.h"

Game::Game(float &widthP, float &heightP) : MainMenu{widthP, heightP}
{
    ResetGame();
}

Game::~Game()
{
}

// Initialize the game
void Game::InitGame()
{
    isGameActive = true;
    isGameSaved = false;

    Image background = LoadImage("./media/space_background.png");
    ImageResize(&background, GameObjects::CalculateObjectSizeX(background.width), GameObjects::CalculateObjectSizeY(background.height));
    Texture2D backgroundTxr = LoadTextureFromImage(background);
    gameBackgroudPosition = {0, 0};
    UnloadImage(background);

    flightArea = {gameBackgroudPosition.x, gameBackgroudPosition.y, screenWidth, screenHeight};
    gameTexture = backgroundTxr;
}

void Game::RenderBackground(bool menu)
{
    if (!menu)
    {
        DrawTexture(gameTexture, gameBackgroudPosition.x, gameBackgroudPosition.y, RAYWHITE);
    }
    else
    {
        BeginBlendMode(BLEND_ALPHA);
        DrawTexture(menuTexture, menuBackgroudPosition.x, menuBackgroudPosition.y, DARKGRAY);
        EndBlendMode();
    }
}

void Game::DrawGameUI(int &currentHealth, int &totalHealth, int &score)
{
    char stringPlayerHealth[3 + sizeof(char)] = "";
    sprintf(stringPlayerHealth, "%i", currentHealth);
    int healthStringWidth = MeasureText(stringPlayerHealth, GameObjects::CalculateObjectSizeY(72.f));
    char stringPlayerScore[15 + sizeof(char)] = "";
    sprintf(stringPlayerScore, "Score: %d", score);
    DrawText(stringPlayerScore, GameObjects::CalculateXCoord((100 / 4) * 3), GameObjects::CalculateYCoord(4.63f), GameObjects::CalculateObjectSizeY(72.f), GREEN);

    // Healthbar
    DrawRectangleLines(GameObjects::CalculateXCoord((100 / 4) * 3), GameObjects::CalculateYCoord(88.7f), GameObjects::CalculateObjectSizeX(400.f), GameObjects::CalculateObjectSizeY(72.f), GREEN);
    // Healtbar filler
    DrawRectangle(GameObjects::CalculateXCoord((100 / 4) * 3), GameObjects::CalculateYCoord(88.7f), GameObjects::CalculateObjectSizeX((400.f / totalHealth) * (float)currentHealth), GameObjects::CalculateObjectSizeY(72.f), GREEN);
    // Health plain text
    DrawText(stringPlayerHealth, (GameObjects::CalculateXCoord((100 / 4) * 3) + GameObjects::CalculateObjectSizeX(200.f)) - (healthStringWidth / 2), GameObjects::CalculateYCoord(88.7f), GameObjects::CalculateObjectSizeY(72.f), WHITE);
}

// For ARCADE MODE
void Game::DrawGameOver(HighScore &highscores, Settings &settings, int &score)
{
    // Diffuse background
    RenderBackground(true);
    // Measuring the text GAME OVER to be able to position it correctly, than draw it
    int textWidth = MeasureText("GAME OVER", GameObjects::CalculateObjectSizeY(120.f));
    DrawText("GAME OVER", GameObjects::CalculateXCoord(100 / 2) - (textWidth / 2), GameObjects::CalculateYCoord(9.26f), GameObjects::CalculateObjectSizeY(120.f), RED);

    // Check if highscore is updated for this round - if it isnt (which it shouldnt be), updates highscore and save it to config file
    if (!highscores.highscoreUpdated)
    {
        highscores.UpdateHighscores(score);
    }

#ifndef PLATFORM_WEB
    if (!isGameSaved)
    {
        activePlayer.currentLevel = 1; // this wll be the current level when thats implemented, really not neccessary now.
        std::strcpy(activePlayer.lastSaved, GameObjects::GetDateTimeNow());
        UpdatePlayerDataList(playerData, activePlayer);
        settings.saveSettings("config.xml", highscores.highScores, playerData);
        isGameSaved = true;
    }
#endif

    // Checking if theres a new highscore entry - if it is, change the color on highscore line
    Color highscoreAchievedTextColor = highscores.newHighscoreEntry ? Color({110, 20, 143, 255}) : RED;

    // Creating char array of last score, measure the width of relevant text and draws it
    char stringPlayerScore[15 + sizeof(char)] = "";
    sprintf(stringPlayerScore, "Score: %d", score);
    int scoreStringWidth = MeasureText(stringPlayerScore, GameObjects::CalculateObjectSizeY(100));
    DrawText(stringPlayerScore, GameObjects::CalculateXCoord(100 / 2) - (scoreStringWidth / 2), GameObjects::CalculateYCoord(100 / 2) - GameObjects::CalculateYCoord(18.56f), GameObjects::CalculateObjectSizeY(100.f), highscoreAchievedTextColor);

    // Header for highscore-table is measured for positioning, then drawn - along with a line to separate it from the actual list of highscores
    int highscoreLabelWidth = MeasureText("Highscores", GameObjects::CalculateObjectSizeY(72.f));
    DrawText("Highscores", GameObjects::CalculateXCoord(100 / 2) - (highscoreLabelWidth / 2), GameObjects::CalculateYCoord(100 / 2) - GameObjects::CalculateYCoord(4.26f), GameObjects::CalculateObjectSizeY(72.f), RED);
    DrawLineEx({GameObjects::CalculateXCoord(100 / 2) - (highscoreLabelWidth / 2) - GameObjects::CalculateObjectSizeX(75.f), GameObjects::CalculateYCoord(100 / 2) + GameObjects::CalculateYCoord(3.f)}, {GameObjects::CalculateXCoord(100 / 2) + (highscoreLabelWidth / 2) + GameObjects::CalculateObjectSizeX(75.f), GameObjects::CalculateYCoord(100 / 2) + GameObjects::CalculateYCoord(3.f)}, 8.f, RED);

    // Init an int for positioning of each line of highscore, is appended to.
    int highscoresPosition = GameObjects::CalculateYCoord(100 / 2) + GameObjects::CalculateYCoord(3.f);
    for (int i = 0; i < highscores.highScores.size(); i++)
    {
        // Appends to highscore position to make it ready for next line
        highscoresPosition += GameObjects::CalculateYCoord(7.08f);

        // Measuring highscore, highscore-position
        char scoreString[15 + sizeof(char)] = "";
        sprintf(scoreString, "%d", highscores.highScores[i]);
        char scorePosString[5 + sizeof(char)] = "";
        sprintf(scorePosString, "%d.", i + 1);
        int scoreStringWidth = MeasureText(scoreString, GameObjects::CalculateObjectSizeY(48.f));
        int scorePosStringWidth = MeasureText(scorePosString, GameObjects::CalculateObjectSizeY(48.f));

        // Checking if the new score is among the highscores, to color it differently (this soultion isnt that well thought through) Drawing the list of highscores
        if (highscores.highScores[i] == score)
        {
            DrawText(scoreString, GameObjects::CalculateXCoord(100 / 2) + (highscoreLabelWidth / 2) + GameObjects::CalculateObjectSizeX(75.f) - (scoreStringWidth), highscoresPosition - GameObjects::CalculateObjectSizeY(48), GameObjects::CalculateObjectSizeY(48), highscoreAchievedTextColor);
            DrawText(scorePosString, GameObjects::CalculateXCoord(100 / 2) - (highscoreLabelWidth / 2) - GameObjects::CalculateObjectSizeX(75.f), highscoresPosition - GameObjects::CalculateObjectSizeY(48), GameObjects::CalculateObjectSizeY(48), highscoreAchievedTextColor);
        }
        else
        {
            DrawText(scoreString, GameObjects::CalculateXCoord(100 / 2) + (highscoreLabelWidth / 2) + GameObjects::CalculateObjectSizeX(75.f) - (scoreStringWidth), highscoresPosition - GameObjects::CalculateObjectSizeY(48), GameObjects::CalculateObjectSizeY(48), RED);
            DrawText(scorePosString, GameObjects::CalculateXCoord(100 / 2) - (highscoreLabelWidth / 2) - GameObjects::CalculateObjectSizeX(75.f), highscoresPosition - GameObjects::CalculateObjectSizeY(48), GameObjects::CalculateObjectSizeY(48), RED);
        }
    }

    // Measuring and drawing info text
    int subTextWidth = MeasureText("[ENTER OR SPACE: RESTART, ESC: MAIN MENU]", GameObjects::CalculateObjectSizeY(36.f));
    DrawText("[ENTER OR SPACE: RESTART, ESC: MAIN MENU]", (screenWidth / 2) - (subTextWidth / 2), GameObjects::CalculateYCoord(100 - 4.63f), GameObjects::CalculateObjectSizeY(36.f), RED);
}

void Game::PauseGame()
{
    paused = true;
    resumeColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    backColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
}

void Game::DrawPauseGame()
{
    RenderBackground(true);

    Rectangle pauseMenuRec = {GameObjects::CalculateXCoord(100 / 2) - GameObjects::CalculateObjectSizeX(350.f),
                              GameObjects::CalculateYCoord(100 / 2) - GameObjects::CalculateObjectSizeY(125.f),
                              GameObjects::CalculateObjectSizeX(700.f),
                              GameObjects::CalculateObjectSizeY(350.f)};

    DrawRectangleLinesEx(pauseMenuRec, 5, GREEN);

    int resumeStringWidth = MeasureText("Resume", GameObjects::CalculateObjectSizeY(72.f));
    resumeRec = {GameObjects::CalculateXCoord(100 / 2) - GameObjects::CalculateObjectSizeX(resumeStringWidth / 2), GameObjects::CalculateYCoord(100 / 2) - GameObjects::CalculateObjectSizeY(72.f / 2), GameObjects::CalculateObjectSizeX(resumeStringWidth), GameObjects::CalculateObjectSizeY(72.f)};
    DrawText("Resume", GameObjects::CalculateXCoord(100 / 2) - GameObjects::CalculateObjectSizeX(resumeStringWidth / 2), GameObjects::CalculateYCoord(100 / 2) - GameObjects::CalculateObjectSizeY(72.f / 2), GameObjects::CalculateObjectSizeY(72.f), resumeColor);

    int backToMenuStringWidth = MeasureText("Exit to menu", GameObjects::CalculateObjectSizeY(72.f));
    backRec = {GameObjects::CalculateXCoord(100 / 2) - GameObjects::CalculateObjectSizeX(backToMenuStringWidth / 2), GameObjects::CalculateYCoord(100 / 2) - GameObjects::CalculateObjectSizeY(72.f / 2) + GameObjects::CalculateObjectSizeY(100.f), GameObjects::CalculateObjectSizeX(backToMenuStringWidth), GameObjects::CalculateObjectSizeY(72.f)};
    DrawText("Exit to menu", GameObjects::CalculateXCoord(100 / 2) - GameObjects::CalculateObjectSizeX(backToMenuStringWidth / 2), GameObjects::CalculateYCoord(100 / 2) - GameObjects::CalculateObjectSizeY(72.f / 2) + GameObjects::CalculateObjectSizeY(100.f), GameObjects::CalculateObjectSizeY(72.f), backColor);
}

void Game::UpdatePauseGame()
{
    mousePoint = GetMousePosition();
    if (CheckCollisionPointRec(mousePoint, resumeRec))
    {
        resumeColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            paused = false;
        }
    }
    else
    {
        resumeColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    }

    if (CheckCollisionPointRec(mousePoint, backRec))
    {
        backColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            UnloadGame();
            LoadMenu();
        }
    }
    else
    {
        backColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    }

    if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_P))
        paused = false;
}

void Game::ResetGame()
{
    paused = false;
    shotTimerRight = 0;
    shotTimerLeft = 0;
    enemyShotTimer = 0;
    enemyCounter = 0;
    isGameActive = false;
}

// Clear remenants of texture from memory
void Game::UnloadGame()
{
    ResetGame();
    UnloadTexture(gameTexture);
}