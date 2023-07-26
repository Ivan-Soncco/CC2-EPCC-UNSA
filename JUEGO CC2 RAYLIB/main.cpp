#include <iostream>
#include <raylib.h>
#include "prueba.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "nave.h"

#define MAX_ENEMIES 6
#define ENEMY_SPEED 20
#define MAX_BULLETS 100
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
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 35.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    const int enemyPoints = 10;

    //Carga los modelos de los jugadores y enemigos desde archivos
    Nave* player1 =new  Nave(LoadModel("data/nave.gltf"));
    player1->setPosicion((Vector3){-99.0f, 0.0f, -1.0f});
    Nave* player2 =new  Nave(LoadModel("data/nave.gltf"));
    player2->setPosicion((Vector3){-99.0f, 0.0f, 1.0f});
    
    //Model enemy = LoadModel("data/asteroide.gltf");
    /*Enemy* arrayEnemy =new  Enemy[6]();
    for(int i=0;i<6;i++){
        arrayEnemy[i].setModelo(LoadModel("data/asteroide.gltf"));
    }*/
    Enemy* enemy =new  Enemy(LoadModel("data/asteroide.gltf"));
    
    Game *game = Game::getInstance();

    //game->bandera1 = false;
    //game->bandera2 = false;

    player1->bandera=false;
    player2->bandera=false;
    
    game->resetGame();
    
    

    while (!WindowShouldClose())
    {
        if(game->gameStart==false){
            game->menu();
            if(IsKeyPressed(KEY_Q)){
                game->gameStart=true;
                game->resetGame();
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

        if (game->player2Position.z < -6.0f)
        {
            game->player2Position.z = -6.0f;
        }
        else if (game->player2Position.z > 6.0f)
        {
            game->player2Position.z = 6.0f;
        }

        // Move bullets 1
        player1->moverBala();
        
        // Move bullets 2
        player2->moverBala();

        // Move enemies
        /*
        for (int i = 0; i < MAX_ENEMIES; i++)
        {
            game->enemyPositions[i].x -= (ENEMY_SPEED + game->elapsedTime * 5) * GetFrameTime();

            if (game->enemyPositions[i].x < -101.0f)
            {
                float x = GetRandomValue(-30, -10);
                float z = GetRandomValue(-6, 6);
                game->enemyPositions[i] = (Vector3){x, 0.0f, z};
            }

            // Limit enemy positions within the vertical bounds
            if (game->enemyPositions[i].y < -5.0f)
                game->enemyPositions[i].y = -5.0f;
            else if (game->enemyPositions[i].y > 5.0f)
                game->enemyPositions[i].y = 5.0f;
        }*/
        
        for (int i = 0; i < MAX_ENEMIES; i++)
        {
            enemy->moverEnemigo(game, i);
        }
        
        // Collision detection  1s
        for (int i = 0; i < MAX_BULLETS; i++)
        {
            enemy->colision(player1, game, i);
    

        // Collision detection 2
        
            enemy->colision(player2, game, i);
        }

        // Players collision with enemies
        for (int i = 0; i < MAX_ENEMIES; i++)
        {
            enemy->colisionConNave(player1,game,i);
            enemy->colisionConNave(player2,game,i);
        }

        if (game->bandera1 && game->bandera2)
        {
            game->gameOver = true;
            game->bandera1 = false;
            game->bandera2 = false;
        }

        // Draw
        BeginDrawing();

        ClearBackground(BLACK);

        BeginMode3D(camera);

        // Draw player 1 ship
        DrawModel(player1->getModelo(), (Vector3){player1->getPosicionX(), player1->getPosicionY(), player1->getPosicionZ()}, game->model_s1, WHITE);

        // Draw player 2 ship
        DrawModel(player2->getModelo(), (Vector3){player2->getPosicionX(), player2->getPosicionY(), player2->getPosicionZ()}, game->model_s2, WHITE);
        
        // Draw enemy ships
        for (int i = 0; i < MAX_ENEMIES; i++)
        {
            if (game->enemyPositions[i].x != -30.0f)
                DrawModel(enemy->getModelo(), (Vector3){game->enemyPositions[i].x, game->enemyPositions[i].y, game->enemyPositions[i].z}, 0.5f, WHITE);
        }

        // Draw bullets 1
        for (int i = 0; i < MAX_BULLETS; i++)
        {
            if (player1->bulletActive[i])

                DrawSphere(player1->bullets[i], 0.1f, BLUE);
            // DrawModel(proyectil, (Vector3){bullets[i].x, bullets[i].y, bullets[i].z}, 0.1f, WHITE);
        }

        // Draw bullets 2
        for (int i = 0; i < MAX_BULLETS; i++)
        {
            if (player2->bulletActive[i])
                DrawSphere(player2->bullets[i], 0.1f, RED);
            // DrawModel(proyectil, (Vector3){bullets2[i].x, bullets2[i].y, bullets2[i].z}, 0.1f, WHITE);
        }
        
        EndMode3D();
        
        // Draw UI
        DrawText("JUGADOR 1", 10, 10, 20, RED);
        DrawText(TextFormat("Score: %04i", player1->score), 10, 30, 20, GREEN);
        DrawText(TextFormat("Bullets: %02i", player1->bulletCount), 10, 50, 20, MAROON);
        DrawText(TextFormat("PLAYER 1: Muevete con A y D ; dispara con ESPACIO"), 10, 70, 20, WHITE);

        DrawText("JUGADOR 2", screenWidth - 150, 10, 20, RED);
        DrawText(TextFormat("Score: %04i", game->score2), screenWidth - 150, 30, 20, GREEN);
        DrawText(TextFormat("Bullets: %02i", game->bulletCount2), screenWidth - 150, 50, 20, MAROON);
        DrawText("PLAYER 2: Muevete con 4 y 6 ; dispara con ENTER", 10, 90, 20, WHITE);
        if (game->gameOver)
        {
            
            ClearBackground(BLACK);
            DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.8f));

            DrawText("GAME OVER", screenWidth / 2 - MeasureText("GAME OVER", 40) / 2, screenHeight / 2 - 80, 40, RED);

            if (player1->score > game->score2)
            {
                DrawText("JUGADOR 1 GANA", screenWidth / 2 - MeasureText("JUGADOR 1 GANA", 30) / 2, screenHeight / 2 - 20, 30, GRAY);
                
            }
            else if (player1->score < game->score2)
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
            DrawText(TextFormat("Puntaje P2: %04i", game->score2), screenWidth / 2 - MeasureText(TextFormat("Score: %04i", game->score2), 30) / 2, screenHeight / 2 + 100, 20, GRAY);
            prueba();
        }
        
        if (game->gameOver == true && IsKeyPressed(KEY_R))
        {
            
            game->resetGame();
            ClearBackground(BLACK);
        }
        if (game->gameOver == true && IsKeyPressed(KEY_Q))
        {
            EndDrawing();
            game->gameStart=false;
            
        }

        EndDrawing();
        // Update elapsed time
        game->currentTime = GetTime();
        game->elapsedTime = game->currentTime - game->startTime;
        }
        
        
        
    }
    // Liberar recursos y cerrar la ventana...
    // De-Initialization
    UnloadModel(player1->getModelo());
    UnloadModel(player2->getModelo());
    UnloadModel(enemy->getModelo());

    CloseWindow();
    return 0;
}
