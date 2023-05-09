#include "settings.h"

Settings::Settings()
{
    InitSettings();
}

Settings::~Settings()
{
}

void Settings::InitSettings()
{
    isSettingsActive = true;
    exitSettings = false;
    soundButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    fullscreenButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    backButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
}

void Settings::toggleSound(Rectangle bounds)
{
    Rectangle updatedBnds = {bounds.x, bounds.y, bounds.width, bounds.height};
    Vector2 mousePoint = GetMousePosition();
    // Check button state
    if (CheckCollisionPointRec(mousePoint, updatedBnds))
    {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            soundButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);

            soundActive = IsSoundPlaying(gameSound);
            if (!soundActive)
            {
                gameSound = LoadSound("../");
                PlaySound(gameSound);
                soundActive = IsSoundPlaying(gameSound);
#ifndef PLATFORM_WEB
                saveSettings(configFileName);
#endif
            }
            else if (soundActive)
            {
                StopSound(gameSound);
                UnloadSound(gameSound);
                soundActive = IsSoundPlaying(gameSound);
            }
        }
        else
        {
            soundButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        }
    }
    else
    {
        soundButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    }
}

void Settings::toggleFullscreen(Rectangle bounds)
{
    Rectangle updatedBnds = {bounds.x, bounds.y, bounds.width, bounds.height};
    Vector2 mousePoint = GetMousePosition();
    // Check button state
    if (CheckCollisionPointRec(mousePoint, updatedBnds))
    {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            fullscreenButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
            ToggleFullscreen();
            fullscreen = IsWindowFullscreen();
#ifndef PLATFORM_WEB
            saveSettings(configFileName);
#endif
        }

        else
        {
            fullscreenButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        }
    }
    else
    {
        fullscreenButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    }
}

void Settings::DrawSettings()
{
    float screenHeight = GetScreenHeight();
    float screenWidth = GetScreenWidth();

    // Fullscreen

    int fullscreenStringWidth = MeasureText("FULLSCREEN", GameObjects::CalculateObjectSizeY(48));
    Rectangle fullscreenButtonRect = {(screenWidth / 2) + (fullscreenStringWidth / 2) + GameObjects::CalculateObjectSizeX(50), (screenHeight / 2) - GameObjects::CalculateObjectSizeY(200), GameObjects::CalculateObjectSizeY(48), GameObjects::CalculateObjectSizeY(48)};

    DrawText("FULLSCREEN", (screenWidth / 2) - (fullscreenStringWidth / 2), (screenHeight / 2) - GameObjects::CalculateObjectSizeY(200), GameObjects::CalculateObjectSizeY(48), GREEN);
    if (fullscreen)
    {
#ifndef PLATFORM_WEB
        saveSettings(configFileName);
#endif
        DrawRectangle(fullscreenButtonRect.x, fullscreenButtonRect.y, fullscreenButtonRect.width, fullscreenButtonRect.height, GREEN);
    }
    else if (!fullscreen)
    {
        DrawRectangleLines(fullscreenButtonRect.x, fullscreenButtonRect.y, fullscreenButtonRect.width, fullscreenButtonRect.height, fullscreenButtonColor);
    }

    // Sound
    Rectangle soundButtonRect = {(screenWidth / 2) + (fullscreenStringWidth / 2) + GameObjects::CalculateObjectSizeX(50), (screenHeight / 2) - GameObjects::CalculateObjectSizeY(100), GameObjects::CalculateObjectSizeY(48), GameObjects::CalculateObjectSizeY(48)};
    DrawText("SOUND", (screenWidth / 2) - (fullscreenStringWidth / 2), (screenHeight / 2) - GameObjects::CalculateObjectSizeY(100), GameObjects::CalculateObjectSizeY(48), GREEN);

    if (soundActive)
    {
#ifndef PLATFORM_WEB
        saveSettings(configFileName);
#endif
        DrawRectangle(soundButtonRect.x, soundButtonRect.y, soundButtonRect.width, soundButtonRect.height, soundButtonColor);
    }
    else if (!soundActive)
    {
        DrawRectangleLines(soundButtonRect.x, soundButtonRect.y, soundButtonRect.width, soundButtonRect.height, soundButtonColor);
    }

    // Exit
    float backStringWidth = MeasureText("BACK", GameObjects::CalculateObjectSizeY(72));
    Rectangle backButtonRect = {(screenWidth / 2) - (backStringWidth / 2), screenHeight - GameObjects::CalculateObjectSizeY(100), backStringWidth, GameObjects::CalculateObjectSizeY(72)};
    DrawText("BACK", backButtonRect.x, backButtonRect.y, backButtonRect.height, backButtonColor);

    toggleSound(soundButtonRect);
    toggleFullscreen(fullscreenButtonRect);
    BackToMenu(backButtonRect);
}

