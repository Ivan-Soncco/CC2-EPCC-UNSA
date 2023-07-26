#include "enemy.h"
#include <raylib.h>
#include <iostream>
#include "game.h"
#include "nave.h"

#define MAX_ENEMIES 6
#define ENEMY_SPEED 20

Enemy::Enemy(){}

Enemy::Enemy(Model m1)
{
    setModelo(m1);
}

int Enemy::getEnemyPoints()
{
    return enemyPoints;
}

void Enemy::moverEnemigo(Game* game, int i){
    
        
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
        
}

void Enemy:: colision(Nave* player1,Game* game,int i)
{
    if (player1->bulletActive[i])
            {
                for (int j = 0; j < MAX_ENEMIES; j++)
                {
                    if (CheckCollisionBoxSphere((BoundingBox){(Vector3){game->enemyPositions[j].x - 0.5f, game->enemyPositions[j].y - 0.5f, game->enemyPositions[j].z - 0.5f},
                                                              (Vector3){game->enemyPositions[j].x + 0.5f, game->enemyPositions[j].y + 0.5f, game->enemyPositions[j].z + 0.5f}},
                                                (Vector3){player1->bullets[i].x, player1->bullets[i].y, player1->bullets[i].z}, 0.1f))
                    {
                        player1->bulletActive[i] = false;

                        float x = GetRandomValue(-30, -10);
                        float z = GetRandomValue(-6, 6);
                        game->enemyPositions[j] = (Vector3){x, 0.0f, z};

                        player1->score += enemyPoints;
                    }
                }
            }
}

void Enemy::colisionConNave(Nave* player1,Game* game, int i)
{
    if (CheckCollisionBoxSphere((BoundingBox){(Vector3){game->player1Position.x - 0.5f, game->player1Position.y - 0.5f, game->player1Position.z - 0.5f},
                                                      (Vector3){game->player1Position.x + 0.5f, game->player1Position.y + 0.5f, game->player1Position.z + 0.5f}},
                                        (Vector3){game->enemyPositions[i].x, game->enemyPositions[i].y, game->enemyPositions[i].z}, 0.5f))
            {

                game->bandera1 = true;
                game->model_s1 = 0.02;
                // bloquear movimiento y disparo del jugador 1
                game->player1Position.x = -120;
                game->bulletCount = 0;

                float x = GetRandomValue(-30, -10);
                float z = GetRandomValue(-6, 6);
                game->bulletActive[i] = false;
                game->bullets[i] = (Vector3){-120, 0.0f, 0.0f};

                game->enemyPositions[i] = (Vector3){x, 0.0f, z};
                if (game->bandera1 && game->bandera2)
                {
                    game->gameOver = true;
                }
            }

}

