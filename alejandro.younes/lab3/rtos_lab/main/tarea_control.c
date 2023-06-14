#include <xinu.h>
#include "serial.h"
#include "utils.h"

#define OC2B 0b00001000  // PD3 = OC2B =  D3 (Nano)

// semaforos
#define SEM_SERVO 1

extern unsigned int timer1_angulo;

int tarea_control() {
    unsigned char tecla_pulsada;
    // cada 151 ms consultar si se presionó una tecla
    while (1) {
        sleepms(151);

        if (serial_get_char_ready()) {
            tecla_pulsada = serial_get_char();
            switch (tecla_pulsada) {
                case 'b': // detener motor
                    portd_como_entrada_pin(OC2B);
                    break;
                case 'n': // iniciar motor
                    portd_como_salida_pin(OC2B);
                    break;
                case 'a': // girar servo a la izquierda 
                    if (timer1_angulo > 0) {
                        timer1_angulo--;
                        sync_signal(SEM_SERVO);
                    }
                    break;
                case 'd': // girar servo a la derecha
                    if (timer1_angulo < 180) {
                        timer1_angulo++;
                        sync_signal(SEM_SERVO);
                    }
                    break;
                default: // las otras teclas no hacen nada
                    break;
            }
        }
    }
}
