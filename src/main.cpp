#include "Arduino.h"
#include <Arduino_FreeRTOS.h>
#include "Tasks.h"
#include "IO_Pins.h"

//Pixy2 pixy;

// Configuración de las tareas
void setup() {
    Serial.begin(9600); // Inicializar comunicación serial

// Sensor de colores
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(S_OUT, INPUT);

    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);

//    pixy.init(); // Inicializar Pixy Cam

    xTaskCreate(stateMachineTask, "StateMachine", 2048, NULL, 1, &Task_Handle_1);
    xTaskCreate(configTask, "Configuracion", 2048, NULL, 1, &Task_Handle_2);
    xTaskCreate(motorsTask, "Desplazamiento", 2048, NULL, 1, &Task_Handle_3);
    xTaskCreate(sensColorTask, "RGB", 2048, NULL, 1, &Task_Handle_4);
    xTaskCreate(gripperTask, "Agarre", 2048, NULL, 1, &Task_Handle_5);
    xTaskCreate(camTask, "Camara", 2048, NULL, 1, &Task_Handle_6);

    // Inicialmente suspender todas las tareas excepto la de la máquina de estados
    vTaskSuspend(Task_Handle_2);
    vTaskSuspend(Task_Handle_3);
    vTaskSuspend(Task_Handle_4);
    vTaskSuspend(Task_Handle_5);
    vTaskSuspend(Task_Handle_6);

    vTaskStartScheduler();
}

void loop() {}

// Implementación de la tarea de la máquina de estados
void stateMachineTask(void *pvParameters) {
    for (;;) {
        switch (currentState) {
            case STATE_INICIO:
                handleStateInicio();
                break;

            case STATE_CALIBRACION:
                handleStateCalibracion();
                break;

            case STATE_BUSCAR_CAJAS:
                handleStateBuscarCajas();
                break;

            case STATE_AGARRAR_CAJA:
                handleStateAgarrarCaja();
                break;

            case STATE_BUSCAR_META:
                handleStateBuscarMeta();
                break;

            case STATE_SOLTAR_CAJA:
                handleStateSoltarCaja();
                break;

            default:
                // Manejo de estado desconocido
                break;
        }
        vTaskDelay(500 / portTICK_PERIOD_MS); // Espera un tiempo antes de revisar el estado nuevamente
    }
}

// Implementación de las funciones de manejo de estado
void handleStateInicio() {
    Serial.println("Estado: INICIO");
    // Tareas a utilizar
    vTaskResume(Task_Handle_2); // Configuracion
    // Tareas a suspender
    vTaskSuspend(Task_Handle_3); // Desplazamiento
    vTaskSuspend(Task_Handle_4); // RGB              
    vTaskSuspend(Task_Handle_5); // Agarre
    vTaskSuspend(Task_Handle_6); // Camara
}

void handleStateCalibracion() {
    Serial.println("Estado: CALIBRACION");
    // Tareas a utilizar
    vTaskResume(Task_Handle_4); // RGB
    // Tareas a suspender
    vTaskSuspend(Task_Handle_2); // Configuracion
    vTaskSuspend(Task_Handle_3); // Desplazamiento
    vTaskSuspend(Task_Handle_5); // Agarre
    vTaskSuspend(Task_Handle_6); // Camara 
}

void handleStateBuscarCajas() {
    Serial.println("Estado: BUSCAR CAJAS");
    // Tareas a utilizar
    vTaskResume(Task_Handle_3); // Desplazamiento
    vTaskResume(Task_Handle_4); // RGB
    vTaskResume(Task_Handle_6); // Camara
    // Tareas a suspender
    vTaskSuspend(Task_Handle_2); // Configuracion
    vTaskSuspend(Task_Handle_5); // Agarre
}

void handleStateAgarrarCaja() {
    Serial.println("Estado: AGARRAR CAJA");
    // Tareas a utilizar
    vTaskResume(Task_Handle_5); // Agarre
    // Tareas a suspender
    vTaskSuspend(Task_Handle_2); // Configuracion
    vTaskSuspend(Task_Handle_3); // Desplazamiento
    vTaskSuspend(Task_Handle_4); // RGB
    vTaskSuspend(Task_Handle_6); // Camara
}

void handleStateBuscarMeta() {
    Serial.println("Estado: BUSCAR META");
    // Tareas a utilizar
    vTaskResume(Task_Handle_3); // Desplazamiento
    vTaskResume(Task_Handle_4); // RGB
    vTaskResume(Task_Handle_6); // Camara
    // Tareas a suspender
    vTaskSuspend(Task_Handle_2); // Configuracion
    vTaskSuspend(Task_Handle_5); // Agarre
}

void handleStateSoltarCaja() {
    Serial.println("Estado: SOLTAR CAJA");
    // Tareas a utilizar
    vTaskResume(Task_Handle_5); // Agarre
    // Tareas a suspender
    vTaskSuspend(Task_Handle_2); // Configuracion
    vTaskSuspend(Task_Handle_3); // Desplazamiento
    vTaskSuspend(Task_Handle_4); // RGB
    vTaskSuspend(Task_Handle_6); // Camara
}