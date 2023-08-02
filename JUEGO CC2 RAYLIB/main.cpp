#include <iostream>
#include <raylib.h>
#include "prueba.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "nave.h"
#include "bala.h"
#include "raymath.h"


#define MAX_ENEMIES 6
#define ENEMY_SPEED 20
#define MAX_BULLETS 100
/*
#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif*/
using namespace std;



Game *Game::instance = nullptr;


int main(void)
{
    
    // Inicialización de la ventana
    const int screenWidth = 940;
    const int screenHeight = 480;

    InitWindow(screenWidth, screenHeight, "SpaceBoom");
    SetTargetFPS(30);
    Camera camera = {0};
    camera.position = (Vector3){-110.0f, 1.0f, 0.0f};
    //camera.position = (Vector3){120.0f, 120.0f, 120.0f};
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 35.0f;
    camera.projection = CAMERA_PERSPECTIVE;
        
    Enemy* arrayEnemy =new  Enemy[6]();
    for (int i = 0; i < 6; i++)
    {
        //arrayEnemy[i].setModelo(LoadModel("data/asteroide.gltf"));
        arrayEnemy[i].setModelo(LoadModel("data/asteroide.gltf"));
    }
    
    Game *game = Game::getInstance();

    //game->resetGame(player1,player2,arrayEnemy);
    while (!WindowShouldClose())
    {
    
        if(game->gameStart==false){
            game->menu();
            
            if(IsKeyPressed(KEY_Q)){
                game->gameStart=true;
                game->resetGame(arrayEnemy);
            }
            EndDrawing();
        }else{
            game->play(arrayEnemy,camera);

        if (game->gameOver)
        {
            game->GameOver();
        }
        if (game->gameOver == true && IsKeyPressed(KEY_R))
        {   
            game->resetGame(arrayEnemy);
            ClearBackground(BLACK);
        }

        if (game->gameOver == true && IsKeyPressed(KEY_Q))
        {
            game->gameStart=false;
            game->gameOver=false;
            ClearBackground(BLACK);
            EndDrawing();
        }
        EndDrawing();
        // Update elapsed time
        game->currentTime = GetTime();
        game->elapsedTime = game->currentTime - game->startTime;
        }
    }
    // Liberar recursos y cerrar la ventana...
    // De-Initialization
    delete[] arrayEnemy;
    delete game;
    CloseWindow();

    return 0;
}
