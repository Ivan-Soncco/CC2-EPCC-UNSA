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
    Nave* player1=nullptr;
    Nave* player2=nullptr;
    static Game *getInstance()
    {
        if (instance == nullptr)
            instance = new Game();
        return instance;
    }
    void resetGame(Enemy*);
    void menu();
    void play(Enemy*,Camera);
    void GameOver();
};

#endif