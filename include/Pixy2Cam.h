#include "Arduino.h"
#include <Pixy2.h>

Pixy2 pixy;

int cont = 0;
int signature, x, y, width, height;
float cx, cy, area;
float deadZone = 0.15;

float mapfloat(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (float)(x - in_min)*(out_max - out_min) / (float)(in_max - in_min) + out_min;
}

float pixyCheck(){

    pixy.ccc.getBlocks();

    if (pixy.ccc.numBlocks)
    {
        signature = pixy.ccc.blocks[0].m_signature;
        height = pixy.ccc.blocks[0].m_height;
        width = pixy.ccc.blocks[0].m_width;
        x = pixy.ccc.blocks[0].m_x;
        y = pixy.ccc.blocks[0].m_y;
        cx = (x + (width / 2));
        cy = (y + (height / 2));
        cx = mapfloat(cx, 0, 320, -1, 1);
        cy = mapfloat(cy, 0, 200, 1, -1);
        area = width * height;
/*
        Serial.print("sig: ");
        Serial.print(signature);
        Serial.print(" x:");
        Serial.print(x);
        Serial.print(" y:");
        Serial.print(y);
        Serial.print(" width:");
        Serial.print(width);
        Serial.print(" height:");
        Serial.print(height);
        Serial.print(" cx:");
        Serial.print(cx);
        Serial.print(" cy:");
        Serial.print(cy);        
*/
    }else
    {
        cont += 1;
        if (cont == 100){
            cont = 0;
            cx = 0;
        }
    }
    return cx;
}
