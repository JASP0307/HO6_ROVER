#include "Arduino.h"
#include <Arduino_FreeRTOS.h>

// Definición de los estados
typedef enum {
    STATE_INICIO,
    STATE_CALIBRACION,
    STATE_BUSCAR_CAJAS,
    STATE_AGARRAR_CAJA,
    STATE_BUSCAR_META,
    STATE_SOLTAR_CAJA,
} State;

// Variable global para almacenar el estado actual
State currentState = STATE_INICIO;

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

// Configuración de las tareas
void setup() {
    Serial.begin(9600); // Inicializar comunicación serial para depuración

    xTaskCreate(stateMachineTask, "StateMachine", 1000, NULL, 1, &Task_Handle_1);
    xTaskCreate(configTask, "Configuracion", 1000, NULL, 1, &Task_Handle_2);
    xTaskCreate(motorsTask, "Desplazamiento", 1000, NULL, 1, &Task_Handle_3);
    xTaskCreate(sensColorTask, "RGB", 1000, NULL, 1, &Task_Handle_4);
    xTaskCreate(gripperTask, "Agarre", 1000, NULL, 1, &Task_Handle_5);
    xTaskCreate(camTask, "Camara", 1000, NULL, 1, &Task_Handle_6);

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
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Espera un tiempo antes de revisar el estado nuevamente
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

    // Lógica para cambiar al siguiente estado
    currentState = STATE_CALIBRACION;
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

    // Lógica para cambiar al siguiente estado
    currentState = STATE_BUSCAR_CAJAS;
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

    // Lógica para cambiar al siguiente estado
    currentState = STATE_AGARRAR_CAJA;
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

    // Lógica para cambiar al siguiente estado
    currentState = STATE_BUSCAR_META;
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

    // Lógica para cambiar al siguiente estado
    currentState = STATE_SOLTAR_CAJA;
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

    // Lógica para volver al estado inicial o algún otro estado
    currentState = STATE_INICIO;
}

// Implementación de las tareas de los estados
void configTask(void *pvParameters) {
    (void) pvParameters;

    for (;;) {
        // Código de configuración
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Temporización para simular trabajo
    }
}

void motorsTask(void *pvParameters) {
    (void) pvParameters;

    for (;;) {
        // Código de desplazamiento
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Temporización para simular trabajo
    }
}

void sensColorTask(void *pvParameters) {
    (void) pvParameters;

    for (;;) {
        // Código de sensor de color
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Temporización para simular trabajo
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
        // Código de cámara
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Temporización para simular trabajo
    }
}