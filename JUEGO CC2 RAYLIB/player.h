#ifndef PLAYER_H
#define PLAYER_H
#include <raylib.h>
#define MAX_BULLETS 100

class Player{
    public:
        Player();
        Player(Model);
        //void movIzquierda();
        //void movDerecha();
        void setPosicion(Vector3);
        void setPosicionZ(float);
        float& getPosicionX();
        float& getPosicionY();
        float& getPosicionZ();
        //void disparar();
        void setModelo(Model);
        Model getModelo();
        //int bulletCount= MAX_BULLETS;
        //bool bulletActive[MAX_BULLETS];
        //Vector3 bullets[MAX_BULLETS];
        //int score{0};
        bool bandera=false;
        
    private:
        Vector3 playerPosition;
        Model modelPlayer;
};



#endif
