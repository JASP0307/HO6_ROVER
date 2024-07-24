#include <Arduino_FreeRTOS.h>
#include "Variables.h"
#include "Motores.h"
#include "Sensor_RGB.h"

// Declaraciones de las funciones de las tareas de los estados
void configTask(void *pvParameters);
void motorsTask(void *pvParameters);
void sensColorTask(void *pvParameters);
void gripperTask(void *pvParameters);
void camTask(void *pvParameters);

// Declaraciones de las funciones de manejo de estado
void handleStateInicio();
void handleStateCalibracion();
void handleStateBuscarCajas();
void handleStateAgarrarCaja();
void handleStateBuscarMeta();
void handleStateSoltarCaja();

TaskHandle_t Task_Handle_1;
TaskHandle_t Task_Handle_2;
TaskHandle_t Task_Handle_3;
TaskHandle_t Task_Handle_4;
TaskHandle_t Task_Handle_5;
TaskHandle_t Task_Handle_6;

// Declaración de la tarea de la máquina de estados
void stateMachineTask(void *pvParameters);

// Implementación de las tareas de los estados
void configTask(void *pvParameters) {
    (void) pvParameters;

    for (;;) {
        // Código de configuración
        if (digitalRead(CALIB_BUTTON)){
            currentState = STATE_CALIBRACION;
        }
        else if (digitalRead(START_BUTTON))
        {
            currentState = STATE_BUSCAR_CAJAS;
        }
        else{
            currentState = STATE_INICIO;
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Temporización para simular trabajo
    }
}

void motorsTask(void *pvParameters) {
    (void) pvParameters;

    for (;;) {
        // Código de desplazamiento
        switch (motores)
        {
        case AVANZAR:
            avanzar();
            break;

        case RETROCEDER:
            retroceder();
            break;

        case DERECHA:
            derecha();
            break;

        case IZQUIERDA:
            izquierda();
            break;

        case PARAR:
            detenerse();

        default:
            detenerse();
            break;
        }
        vTaskDelay(100 / portTICK_PERIOD_MS); // Temporización para simular trabajo
    }
}

void sensColorTask(void *pvParameters) {
    (void) pvParameters;

    for (;;) {
        // Código de sensor de color
        switch (currentState)
        {
        case STATE_CALIBRACION:
            calibrar();
            currentState = STATE_INICIO;
            break;

        case STATE_BUSCAR_CAJAS:
            detectarColor();
            break;
        case STATE_BUSCAR_META:
            detectarColor();
            break;
        default:
            break;
        }
        vTaskDelay(100 / portTICK_PERIOD_MS); // Temporización para simular trabajo
    }
}

void gripperTask(void *pvParameters) {
    (void) pvParameters;

    for (;;) {
        // Código de agarre
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Temporización para simular trabajo
    }
}

void camTask(void *pvParameters) {
    (void) pvParameters;

    for (;;) {
        // Código de la cámara
/*        pixy.ccc.getBlocks();
        if (pixy.ccc.numBlocks) {
            for (int i = 0; i < pixy.ccc.numBlocks; i++) {
                // Procesar los datos de los bloques
            }
        }
*/
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Temporización para simular trabajo
    }
}