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

    Image background = LoadImage("./media/space_background.png");
    ImageResize(&background, CalculateObjectSizeX(background.width), CalculateObjectSizeY(background.height));
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

void Game::DrawGameUI(int &health, int &score)
{
    char stringPlayerHealth[15 + sizeof(char)] = "";
    sprintf(stringPlayerHealth, "%d", health);
    int healthStringWidth = MeasureText(stringPlayerHealth, CalculateObjectSizeY(72));
    char stringPlayerScore[15 + sizeof(char)] = "";
    sprintf(stringPlayerScore, "Score: %d", score);
    DrawText(stringPlayerScore, CalculateXCoord(100 - 23.4375f), CalculateYCoord(4.63f), CalculateObjectSizeY(72.f), GREEN);

    // Healthbar
    DrawRectangleLines(CalculateXCoord(100 - 23.4375f), CalculateYCoord(88.7f), CalculateObjectSizeX(400.f), CalculateObjectSizeY(72.f), GREEN);
    // Healtbar filler
    DrawRectangle(CalculateXCoord(100 - 23.4375f), CalculateYCoord(88.7f), CalculateObjectSizeX((400.f / 150.f) * (float)health), CalculateObjectSizeY(72.f), GREEN);
    // Health plain text
    DrawText(stringPlayerHealth, CalculateXCoord(100 - 10.416f) - healthStringWidth, CalculateYCoord(88.7f), CalculateObjectSizeY(72.f), WHITE);
}

