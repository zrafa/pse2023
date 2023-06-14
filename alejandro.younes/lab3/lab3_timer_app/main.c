#include <avr/interrupt.h>
#include <avr/io.h>
#include "serial.h"
#include "timer.h"
#include "utils.h"

unsigned int timer1_angulo = 0;

#define OC1A 0b00000010  // PB1 = OC1A =  D9 (Nano)

int main(void) {
    unsigned char tecla = '?';

    inicializar_port_b();
    salida_pin_port_b(OC1A);
    timer1_init();
    serial_init();

    while (1) {
        tecla = serial_get_char();
        switch (tecla) {
            case 'a':
                if (timer1_angulo > 0) {
                    timer1_angulo--;
                    timer1_fijar_angulo(timer1_angulo);
                }
                break;
            case 'd':
                if (timer1_angulo < 180) {
                    timer1_angulo++;
                    timer1_fijar_angulo(timer1_angulo);
                }
                break;
            default:
                break;
        }
        tecla = '?';
    }
}
