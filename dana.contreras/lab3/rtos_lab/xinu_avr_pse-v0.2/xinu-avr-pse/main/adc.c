/**********************************************************************
 *
 * adc.c - Driver del ADC del atmega328p
 *
 * META : ocultar el hardware a la aplicacion
 *
 **********************************************************************/

#include <stdint.h>
#include "adc.h"

typedef struct
{
        uint8_t adcl; /* ADC Data Register Low */
        uint8_t adch;
        uint8_t adcsra; /* ADC Control and Status Register A */
        uint8_t adcsrb;
        uint8_t admux; /* ADC Multiplexer Selection Register */
        uint8_t reserved;
        uint8_t didr0;

} volatile adc_t;

volatile adc_t *adc = (adc_t *) (0x78);

#define ADSC 6
#define ADLAR 5

void adc_init()
{
        adc->admux = 0x40; // voltaje vcc con capacitor externo.
        adc->admux |= (1<<ADLAR);
        adc->adcsra = 0x80; // habilitar periferico.
        adc->adcsra |= 0x04;  // prescalar
}       

int adc_get(char input)
{
        // Devuelve un valor de 8 bits de la conversión ADC entrada input.
        int val;

        adc->admux |= input; // seleccion de entrada analogica.
        adc->adcsra |= (1<<ADSC); // comenzar conversion
     
        while ((adc->adcsra & (1<<ADSC)) == (1<<ADSC)); 
       
        val = adc->adch; // obtener dato de 8 bits
        
        return val;
}
