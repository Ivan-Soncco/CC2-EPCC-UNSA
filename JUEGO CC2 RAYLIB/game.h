#ifndef GAME_H
#define GAME_H
#include <raylib.h>
#include <iostream>
#include "player.h"
#include "nave.h"
#include "enemy.h"
#define MAX_ENEMIES 6
#define ENEMY_SPEED 20
#define MAX_BULLETS 100
using namespace std;

//class Enemy;

class Game
{
private:
    static Game *instance; // Singleton
    
    Game() {} // Construtor Privado

public:
    double startTime = GetTime();
    double currentTime = startTime;
    double elapsedTime = 0.0;
    bool gameOver;
    bool gameStart=false;
    
    static Game *getInstance()
    {
        if (instance == nullptr)
            instance = new Game();
        return instance;
    }

    void resetGame(Nave*,Nave*,Enemy*);
    void generateRandomEnemies();
    void setBulletCount1(int);
    void setBulletCount2(int);
    void menu(Camera);
};

#endif