void Settings::BackToMenu(Rectangle bounds)
{
    Rectangle updatedBnds = {bounds.x, bounds.y, bounds.width, bounds.height};
    Vector2 mousePoint = GetMousePosition();
    // Check button state
    if (CheckCollisionPointRec(mousePoint, updatedBnds))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            backButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        else
        {
            backButtonColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            exitSettings = true;
        }
    }
    else
    {
        backButtonColor = ColorAlphaBlend(BLACK, WHITE, GREEN);
    }
}

void Settings::LoadPlayerData(std::vector<GameObjects::PlayerData> &playerData)
{
    try
    {
        BOOST_FOREACH (pt::ptree::value_type &value, tree.get_child("settings.playerdata"))
        {

            GameObjects::PlayerData player;
            std::string playerName = value.second.get<std::string>("playerName");
            std::strcpy(player.playerName, playerName.c_str());
            player.currentLevel = value.second.get<int>("currentLevel");
            player.playerId = value.second.get<int>("playerId");
            player.health = value.second.get<int>("health");
            std::string lastSaved = value.second.get<std::string>("lastSaved");
            std::strcpy(player.lastSaved, lastSaved.c_str());

            // The data function is used to access the data stored in a node.
            playerData.push_back(player);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Settings::LoadHighscores(std::vector<int> &highscores)
{
    try
    {

        BOOST_FOREACH (pt::ptree::value_type &value, tree.get_child("settings.highscores"))
        {
            int score = stoi(value.second.data());
            // The data function is used to access the data stored in a node.
            highscores.push_back(score);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Settings::loadSettings(const std::string &filename, std::vector<int> &highscores, std::vector<GameObjects::PlayerData> &playerData)
{
    // Parse the XML into the property tree.
    pt::read_xml(filename, tree);

    // Use the throwing version of get to find the debug filename.
    // If the path cannot be resolved, an exception is thrown.

    // highscores.push_back(tree.get<int>("settings.highscores"));

    // Use the default-value version of get to find the debug level.
    // Note that the default value is used to deduce the target type.

    // Use get_child to find the node containing the modules, and iterate over
    // its children. If the path cannot be resolved, get_child throws.
    // A C++11 for-range loop would also work.
    try
    {
        fullscreen = tree.get<bool>("settings.fullscreen");
        soundActive = tree.get<bool>("settings.sound");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    LoadHighscores(highscores);
    LoadPlayerData(playerData);
}

void Settings::saveSettings(const std::string &filename)
{
    try
    {
        tree.put("settings.filename", configFileName);
        tree.put("settings.fullscreen", fullscreen);
        tree.put("settings.sound", soundActive);
        // Write property tree to XML file
        pt::write_xml(filename, tree);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Settings::saveSettings(const std::string &filename, std::vector<int> &highscores, std::vector<GameObjects::PlayerData> &playerData)
{
    try
    {
        tree.put("settings.filename", configFileName);
        tree.put("settings.fullscreen", fullscreen);
        tree.put("settings.sound", soundActive);

        if (highscores.size() > 0)
        {
            tree.get_child("settings.highscores").erase("highscore");

            std::sort(highscores.begin(), highscores.end(), std::greater<int>());
            BOOST_FOREACH (int highscore, highscores)
            {
                tree.add("settings.highscores.highscore", highscore);
            }
        }

        if (playerData.size() > 0)
        {
            tree.get_child("settings").erase("playerdata");

            BOOST_FOREACH (GameObjects::PlayerData player, playerData)
            {
                char stringPlayerId[50 + sizeof(char)] = "";
                sprintf(stringPlayerId, "settings.playerdata.%d.playerId", player.playerId);
                tree.add(stringPlayerId, player.playerId);

                char stringPlayerLevel[50 + sizeof(char)] = "";
                sprintf(stringPlayerLevel, "settings.playerdata.%d.currentLevel", player.playerId);
                tree.add(stringPlayerLevel, player.currentLevel);

                char stringPlayerHealth[50 + sizeof(char)] = "";
                sprintf(stringPlayerHealth, "settings.playerdata.%d.health", player.playerId);
                tree.add(stringPlayerHealth, player.health);

                char stringPlayerName[50 + sizeof(char)] = "";
                sprintf(stringPlayerName, "settings.playerdata.%d.playerName", player.playerId);
                tree.add(stringPlayerName, player.playerName);

                char stringPlayerLastSaved[50 + sizeof(char)] = "";
                sprintf(stringPlayerLastSaved, "settings.playerdata.%d.lastSaved", player.playerId);
                tree.add(stringPlayerLastSaved, player.lastSaved);
            }
        }
        // Write property tree to XML file
        pt::write_xml(filename, tree);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Settings::InitGameSettings()
{
    if (!IsWindowFullscreen() && fullscreen)
    {
        ToggleFullscreen();
    }
    if (soundActive)
    {
        gameSound = LoadSound("../");
        PlaySound(gameSound);
    }
}
