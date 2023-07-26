#include "nave.h"
#include <raylib.h>
#include <iostream>

Nave::Nave(){}

Nave::Nave(Model m1)
{
    setModelo(m1);
}
void Nave::movIzquierda(){
    getPosicionZ()-= 0.2f;
}
void Nave::movDerecha(){
    getPosicionZ()+= 0.2f;
}

void Nave::disparar(){
    
            bool bulletFired = false;

            for (int i = 0; i < MAX_BULLETS; i++)
            {
                if (!bulletActive[i])
                {
                    bullets[i] = (Vector3){getPosicionX(), getPosicionY(), getPosicionZ()};
                    bulletActive[i] = true;
                    bulletFired = true;
                    break;
                }
            }

            if (bulletFired)
            {
                bulletCount--;
            }
    
}
void Nave::moverBala(){
    const int screenWidth = 940;
    for (int i = 0; i < MAX_BULLETS; i++)
            {
                if (bulletActive[i])
                {
                    bullets[i].x += 0.2f;
    
                    if (bullets[i].x > screenWidth)
                    {
                        bulletActive[i] = false;
                    }
                }
            }
}

