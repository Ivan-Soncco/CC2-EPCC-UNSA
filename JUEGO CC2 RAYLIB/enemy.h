#ifndef ENEMY_H
#define ENEMY_H
#include <raylib.h>
#include <iostream>
#include "player.h"
#include "nave.h"
#define MAX_ENEMIES 6

class Game;

class Enemy : public Player{
    public:
        Enemy(){};
        
        Enemy(const Enemy& otro)= default;
        Enemy(Model);
        Enemy& operator=(const Enemy& otro);
        int getEnemyPoints();
        void msj(int);
        void move(double);
        void colisionConBala(Nave*,int);
        void colisionConNave(Nave*,int);
        void reiniciarEnemy();
    private:
        const int enemyPoints= 10;
        
};
#endif