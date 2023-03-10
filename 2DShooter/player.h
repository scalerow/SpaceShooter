#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include "game.h"
#include "bullet.h"
#include <vector>
#include <cmath>
#include "gameobjects.h"
#include <random>

class Player
{
private:

public:
    Vector2 position;
    float rotation;
    float radius;
    float speed;
    int health;
    bool playerActive;
    Texture2D playerTexture;
    Texture2D playerBulletTexture;
    std::vector<Bullet> rightBullets;
    std::vector<Bullet> leftBullets;
    int leftShotTimer;
    int rightShotTimer;
    int specialAttackBulletCount;
    std::vector<Debris> playerDebris;
    
    bool gameOver;
    int score;

    Player();
    ~Player();

    void InitPlayer(float screenHeight, float screenWidth);
    void UpdatePlayer(float delta, Vector4 flightArea);
    void UpdateRightBullet();
    void UpdateLeftBullet();
    void isHit(std::vector<Bullet> &bullet);
    void PlayerExplosion(float explosionArea, float debrisSize);
    void FillDebris(int particleAmount);

    void UnloadPlayer();
};

#endif