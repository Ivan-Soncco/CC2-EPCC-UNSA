#include <raylib.h>
#include "game.h"
#include "enemy.h"
#include "nave.h"


#define MAX_ENEMIES 6
#define ENEMY_SPEED 20
#define MAX_BULLETS 100
using namespace std;
/*
Enemy Game::getEnemyfromGame(){
    return Enemy();
}*/

void Game::resetGame(Nave* player1,Nave* player2,Enemy* A)
    {
        for (int i = 0; i < MAX_ENEMIES; i++)
        {
            A[i].reiniciarEnemy();
        }
        
        // Restablece los disparos de los jugadores
        player1->reiniciarNave();
        player2->reiniciarNave();
        /*
        */
        startTime = GetTime();
        elapsedTime = 0.0;
        gameOver = false;
        currentTime = startTime;
        
    }

void Game::menu(Camera camera)
    {
        BeginDrawing();
        ClearBackground(BLACK);
        const int screenWidth = 940;
        const int screenHeight = 480;
        /*
        BeginMode3D(camera);
        DrawModel(skyboxModel, (Vector3){ 0.0f, 0.0f, 0.0f }, 1.0f, WHITE);
        EndMode3D();
        BeginMode3D(camera);

        DrawModel(skybox, (Vector3){ 0.0f, 0.0f, 0.0f }, 1.0f, WHITE);

        EndMode3D();*/
        DrawText("GAME SPACEBOOM", screenWidth / 2 - MeasureText("GAME SPACEBOOM", 20) / 2, screenHeight / 2 + 20, 20, GRAY);
        DrawText("Press Q to start", screenWidth / 2 - MeasureText("Press Q to start", 20) / 2, screenHeight / 2 + 40, 20, GRAY);
            
    }
    