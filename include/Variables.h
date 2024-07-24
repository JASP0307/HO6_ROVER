// Definición de los estados
typedef enum {
    STATE_INICIO,
    STATE_CALIBRACION,
    STATE_BUSCAR_CAJAS,
    STATE_AGARRAR_CAJA,
    STATE_BUSCAR_META,
    STATE_SOLTAR_CAJA,
} State;

// Definición de los movimientos de motores
typedef enum {
    PARAR,
    AVANZAR,
    RETROCEDER,
    DERECHA,
    IZQUIERDA,
} Mov;

// Variable global para almacenar el estado actual
State currentState = STATE_INICIO;
// Variable global para almacenar el estado actual de los motores
Mov motores = PARAR;

