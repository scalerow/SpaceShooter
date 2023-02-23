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

    Home(float height, float width);
    ~Home();

    void LoadMenu();
    void LoadGame();
    void LoadSettings();
};
#endif