// For ARCADE MODE
void Game::DrawGameOver(HighScore &highscores, Settings &settings, int &score)
{
    // Diffuse background
    RenderBackground(true);
    // Measuring the text GAME OVER to be able to position it correctly, than draw it
    int textWidth = MeasureText("GAME OVER", CalculateObjectSizeY(120.f));
    DrawText("GAME OVER", CalculateXCoord(100 / 2) - (textWidth / 2), CalculateYCoord(9.26f), CalculateObjectSizeY(120.f), RED);

    // Check if highscore is updated for this round - if it isnt (which it shouldnt be), updates highscore and save it to config file
    if (!highscores.highscoreUpdated)
    {
        highscores.UpdateHighscores(score);
#ifndef PLATFORM_WEB
        settings.saveSettings("config.xml", highscores.highScores);
#endif
    }

    // Checking if theres a new highscore entry - if it is, change the color on highscore line
    Color highscoreAchievedTextColor = highscores.newHighscoreEntry ? Color({110, 20, 143, 255}) : RED;

    // Creating char array of last score, measure the width of relevant text and draws it
    char stringPlayerScore[15 + sizeof(char)] = "";
    sprintf(stringPlayerScore, "Score: %d", score);
    int scoreStringWidth = MeasureText(stringPlayerScore, CalculateObjectSizeY(100));
    DrawText(stringPlayerScore, CalculateXCoord(100 / 2) - (scoreStringWidth / 2), CalculateYCoord(100 / 2) - CalculateYCoord(18.56f), CalculateObjectSizeY(100.f), highscoreAchievedTextColor);

    // Header for highscore-table is measured for positioning, then drawn - along with a line to separate it from the actual list of highscores
    int highscoreLabelWidth = MeasureText("Highscores", CalculateObjectSizeY(72.f));
    DrawText("Highscores", CalculateXCoord(100 / 2) - (highscoreLabelWidth / 2), CalculateYCoord(100 / 2) - CalculateYCoord(4.26f), CalculateObjectSizeY(72.f), RED);
    DrawLineEx({CalculateXCoord(100 / 2) - (highscoreLabelWidth / 2) - CalculateObjectSizeX(75.f), CalculateYCoord(100 / 2) + CalculateYCoord(3.f)}, {CalculateXCoord(100 / 2) + (highscoreLabelWidth / 2) + CalculateObjectSizeX(75.f), CalculateYCoord(100 / 2) + CalculateYCoord(3.f)}, 8.f, RED);

    // Init an int for positioning of each line of highscore, is appended to.
    int highscoresPosition = CalculateYCoord(100 / 2) + CalculateYCoord(3.f);
    for (int i = 0; i < highscores.highScores.size(); i++)
    {
        // Appends to highscore position to make it ready for next line
        highscoresPosition += CalculateYCoord(7.08f);

        // Measuring highscore, highscore-position
        char scoreString[15 + sizeof(char)] = "";
        sprintf(scoreString, "%d", highscores.highScores[i]);
        char scorePosString[5 + sizeof(char)] = "";
        sprintf(scorePosString, "%d.", i + 1);
        int scoreStringWidth = MeasureText(scoreString, CalculateObjectSizeY(48.f));
        int scorePosStringWidth = MeasureText(scorePosString, CalculateObjectSizeY(48.f));

        // Checking if the new score is among the highscores, to color it differently (this soultion isnt that well thought through) Drawing the list of highscores
        if (highscores.highScores[i] == score)
        {
            DrawText(scoreString, CalculateXCoord(100 / 2) + (highscoreLabelWidth / 2) + CalculateObjectSizeX(75.f) - (scoreStringWidth), highscoresPosition - CalculateObjectSizeY(48), CalculateObjectSizeY(48), highscoreAchievedTextColor);
            DrawText(scorePosString, CalculateXCoord(100 / 2) - (highscoreLabelWidth / 2) - CalculateObjectSizeX(75.f), highscoresPosition - CalculateObjectSizeY(48), CalculateObjectSizeY(48), highscoreAchievedTextColor);
        }
        else
        {
            DrawText(scoreString, CalculateXCoord(100 / 2) + (highscoreLabelWidth / 2) + CalculateObjectSizeX(75.f) - (scoreStringWidth), highscoresPosition - CalculateObjectSizeY(48), CalculateObjectSizeY(48), RED);
            DrawText(scorePosString, CalculateXCoord(100 / 2) - (highscoreLabelWidth / 2) - CalculateObjectSizeX(75.f), highscoresPosition - CalculateObjectSizeY(48), CalculateObjectSizeY(48), RED);
        }
    }

    // Measuring and drawing info text
    int subTextWidth = MeasureText("[ENTER OR SPACE: RESTART, ESC: MAIN MENU]", CalculateObjectSizeY(36.f));
    DrawText("[ENTER OR SPACE: RESTART, ESC: MAIN MENU]", (screenWidth / 2) - (subTextWidth / 2), CalculateYCoord(100 - 4.63f), CalculateObjectSizeY(36.f), RED);
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

    Rectangle pauseMenuRec = {CalculateXCoord(100 / 2) - CalculateObjectSizeX(350.f),
                              CalculateYCoord(100 / 2) - CalculateObjectSizeY(125.f),
                              CalculateObjectSizeX(700.f),
                              CalculateObjectSizeY(350.f)};

    DrawRectangleLinesEx(pauseMenuRec, 5, GREEN);

    int resumeStringWidth = MeasureText("Resume", CalculateObjectSizeY(72.f));
    resumeRec = {CalculateXCoord(100 / 2) - CalculateObjectSizeX(resumeStringWidth / 2), CalculateYCoord(100 / 2) - CalculateObjectSizeY(72.f / 2), CalculateObjectSizeX(resumeStringWidth), CalculateObjectSizeY(72.f)};
    DrawText("Resume", CalculateXCoord(100 / 2) - CalculateObjectSizeX(resumeStringWidth / 2), CalculateYCoord(100 / 2) - CalculateObjectSizeY(72.f / 2), CalculateObjectSizeY(72.f), resumeColor);

    int backToMenuStringWidth = MeasureText("Exit to menu", CalculateObjectSizeY(72.f));
    backRec = {CalculateXCoord(100 / 2) - CalculateObjectSizeX(backToMenuStringWidth / 2), CalculateYCoord(100 / 2) - CalculateObjectSizeY(72.f / 2) + CalculateObjectSizeY(100.f), CalculateObjectSizeX(backToMenuStringWidth), CalculateObjectSizeY(72.f)};
    DrawText("Exit to menu", CalculateXCoord(100 / 2) - CalculateObjectSizeX(backToMenuStringWidth / 2), CalculateYCoord(100 / 2) - CalculateObjectSizeY(72.f / 2) + CalculateObjectSizeY(100.f), CalculateObjectSizeY(72.f), backColor);
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