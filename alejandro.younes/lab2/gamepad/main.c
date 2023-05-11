#include "adc.h"
#include "serial.h"
#include "utils.h"

#define BTN 0b00000001  // botón a PB0 (pin D8 Arduino Nano)

volatile unsigned int i;

// Botón a PB0 (pin D8 Arduino Nano)
// Pin medio de knob a ADC0 (pin A0 Arduino Nano)
int main(void) {
    inicializar_port_b();
    entrada_pin_port_b(BTN);   // PB0 es entrada
    levantar_pin_port_b(BTN);  // PB0 activa resistencia interna
    serial_init();
    adc_init();

    while (1) {
        unsigned int pulsado = 0;
        for (int i = 0; i < 3600; i++)  // botón debe pulsarse un ratito (20 ms)
            pulsado = !leer_pin_port_b(BTN);  // señal baja es pulsado
        if (pulsado) {
            serial_put_char('s');
            serial_put_char('\r');
        }
        delay_ms(30);          // dar tiempo a PC para que tome el dato
        int res = adc_get(0);  // pin medio knob a ADC0 (pin A0 Arduino Nano)
        if (res <= 1365) {     // rango 0 a 1365 escribe 'a'
            serial_put_char('a');
            serial_put_char('\r');
        } else if (res >= 2730) {  // rango 2730 a 4096 escribe 'd'
            serial_put_char('d');
            serial_put_char('\r');
        } else {  // rango 1366 a 2729 es "zona muerta" (hacer nada)
            // serial_put_char('?');   // escribe '?', será interpretado como
            // serial_put_char('\r');  // ausencia de entrada por la PC
        }
    }
}
