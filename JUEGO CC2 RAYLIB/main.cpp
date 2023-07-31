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
#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif
using namespace std;



Game *Game::instance = nullptr;


int main(void)
{
    
    // Inicialización de la ventana
    const int screenWidth = 940;
    const int screenHeight = 480;
    // Inicialización de la ventana y otras configuraciones...

    
    InitWindow(screenWidth, screenHeight, "SpaceBoom");
    SetTargetFPS(30);
    Camera camera = {0};
    camera.position = (Vector3){-110.0f, 1.0f, 0.0f};
    //camera.position = (Vector3){120.0f, 120.0f, 120.0f};
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 35.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    
    //Carga los modelos de los jugadores y enemigos desde archivos
    Nave* player1 =new  Nave(LoadModel("data/nave.gltf"));
    player1->setPosicion((Vector3){-99.0f, 0.0f, -1.0f});
    Nave* player2 =new  Nave(LoadModel("data/nave.gltf"));
    player2->setPosicion((Vector3){-99.0f, 0.0f, 1.0f});
    
    
    
    
    Enemy* arrayEnemy =new  Enemy[6]();
    for (int i = 0; i < 6; i++)
    {
        //arrayEnemy[i].setModelo(LoadModel("data/asteroide.gltf"));
        arrayEnemy[i].setModelo(LoadModel("data/asteroide.gltf"));
    }
    

    Game *game = Game::getInstance();

    

    player1->bandera=false;
    player2->bandera=false;
    
    //game->resetGame(player1,player2,arrayEnemy);
    
    

    while (!WindowShouldClose())
    {
    
        if(game->gameStart==false){
            game->menu(camera);
            
            if(IsKeyPressed(KEY_Q)){
                game->gameStart=true;
                game->resetGame(player1,player2,arrayEnemy);
                player1->setPosicion((Vector3){-99.0f, 0.0f, -1.0f});
                player2->setPosicion((Vector3){-99.0f, 0.0f, 1.0f});
            }
            EndDrawing();
        }else{
            // Actualizar y dibujar el juego...
        // Player 1 movement
        if (IsKeyDown(KEY_A))
        {
            player1->movIzquierda();
        }
        else if (IsKeyDown(KEY_D))
        {
            player1->movDerecha();
        }
        
        // Player 1 shoot bullet
        if (IsKeyPressed(KEY_SPACE) && player1->bulletCount > 0)
        {
            
            player1->disparar();
        }

        // Player 2 movement
        if (IsKeyDown(KEY_LEFT))
        {
            player2->movIzquierda();
        }
        else if (IsKeyDown(KEY_RIGHT))
        {
            player2->movDerecha();
        }

        // Player 2 shoot bullet
        if (IsKeyPressed(KEY_UP) && player2->bulletCount > 0)
        {
            
            player2->disparar();
        }

        // Restricción para que los jugadores no se salgan de la pantalla
        if (player1->getPosicionZ() < -6.0f)
        {
            player1->setPosicionZ(-6.0f);
        }
        else if (player1->getPosicionZ() > 6.0f)
        {
            player1->setPosicionZ(6.0f);
        }

        if (player2->getPosicionZ() < -6.0f)
        {
            player2->setPosicionZ(-6.0f);
        }
        else if (player2->getPosicionZ() > 6.0f)
        {
            player2->setPosicionZ(6.0f);
        }

        // Move bullets 1
        player1->moverBala();
        
        // Move bullets 2
        player2->moverBala();

        // Move enemies
        for (int i = 0; i < MAX_ENEMIES; i++){
            arrayEnemy[i].move(game->elapsedTime);
        }

       //func colision enemy con bala
       //fun colision bala con enemy
       //if(player1->bala){for(enemyes){player1->bala.colision(arrayEnemies[]); } }
        for (int i = 0; i < MAX_BULLETS; i++)
        {
            if (player1->bulletActive[i])
            {
                for (int j = 0; j < MAX_ENEMIES; j++)
                {
                    arrayEnemy[j].colisionConBala(player1,i);
                }
            }
            if (player2->bulletActive[i])
            {
                for (int j = 0; j < MAX_ENEMIES; j++)
                {
                    arrayEnemy[j].colisionConBala(player2,i);
                }
            }
        }
        /*
        // Collision detection  1s
        */
        // Players collision with enemies
        for (int i = 0; i < MAX_ENEMIES; i++)
        {

            arrayEnemy[i].colisionConNave(player1,i);
            arrayEnemy[i].colisionConNave(player2,i);
            if (player1->bandera && player2->bandera)
                {
                    game->gameOver = true;
                }
        }/*
        *//*
        // Players collision with enemies
        */

        if (player1->bandera && player2->bandera)
        {
            game->gameOver = true;
            player1->bandera = false;
            player2->bandera = false;
        }

        // Draw
        BeginDrawing();

        ClearBackground(BLACK);

        BeginMode3D(camera);

        // Draw player 1 ship
        DrawModel(player1->getModelo(), (Vector3){player1->getPosicionX(), player1->getPosicionY(), player1->getPosicionZ()}, player1->model, WHITE);

        // Draw player 2 ship
        DrawModel(player2->getModelo(), (Vector3){player2->getPosicionX(), player2->getPosicionY(), player2->getPosicionZ()}, player2->model, WHITE);
        
        // Draw enemy ships
        /*
        */
        for (int i = 0; i < MAX_ENEMIES; i++)
        {
            /*
            for(int i=0;i<arrayEnemy[i].getModelo().materialCount; i++){
                DrawModelEx(arrayEnemy[i].getModelo(),(Vector3){arrayEnemy[i].getPosicionX(), arrayEnemy[i].getPosicionY(), arrayEnemy[i].getPosicionZ()},0.0f, (Vector3){1.0f, 1.0f, 1.0f}, arrayEnemy[i].getModelo().materials[i].maps[MAP_DIFFUSE].color);
            }
            */
            if (arrayEnemy[i].getPosicionX() != -30.0f){
                DrawModel(arrayEnemy[i].getModelo(), (Vector3){arrayEnemy[i].getPosicionX(), arrayEnemy[i].getPosicionY(), arrayEnemy[i].getPosicionZ()}, 0.5f, WHITE);
                
                //DrawModelEx(arrayEnemy[i].getModelo(),arrayEnemy[i].getPosicion(),(Vector3){1.0f, 0.0f, 0.0f},0.0f, (Vector3){1.0f, 1.0f, 1.0f}, WHITE);
            
            }

        }

        // Draw bullets 1
        // draw bala de objeto Bala

        for (int i = 0; i < MAX_BULLETS; i++)
        {
            if (player1->bulletActive[i])

                DrawSphere(player1->arrayBalas[i].getPosicion(), 0.1f, BLUE);
            // DrawModel(proyectil, (Vector3){bullets[i].x, bullets[i].y, bullets[i].z}, 0.1f, WHITE);
        }

        // Draw bullets 2
        for (int i = 0; i < MAX_BULLETS; i++)
        {
            if (player2->bulletActive[i])
                DrawSphere(player2->arrayBalas[i].getPosicion(), 0.1f, RED);
            // DrawModel(proyectil, (Vector3){bullets2[i].x, bullets2[i].y, bullets2[i].z}, 0.1f, WHITE);
        }
        
        EndMode3D();
        
        // Draw UI
        DrawText("JUGADOR 1", 10, 10, 20, RED);
        DrawText(TextFormat("Score: %04i", player1->score), 10, 30, 20, GREEN);
        DrawText(TextFormat("Bullets: %02i", player1->bulletCount), 10, 50, 20, MAROON);
        DrawText(TextFormat("PLAYER 1: Muevete con A y D ; dispara con ESPACIO"), 10, 70, 20, WHITE);

        DrawText("JUGADOR 2", screenWidth - 150, 10, 20, RED);
        DrawText(TextFormat("Score: %04i", player2->score), screenWidth - 150, 30, 20, GREEN);
        DrawText(TextFormat("Bullets: %02i", player2->bulletCount), screenWidth - 150, 50, 20, MAROON);
        DrawText("PLAYER 2: Muevete con 4 y 6 ; dispara con ENTER", 10, 90, 20, WHITE);
        if (game->gameOver)
        {
            
            ClearBackground(BLACK);
            DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.8f));

            DrawText("GAME OVER", screenWidth / 2 - MeasureText("GAME OVER", 40) / 2, screenHeight / 2 - 80, 40, RED);

            if (player1->score > player2->score)
            {
                DrawText("JUGADOR 1 GANA", screenWidth / 2 - MeasureText("JUGADOR 1 GANA", 30) / 2, screenHeight / 2 - 20, 30, GRAY);
                
            }
            else if (player1->score < player2->score)
            {
                DrawText("JUGADOR 2 GANA", screenWidth / 2 - MeasureText("JUGADOR 2 GANA", 30) / 2, screenHeight / 2 - 20, 30, GRAY);
            }
            else
            {
                DrawText("EMPATE", screenWidth / 2 - MeasureText("EMPATE", 30) / 2, screenHeight / 2 - 20, 30, GRAY);
            }

            DrawText("Press R to restart", screenWidth / 2 - MeasureText("Press R to restart", 20) / 2, screenHeight / 2 + 40, 20, GRAY);
            DrawText("Press Q to back MENU", screenWidth / 2 - MeasureText("Press R to back MENU", 20) / 2, screenHeight / 2 + 60, 20, GRAY);
            //scores
            DrawText(TextFormat("Puntaje P1: %04i", player1->score), screenWidth / 2 - MeasureText(TextFormat("Score: %04i", player1->score), 30) / 2, screenHeight / 2 + 80, 20, GRAY);
            DrawText(TextFormat("Puntaje P2: %04i", player2->score), screenWidth / 2 - MeasureText(TextFormat("Score: %04i", player2->score), 30) / 2, screenHeight / 2 + 100, 20, GRAY);

        }
        
        if (game->gameOver == true && IsKeyPressed(KEY_R))
        {
            
            game->resetGame(player1,player2,arrayEnemy);
            player1->setPosicion((Vector3){-99.0f, 0.0f, -1.0f});
            player2->setPosicion((Vector3){-99.0f, 0.0f, 1.0f});
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
    UnloadModel(player1->getModelo());
    UnloadModel(player2->getModelo());
    CloseWindow();

    return 0;
}
