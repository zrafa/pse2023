/**********************************************************************
 *
 * adc.c - Driver del ADC del atmega328p
 *
 * META : ocultar el hardware a la aplicacion
 *
 **********************************************************************/

#include <stdint.h> /* para los tipos de datos. Ej.: uint8_t */
#include "adc.h"

// admux register macros
#define ADMUX_INIT 0x40

// adcsra register macros
#define ADCSRA_EN 0x80  // Enable device bits configuration
#define ADCSRA_ADP 0x07 // Prescalar bits configuration
#define ADCSRA_INIT (ADCSRA_ADP | ADCSRA_EN)
#define ADSC 0x40 // ADC start convertion bit

/* Estructura de datos del driver ADC */
typedef struct
{
        uint8_t adcl;    // ADC Data Register Low
        uint8_t adch;    // ADC Data Register High
        uint8_t adc_sra; // ADC Control and Status Register A
        uint8_t adc_srb; // ADC Control and Status Register B
        uint8_t admux;   // ADC Multiplexer Selection Register
} volatile adc_t;

volatile adc_t *adc = (adc_t *)(0x78); // Puntero a la direccion de datos de la base de los registros

void adc_init()
{
        adc->admux = ADMUX_INIT;
        adc->adc_sra = ADCSRA_INIT;
}

int adc_get(char input)
{
        int low, high, res;

        if (input < 0 || input > 8)
                return -1;

        /* 1. Selects which analog input is connected to the ADC */
        adc->admux = adc->admux | input;

        /* 2. Write this bit to one to start each conversion */
        adc->adc_sra = adc->adc_sra | ADSC;

        /* 3. When conversion is complete, it returns to zero */
        while (adc->adc_sra & ADSC)
        {
        }

        /* 4. When conversion is complete, the result is found in these registers */
        /* IMPORTANT: ADCL must be read first, then ADCH */
        low = adc->adcl;
        high = adc->adch;
        res = high << 8 | low;

        return res;
}
