#include <xinu.h>
#include "timer.h"

// semaforos
#define SEM_SERVO 1

extern unsigned int timer1_angulo;

int tarea_servo() {
    // esperar señal para cambiar angulo del servo
    while (1) {
        sync_wait(SEM_SERVO);

        timer1_fijar_angulo(timer1_angulo);
    }
}
