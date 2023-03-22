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
                saveSettings(configFileName);
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
            saveSettings(configFileName);
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

    int fullscreenStringWidth = MeasureText("FULLSCREEN", CalculateObjectSizeY(48));
    Rectangle fullscreenButtonRect = {(screenWidth / 2) + (fullscreenStringWidth / 2) + CalculateObjectSizeX(50), (screenHeight / 2) - CalculateObjectSizeY(200), CalculateObjectSizeY(48), CalculateObjectSizeY(48)};

    DrawText("FULLSCREEN", (screenWidth / 2) - (fullscreenStringWidth / 2), (screenHeight / 2) - CalculateObjectSizeY(200), CalculateObjectSizeY(48), GREEN);
    if (fullscreen)
    {
        saveSettings(configFilePath);
        DrawRectangle(fullscreenButtonRect.x, fullscreenButtonRect.y, fullscreenButtonRect.width, fullscreenButtonRect.height, GREEN);
    }
    else if (!fullscreen)
    {
        DrawRectangleLines(fullscreenButtonRect.x, fullscreenButtonRect.y, fullscreenButtonRect.width, fullscreenButtonRect.height, fullscreenButtonColor);
    }

    // Sound
    Rectangle soundButtonRect = {(screenWidth / 2) + (fullscreenStringWidth / 2) + CalculateObjectSizeX(50), (screenHeight / 2) - CalculateObjectSizeY(100), CalculateObjectSizeY(48), CalculateObjectSizeY(48)};
    DrawText("SOUND", (screenWidth / 2) - (fullscreenStringWidth / 2), (screenHeight / 2) - CalculateObjectSizeY(100), CalculateObjectSizeY(48), GREEN);

    if (soundActive)
    {
        saveSettings(configFilePath);
        DrawRectangle(soundButtonRect.x, soundButtonRect.y, soundButtonRect.width, soundButtonRect.height, soundButtonColor);
    }
    else if (!soundActive)
    {
        DrawRectangleLines(soundButtonRect.x, soundButtonRect.y, soundButtonRect.width, soundButtonRect.height, soundButtonColor);
    }

    // Exit
    float backStringWidth = MeasureText("BACK", CalculateObjectSizeY(72));
    Rectangle backButtonRect = {(screenWidth / 2) - (backStringWidth / 2), screenHeight - CalculateObjectSizeY(100), backStringWidth, CalculateObjectSizeY(72)};
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

void Settings::loadSettings(const std::string &filename, std::vector<int> &highscores)
{
    // Parse the XML into the property tree.
    pt::read_xml(filename, tree);

    // Use the throwing version of get to find the debug filename.
    // If the path cannot be resolved, an exception is thrown.
    fullscreen = tree.get<bool>("settings.fullscreen");
    soundActive = tree.get<bool>("settings.sound");
    // highscores.push_back(tree.get<int>("settings.highscores"));

    // Use the default-value version of get to find the debug level.
    // Note that the default value is used to deduce the target type.

    // Use get_child to find the node containing the modules, and iterate over
    // its children. If the path cannot be resolved, get_child throws.
    // A C++11 for-range loop would also work.
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

void Settings::saveSettings(const std::string &filename)
{
    // Put the simple values into the tree. The integer is automatically
    // converted to a string. Note that the "debug" node is automatically
    // created if it doesn't exist.
    tree.put("settings.filename", configFileName);
    tree.put("settings.fullscreen", fullscreen);
    tree.put("settings.sound", soundActive);
    // Write property tree to XML file
    pt::write_xml(filename, tree);
}

void Settings::saveSettings(const std::string &filename, std::vector<int> &highscores)
{
    // Put the simple values into the tree. The integer is automatically
    // converted to a string. Note that the "debug" node is automatically
    // created if it doesn't exist.
    tree.put("settings.filename", configFileName);
    tree.put("settings.fullscreen", fullscreen);
    tree.put("settings.sound", soundActive);
    // Add all the modules. Unlike put, which overwrites existing nodes, add
    // adds a new node at the lowest level, so the "modules" node will have
    // multiple "module" children.
    if (highscores.size() > 0)
    {

        tree.erase("settings.highscores");

        std::sort(highscores.begin(), highscores.end(), std::greater<int>());
        BOOST_FOREACH (int highscore, highscores)
        {
            tree.add("settings.highscores.highscore", highscore);
        }
    }
    // Write property tree to XML file
    pt::write_xml(filename, tree);
}

void Settings::LoadGameSettings()
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