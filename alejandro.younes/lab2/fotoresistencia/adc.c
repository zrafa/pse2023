/**********************************************************************
 *
 * adc.c - Driver del ADC del atmega328p
 *
 * META : ocultar el hardware a la aplicacion
 *
 **********************************************************************/

#include <stdint.h>  // para los tipos de datos, p.e.: uint8_t

// bits registro ADMUX
#define MUX0 0b00000001
#define MUX1 0b00000010
#define MUX2 0b00000100
#define MUX3 0b00001000
#define ADLAR 0b00100000
#define REFS0 0b01000000
#define REFS1 0b10000000

// bits registro ADCSRA
#define ADPS0 0b00000001
#define ADPS1 0b00000010
#define ADPS2 0b00000100
#define ADSC 0b01000000
#define ADEN 0b10000000

// Estructura de datos del driver ADC
typedef struct {
    uint8_t adcl;    // ADC Data Register Low
    uint8_t adch;    // ADC Data Register High
    uint8_t adcsra;  // ADC Status Register A
    uint8_t adcsrb;  // ADC Status Register B
    uint8_t admux;   // ADC Multiplexor
    uint8_t reserved;
    uint8_t DIDR0;  // Digital Input Disable Register 0
} volatile adc_t;

adc_t* adc = (adc_t*)(0x78);  // Dirección del primer registro

void adc_init() {
    // Resultado ajustado a derecha (leer primero ADCL)
    adc->admux = adc->admux & ~ADLAR;  // ADLAR en 0

    // Usar VCC con capacitor externo
    adc->admux = adc->admux | REFS0;   // REFS0 en 1
    adc->admux = adc->admux & ~REFS1;  // REFS1 en 0

    //  50 KHz = 0.05 MHz
    // 200 KHz = 0.2 MHz
    // 8 MHz / 0.05 MHz = 160
    // 8 MHz / 0.2 MHz = 40
    // Entonces rango preescalar está en 40-160 (conviene cerca de 40)
    // Usar preescalar 64, 8 MHz / 64 = 0.125 MHz
    adc->adcsra = adc->adcsra & ~ADPS0;  // ADPS0 en 0
    adc->adcsra = adc->adcsra | ADPS1;   // ADPS1 en 1
    adc->adcsra = adc->adcsra | ADPS2;   // ADPS2 en 1

    // Habilitar ADC
    adc->adcsra = adc->adcsra | ADEN;  // ADEN en 1
}

// Obtener entrada analogica conectada al multiplexor
int adc_get(int input) {
    switch (input) {
        case 0:
            adc->admux = adc->admux & ~MUX0;  // MUX0 en 0
            adc->admux = adc->admux & ~MUX1;  // MUX1 en 0
            adc->admux = adc->admux & ~MUX2;  // MUX2 en 0
            adc->admux = adc->admux & ~MUX3;  // MUX3 en 0
            break;
        case 1:
            adc->admux = adc->admux | MUX0;   // MUX0 en 1
            adc->admux = adc->admux & ~MUX1;  // MUX1 en 0
            adc->admux = adc->admux & ~MUX2;  // MUX2 en 0
            adc->admux = adc->admux & ~MUX3;  // MUX3 en 0
            break;
        case 2:
            adc->admux = adc->admux & ~MUX0;  // MUX0 en 0
            adc->admux = adc->admux | MUX1;   // MUX1 en 1
            adc->admux = adc->admux & ~MUX2;  // MUX2 en 0
            adc->admux = adc->admux & ~MUX3;  // MUX3 en 0
            break;
        case 3:
            adc->admux = adc->admux | MUX0;   // MUX0 en 1
            adc->admux = adc->admux | MUX1;   // MUX1 en 1
            adc->admux = adc->admux & ~MUX2;  // MUX2 en 0
            adc->admux = adc->admux & ~MUX3;  // MUX3 en 0
            break;
        case 4:
            adc->admux = adc->admux & ~MUX0;  // MUX0 en 0
            adc->admux = adc->admux & ~MUX1;  // MUX1 en 0
            adc->admux = adc->admux | MUX2;   // MUX2 en 1
            adc->admux = adc->admux & ~MUX3;  // MUX3 en 0
            break;
        case 5:
            adc->admux = adc->admux | MUX0;   // MUX0 en 1
            adc->admux = adc->admux & ~MUX1;  // MUX1 en 0
            adc->admux = adc->admux | MUX2;   // MUX2 en 1
            adc->admux = adc->admux & ~MUX3;  // MUX3 en 0
            break;
        case 6:
            adc->admux = adc->admux & ~MUX0;  // MUX0 en 0
            adc->admux = adc->admux | MUX1;   // MUX1 en 1
            adc->admux = adc->admux | MUX2;   // MUX2 en 1
            adc->admux = adc->admux & ~MUX3;  // MUX3 en 0
            break;
        case 7:
            adc->admux = adc->admux | MUX0;   // MUX0 en 1
            adc->admux = adc->admux | MUX1;   // MUX1 en 1
            adc->admux = adc->admux | MUX2;   // MUX2 en 1
            adc->admux = adc->admux & ~MUX3;  // MUX3 en 0
            break;
        case 8:
            adc->admux = adc->admux & ~MUX0;  // MUX0 en 0
            adc->admux = adc->admux & ~MUX1;  // MUX1 en 0
            adc->admux = adc->admux & ~MUX2;  // MUX2 en 0
            adc->admux = adc->admux | MUX3;   // MUX3 en 1
            break;
        default:
            break;
    }

    // ADSC en 1 para iniciar conversión
    adc->adcsra = adc->adcsra | ADSC;

    // Esperar que finalize conversión (ADSC en 0)
    while (adc->adcsra & ADSC) {
    }

    // Leer resultado (primero ADCL)
    int ADCL = adc->adcl;
    int ADCH = adc->adch;
    int res = (ADCH << 8) | ADCL;
    return res;
}
