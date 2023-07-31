#include "enemy.h"
//#include "game.h"
#include <raylib.h>
#include <iostream>
#include "nave.h"

#define MAX_ENEMIES 6
#define ENEMY_SPEED 20




/*
Game Enemy::getGamefromEnemy(){
    return Game();
}*/

Enemy::Enemy(Model m1)
{
    setModelo(m1);
}

int Enemy::getEnemyPoints()
{
    return enemyPoints;
}


void Enemy::msj(int i){
    const int screenWidth = 940;
    const int screenHeight = 480;
    //const char* enemyName = "Enemy ";
    //char enemyIndex[10];
    //sprintf(enemyIndex,i);

    DrawText(TextFormat("Enemy %d",(i+1)), screenWidth / 2 - MeasureText("Enemy %d", 20) / 2, screenHeight / 2 + ((i+2)*40), 20, GRAY);  
}

Enemy& Enemy::operator=(const Enemy& otro){
    Enemy tmp(otro);
    std::swap(*this,tmp);
    return *this;
}

void Enemy::move(double elapsedTime){
    getPosicionX() -= (ENEMY_SPEED + elapsedTime * 5) * GetFrameTime();
            
            if (getPosicionX() < -101.0f)
            {
                float x = GetRandomValue(-30, -10);
                float z = GetRandomValue(-6, 6);
                setPosicion((Vector3){x, 0.0f, z});
            }

            // Limit enemy positions within the vertical bounds
            if (getPosicionY() < -5.0f)
                setPosicionY(-5.0f);
            else if (getPosicionY() > 5.0f)
                setPosicionY(5.0f);
}

void Enemy::colisionConBala(Nave* player1,int i){
    if (CheckCollisionBoxSphere((BoundingBox){(Vector3){getPosicionX()- 0.5f, getPosicionY() - 0.5f, getPosicionZ() - 0.5f},
                                                              (Vector3){getPosicionX() + 0.5f, getPosicionY() + 0.5f, getPosicionZ() + 0.5f}},
                                                (Vector3){player1->arrayBalas[i].getPosicionX(), player1->arrayBalas[i].getPosicionY(), player1->arrayBalas[i].getPosicionZ()}, 0.1f))
                    {
                        player1->bulletActive[i] = false;

                        float x = GetRandomValue(-30, -10);
                        float z = GetRandomValue(-6, 6);
                        setPosicion((Vector3){x, 0.0f, z});

                        player1->score += getEnemyPoints();
                    }
}
void Enemy::colisionConNave(Nave* nave,int i){
    if (CheckCollisionBoxSphere((BoundingBox){(Vector3){nave->getPosicionX() - 0.5f, nave->getPosicionY() - 0.5f, nave->getPosicionZ() - 0.5f},
                                                      (Vector3){nave->getPosicionX() + 0.5f, nave->getPosicionY() + 0.5f, nave->getPosicionZ() + 0.5f}},
                                        (Vector3){getPosicionX(), getPosicionY(), getPosicionZ()}, 0.5f))
            {

                nave->bandera= true;
                nave->model = 0.02;
                // bloquear movimiento y disparo del jugador 1
                nave->setPosicionX(-120);
                nave->bulletCount = 0;

                float x = GetRandomValue(-30, -10);
                float z = GetRandomValue(-6, 6);
                nave->bulletActive[i] = false;
                nave->arrayBalas[i].setPosicion((Vector3){-120, 0.0f, 0.0f});

                setPosicion((Vector3){x, 0.0f, z});
                
            }
}

void Enemy::reiniciarEnemy(){
    
    float x = GetRandomValue(-30, -10);
    float z = GetRandomValue(-6, 6);
    setPosicion((Vector3){x, 0.0f, z});
}