#ifndef SETTINGS_H
#define SETTINGS_H

#include <raylib.h>
#include "gameobjects.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <set>
#include <exception>
#include <iostream>
#include "highscore.h"

namespace pt = boost::property_tree;

class Settings
{
private:
    bool fullscreen;
    bool soundActive;
    Sound gameSound;
    Color fullscreenButtonColor;
    Color soundButtonColor;
    Color backButtonColor;
    std::string configFileName = "config.xml";
    pt::ptree tree;

    void LoadPlayerData(std::vector<PlayerData> &playerData);
    void LoadHighscores(std::vector<int> &highscores);

public:
    bool isSettingsActive;
    bool exitSettings;

    Settings();
    ~Settings();

    // load/save settings to file
    void loadSettings(const std::string &filename, std::vector<int> &highscores, std::vector<PlayerData> &playerData);
    void saveSettings(const std::string &filename);
    void saveSettings(const std::string &filename, std::vector<int> &highscores, std::vector<PlayerData> &playerData);

    void InitSettings();
    void InitGameSettings();

    void toggleSound(Rectangle bounds);
    void toggleFullscreen(Rectangle bounds);

    void DrawSettings();

    void BackToMenu(Rectangle bounds);
};

#endif