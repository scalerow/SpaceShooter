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

public:
    bool isSettingsActive;
    bool exitSettings;

    Settings();
    ~Settings();

    void InitSettings();

    void toggleSound(Rectangle bounds);
    void toggleFullscreen(Rectangle bounds);

    void DrawSettings();

    void BackToMenu(Rectangle bounds);
};

#endif