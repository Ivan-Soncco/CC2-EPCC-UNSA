#include "colision.h"


bool Colision::colisionan(Nave* player, Enemy* arrayEnemigos){
    if (CheckCollisionBoxSphere((BoundingBox){(Vector3){player->getPosicionX() - 0.5f, player->getPosicionY() - 0.5f, player->getPosicionZ() - 0.5f},
                                                      (Vector3){player->getPosicionX() + 0.5f, player->getPosicionY() + 0.5f, player->getPosicionZ() + 0.5f}},
                                        (Vector3){arrayEnemigos->getPosicionX(), arrayEnemigos->getPosicionY(), arrayEnemigos->getPosicionZ()}, 0.5f))
                                        return true;
    else   
        return false;
}