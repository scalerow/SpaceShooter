#include "home.h"
#include "mainmenu.h"

Home::Home(float height, float width) : screenHeight{height}, screenWidth{width}
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
}
void Home::LoadGame()
{
    activateGame = true;
    activateSettings = false;
    activateMenu = false;
}
void Home::LoadSettings()
{
    activateGame = false;
    activateSettings = true;
    activateMenu = false;
}