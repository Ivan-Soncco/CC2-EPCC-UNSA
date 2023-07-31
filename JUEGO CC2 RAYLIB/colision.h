#ifndef COLISION_H
#define COLISION_H
#include "nave.h"
#include "enemy.h"

class Colision{
    public:

        Colision(){};
        bool colisionan(Nave*,Enemy*);
};


#endif