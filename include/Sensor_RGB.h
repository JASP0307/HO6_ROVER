#include "Arduino.h"
#include "IO_Pins.h"

// Variables para sensor de color
int RedPW = 0;
int GreenPW = 0;
int BluePW = 0;
// Valores a configurar luego de la calibracion
int RedMin = 0;
int RedMax = 0;
int GreenMin = 0;
int GreenMax = 0;
int BlueMin = 0;
int BlueMax = 0;

int RedVal, GreenVal, BlueVal;

int getRedPW(){

    // Para leer solo el ROJO
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    int PW;
    PW = pulseIn(S_OUT, LOW);
    return PW;
}

int getGreenPW(){

    // Para leer solo el VERDE
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    int PW;
    PW = pulseIn(S_OUT, LOW);
    return PW;
}

int getBluePW(){

    // Para leer solo el AZUL
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    int PW;
    PW = pulseIn(S_OUT, LOW);
    return PW;
}

void calibrar(){
    RedPW = getBluePW();
    delay(200);
    
    GreenPW = getGreenPW();
    delay(200);

    BluePW = getBluePW();
    delay(200);

    Serial.print("Red PW = ");
    Serial.print(RedPW);
    Serial.print(" - Green PW = ");
    Serial.print(GreenPW);
    Serial.print(" - Blue PW = ");
    Serial.println(BluePW);
}

void detectarColor(){

    RedPW = getBluePW();
    RedVal = map(RedPW, RedMin, RedMax, 255, 0);
    delay(200);
    
    GreenPW = getGreenPW();
    GreenVal = map(GreenPW, GreenMin, GreenMax, 255, 0);
    delay(200);

    BluePW = getBluePW();
    BlueVal = map(BluePW, BlueMin, BlueMax, 255, 0);
    delay(200);
    Serial.print("Red = ");
    Serial.print(RedVal);
    Serial.print(" - Green = ");
    Serial.print(GreenVal);
    Serial.print(" - Blue = ");
    Serial.println(BlueVal);
}

