#include "adc.h"
#include "serial.h"
#include "utils.h"

int main(void) {
    serial_init();
    adc_init();

    // Cable entre resistencia y fotorresistencia conectado a ADC0 (pin A0 Arduino Nano)
    while (1) {
        int val = adc_get(0);  // Recibir valor (entre 0 y 4095)
        val = val * 2;  // Brillo PC va de 0 a 7267, entonces duplicar valor
        serial_put_int(val);  // Comunicar valor a PC (entre 0 y 8190)
        serial_put_char('\r');
        delay_ms(200);        // Esperar que PC tome dato y cambie brillo
    }
}