#include "nave.h"
#include <raylib.h>
#include "bala.h"
#include <iostream>
#include <memory>
#define MAX_BULLETS 100

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
            
            /*
            //for (int i = 0; i < MAX_BULLETS; i++){
            if(i<MAX_BULLETS){
                arrayBalas[i].setPosicion(getPosicion());
                balaDraw=arrayBalas[i].getPosicion();
            }
            
            //}
            i++;*/
            
            bool bulletFired = false;

            for (int i = 0; i < MAX_BULLETS; i++)
            {
                if (!bulletActive[i])
                {
                    //arrayBalas[i]= std::make_unique<Bala>();
                    arrayBalas[i].setPosicion(getPosicion());
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
                    arrayBalas[i].getPosicionX()+= 0.2f;
    
                    if (arrayBalas[i].getPosicionX() > screenWidth)
                    {
                        bulletActive[i] = false;
                    }
                }
            }        
}

void Nave::reiniciarNave(){
    for (int i = 0; i < MAX_BULLETS; i++)
        {
            bulletActive[i] = false;
        }

    bulletCount= MAX_BULLETS;
    score = 0;
    model=0.2;
    bandera=false;
    //setPosicion((Vector3){-99.0f, 0.0f, -1.0f});
}

