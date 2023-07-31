#include "player.h"
#include <raylib.h>
#include <iostream>

Player::Player(){}

Player::Player(Model m1)
{
    setModelo(m1);
}

void Player::setPosicion(Vector3 pos){
    playerPosition=pos;
}
void Player::setPosicionX(float valor)
{
    playerPosition.x=valor;
}
void Player::setPosicionY(float valor)
{
    playerPosition.y=valor;
}
void Player::setPosicionZ(float valor)
{
    playerPosition.z=valor;
}
float& Player::getPosicionX()
{
    return playerPosition.x;
}
float& Player::getPosicionY()
{
    return playerPosition.y;
}
float& Player::getPosicionZ()
{
    return playerPosition.z;
}
void Player::setModelo(Model modelo){
    modelPlayer=modelo;
}
Model Player::getModelo(){
    return modelPlayer;
}
Vector3 Player::getPosicion(){
    return playerPosition;
}