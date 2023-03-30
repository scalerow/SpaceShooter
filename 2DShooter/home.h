#ifndef HOME_H
#define HOME_H

class Home
{
private:
public:
    float screenWidth;
    float screenHeight;
    bool activateMenu = false;
    bool activateGame = false;
    bool activateSettings = false;
    bool activateLoadGame = false;
    bool activateNewGame = false;

    Home(float width, float height);
    ~Home();

    void LoadMenu();
    void LoadGame();
    void SelectLoadGame();
    void NewGame();
    void LoadSettings();
};
#endif
