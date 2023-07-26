#include <raylib.h>
#include "game.h"

#define MAX_ENEMIES 6
#define ENEMY_SPEED 20
#define MAX_BULLETS 100
using namespace std;

void Game::resetGame()
    {
        player1Position = (Vector3){-99.0f, 0.0f, -1.0f};
        player2Position = (Vector3){-99.0f, 0.0f, 1.0f};

        // Genera posiciones aleatorias para los enemigos
        for (int i = 0; i < MAX_ENEMIES; i++)
        {
            float x = GetRandomValue(-30, -10);
            float z = GetRandomValue(-6, 6);
            enemyPositions[i] = (Vector3){x, 0.0f, z};
        }

        // Restablece los disparos de los jugadores
        for (int i = 0; i < MAX_BULLETS; i++)
        {
            bulletActive[i] = false;
        }

        // Restablece las variables de puntuación y tiempo
        bulletCount = 100;
        bulletCount2 = 100;
        score = 0;
        score2 = 0;
        startTime = GetTime();
        elapsedTime = 0.0;
        gameOver = false;
        currentTime = startTime;
        model_s1 = 0.2;
        model_s2 = 0.2;
    }
void Game::generateRandomEnemies()
    {
        for (int i = 0; i < MAX_ENEMIES; i++)
        {
            float x = GetRandomValue(-30, -10);
            float z = GetRandomValue(-6, 6);
            enemyPositions[i] = (Vector3){x, 0.0f, z};
        }
    }
void Game::setBulletCount1(int count)
    {
        bulletCount = count;
    }
void Game::setBulletCount2(int count)
    {
        bulletCount2 = count;
    }
void Game::menu()
    {
        BeginDrawing();
        const int screenWidth = 940;
        const int screenHeight = 480;
        DrawText("GAME SPACEBOOM", screenWidth / 2 - MeasureText("GAME SPACEBOOM", 20) / 2, screenHeight / 2 + 20, 20, GRAY);
        DrawText("Press Q to start", screenWidth / 2 - MeasureText("Press Q to start", 20) / 2, screenHeight / 2 + 40, 20, GRAY);
            
    }
    