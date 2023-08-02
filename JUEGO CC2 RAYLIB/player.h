#ifndef PLAYER_H
#define PLAYER_H
#include <raylib.h>
#define MAX_BULLETS 100

class Player{
    public:
        Player();
        Player(Model);
        void setPosicion(Vector3);
        void setPosicionX(float);
        void setPosicionY(float);
        void setPosicionZ(float);
        Vector3 getPosicion();
        float& getPosicionX();
        float& getPosicionY();
        float& getPosicionZ();
        void setModelo(Model);
        Model getModelo();    
    private:
        Vector3 playerPosition;
        Model modelPlayer;
};

#endif
