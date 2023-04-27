#include "home.h"
#include "mainmenu.h"

Home::Home(float width, float height) : screenHeight{height}, screenWidth{width}
{
}

Home::~Home()
{
}

void Home::LoadMenu()
{
    activateGame = false;
    activateSettings = false;
    activateMenu = true;
    activateNewGame = false;
    activateLoadGame = false;
}
void Home::LoadGame()
{
    activateGame = true;
    activateSettings = false;
    activateMenu = false;
    activateNewGame = false;
    activateLoadGame = false;
}
void Home::NewGame()
{
    activateGame = false;
    activateSettings = false;
    activateMenu = false;
    activateNewGame = true;
    activateLoadGame = false;
}
void Home::LoadSelectGame()
{
    activateGame = false;
    activateSettings = false;
    activateMenu = false;
    activateNewGame = false;
    activateLoadGame = true;
}
void Home::LoadSettings()
{
    activateGame = false;
    activateSettings = true;
    activateMenu = false;
    activateNewGame = false;
    activateLoadGame = false;
}