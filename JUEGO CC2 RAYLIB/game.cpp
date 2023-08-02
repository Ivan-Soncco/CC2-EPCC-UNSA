#include <raylib.h>
#include "game.h"
#include "enemy.h"
#include "nave.h"


#define MAX_ENEMIES 6
#define ENEMY_SPEED 20
#define MAX_BULLETS 100
#define screenWidth 940
#define screenHeight 480
using namespace std;
/*
Enemy Game::getEnemyfromGame(){
    return Enemy();
}*/

void Game::resetGame(Enemy* A)
    {
        player1 =new  Nave(LoadModel("data/nave.gltf"));
        player1->setPosicion((Vector3){-99.0f, 0.0f, -1.0f});
        player2 =new  Nave(LoadModel("data/nave.gltf"));
        player2->setPosicion((Vector3){-99.0f, 0.0f, 1.0f});
        /*Enemy* arrayEnemy =new  Enemy[6]();
        for (int i = 0; i < 6; i++)
        {
            //arrayEnemy[i].setModelo(LoadModel("data/asteroide.gltf"));
            arrayEnemy[i].setModelo(LoadModel("data/asteroide.gltf"));
        }*/
        for (int i = 0; i < MAX_ENEMIES; i++)
        {
            A[i].reiniciarEnemy();
        }
        
        // Restablece los disparos de los jugadores
        player1->reiniciarNave();
        player2->reiniciarNave();
        player1->setPosicion((Vector3){-99.0f, 0.0f, -1.0f});
        player2->setPosicion((Vector3){-99.0f, 0.0f, 1.0f});
        /*
        */
        startTime = GetTime();
        elapsedTime = 0.0;
        gameOver = false;
        currentTime = startTime;
        
    }

void Game::menu()
    {
        BeginDrawing();
        ClearBackground(BLACK);
        //const int screenWidth = 940;
        //const int screenHeight = 480;
        DrawText("GAME SPACEBOOM", screenWidth / 2 - MeasureText("GAME SPACEBOOM", 20) / 2, screenHeight / 2 + 20, 20, GRAY);
        DrawText("Press Q to start", screenWidth / 2 - MeasureText("Press Q to start", 20) / 2, screenHeight / 2 + 40, 20, GRAY);
    }
void Game::play(Enemy* arrayEnemy, Camera camera){
    // Actualizar y dibujar el juego
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
            arrayEnemy[i].move(elapsedTime);
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
                    gameOver = true;
                    player1->bandera = false;
                    player2->bandera = false;
                    return;
                }
        }/*
        *//*
        // Players collision with enemies
        */

        if (player1->bandera && player2->bandera)
        {
            gameOver = true;
            player1->bandera = false;
            player2->bandera = false;
            return;
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
}    
void Game::GameOver(){
    
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
    //delete player1;
    //delete player2;
    //player1=nullptr;
    //player2=nullptr;
    //UnloadModel(player1->getModelo());
    //UnloadModel(player2->getModelo());        
}