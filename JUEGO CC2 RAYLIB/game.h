#ifndef GAME_H
#define GAME_H
#include <raylib.h>
#define MAX_ENEMIES 6
#define ENEMY_SPEED 20
#define MAX_BULLETS 100
using namespace std;

class Game
{
private:
    static Game *instance; // Singleton
    Game() {} // Private constructor to prevent instantiation

public:
    Vector3 player1Position;
    Vector3 player2Position;
    Vector3 enemyPositions[MAX_ENEMIES];
    bool bulletActive[MAX_BULLETS];
    bool bulletActive2[MAX_BULLETS];
    Vector3 bullets[MAX_BULLETS];
    Vector3 bullets2[MAX_BULLETS];
    int bulletCount;
    int bulletCount2;
    int score;
    int score2;
    double startTime = GetTime();
    double currentTime = startTime;
    double elapsedTime = 0.0;
    bool gameOver;
    bool gameStart=false;
    bool bandera1 = false;
    bool bandera2 = false;
    float model_s1 = 0.2;
    float model_s2 = 0.2;
    static Game *getInstance()
    {
        if (instance == nullptr)
            instance = new Game();
        return instance;
    }

    void resetGame();
    void generateRandomEnemies();
    void setBulletCount1(int);
    void setBulletCount2(int);
    void menu();
    
};

#endif