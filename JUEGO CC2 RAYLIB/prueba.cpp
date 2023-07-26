#include <iostream>
#include <raylib.h>
#include "prueba.h"

#define MAX_ENEMIES 6
#define ENEMY_SPEED 20
#define MAX_BULLETS 100
using namespace std;

void prueba(){
    
    const int screenWidth = 940;
    const int screenHeight = 480;
    DrawText("PRUEBA CABECERA", screenWidth / 2 - MeasureText("PRUEBA CABECERA", 20) / 2, screenHeight / 2 + 120, 20, GRAY);
                   
}