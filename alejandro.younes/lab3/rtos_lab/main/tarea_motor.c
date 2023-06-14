#include <xinu.h>
#include "timer.h"

// semaforos
#define SEM_MOTOR 0

extern unsigned int timer2_velocidad_motor;

int tarea_motor() {
    // esperar señal para cambiar velocidad del motor
    while (1) {
        sync_wait(SEM_MOTOR);

        timer2_fijar_ciclo_trabajo(timer2_velocidad_motor);
    }
}
