#ifndef NAVE_H
#define NAVE_H
#include <raylib.h>
#include "player.h"
#include "bala.h"
#include <memory>

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
        Bala arrayBalas[MAX_BULLETS];
        //std::unique_ptr<Bala> arrayBalas[MAX_BULLETS];
        int score{0};
        bool bandera=false;
        float model = 0.2;
        void reiniciarNave();
};

#endif