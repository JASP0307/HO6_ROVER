# HO6_ROVER
=============== AVANCES 07/23/24 - JSP ===============

El día de hoy el enfoque principal fue iniciar a desarrollar cada una de las tareas para integrarlas una a una al código de control general. Las tareas ya trabajadas fueron:

    - configTask: En esta tarea se espera que el usuario oprima uno de dos botones para seleccionar entre STATE_CALIBRACION o STATE_BUSCAR_CAJAS.

    - motorsTask: En esta tarea se controla el movimiento de los motores para: detenerse, avanzar, izquierda, derecha, retroceder y línea. Este último está aún por verificarse en función de lo que se requiera.

    - sensColorTask: En esta tarea, dependiendo del currentState se llama la función de calibrar o detectarColor. Esta segunda se utilizará en STATE_BUSCAR_CAJAS y STATE_BUSCAR_META.

Queda pendiente:
1. Confirmar el sensor de color a utilizar.
2. Trabajar las tareas de:
    - gripperTask
    - camTask
3. Hacer pruebas con la PixyCam.
4. Definir el listado de IO_Pins en función de los componentes actuales.

======================================================