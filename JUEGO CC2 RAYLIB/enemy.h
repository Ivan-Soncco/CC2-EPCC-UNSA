#ifndef ENEMY_H
#define ENEMY_H
#include <raylib.h>
#include "player.h"
#include "nave.h"
#include "game.h"
#define MAX_ENEMIES 6

class Enemy : public Player{
    public:
        Enemy();
        Enemy(Model);
        int getEnemyPoints();
        void moverEnemigo(Game* game, int i);
        void colision(Nave* player1,Game* game, int i);
        void colisionConNave(Nave* player1,Game* game, int i);
    private:
        const int enemyPoints= 10;

};


#endif