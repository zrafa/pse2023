#include "serial.h"
#include "utils.h"

//  8 (Uno) =  D8 (Nano) = PB0 (328P)
// 10 (Uno) = D10 (Nano) = PB2 (328P)

#define ECHO 0b00000001  // PB0 conectado a pin ECHO de HC-SR04
#define TRIG 0b00000100  // PB2 conectado a pin TRIG de HC-SR04

void mostrar_medida(int valor, char* unidad) {
    serial_put_int(valor, 4);
    serial_put_str(" ");
    serial_put_str(unidad);
    serial_put_str("\n");
}

void main() {
    volatile unsigned char* PIN_B = (unsigned char*)0x23;
    volatile unsigned char* DDR_B = (unsigned char*)0x24;
    volatile unsigned char* PRT_B = (unsigned char*)0x25;
    unsigned long t;
    unsigned long tiempo_us;
    unsigned int distancia_cm;

    serial_init();        // salida de texto por USB
    *PRT_B = 0b00000000;  // inicializar PB
    *DDR_B = 0b00000100;  // PB0 entrada, PB2 salida

    while (1) {
        t = 0;
        *PRT_B = *PRT_B | TRIG;         // levantar trigger
        delay_10us();                   // esperar que tome solicitud
        *PRT_B = *PRT_B ^ TRIG;         // bajar trigger
        while ((*PIN_B & ECHO) != 1) {  // esperar que echo levante
        }
        while ((*PIN_B & ECHO) == 1) {  // contar duración echo
            t++;
            delay_10us();
        }
        tiempo_us = t * 10;
        distancia_cm = tiempo_us / 58;
        mostrar_medida(distancia_cm, "cm");
        delay_ms(500);  // esperar para solicitar nueva medición
    }
}