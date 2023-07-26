#ifndef NAVE_H
#define NAVE_H
#include <raylib.h>
#include "player.h"
#define MAX_BULLETS 100

class Nave: public Player{
    public:
        Nave();
        Nave(Model);
        void movIzquierda();
        void movDerecha();
        void disparar();
        void moverBala();
        int bulletCount= MAX_BULLETS;
        bool bulletActive[MAX_BULLETS];
        Vector3 bullets[MAX_BULLETS];
        int score{0};
};


#endif