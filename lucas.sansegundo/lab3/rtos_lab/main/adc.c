/**********************************************************************
 *
 * adc.c - Driver del ADC del atmega328p
 *
 * META : ocultar el hardware a la aplicacion 
 *
 **********************************************************************/

#include <stdint.h> /* para los tipos de datos. Ej.: uint8_t */
#include "adc.h"

/* Estructura de datos del driver ADC */

typedef struct
{
        uint8_t adcl;              
        uint8_t adch;
        uint8_t adcsra; /*ADC Control and Status Register A*/
        uint8_t adcsrb;
        uint8_t admux;
        uint8_t reserved;
        uint8_t didr0;

} volatile adc_t;

volatile adc_t *adc = (adc_t *) (0x78);


void adc_init()
{
        //Habilita capacitor externo
        adc->admux = 0b01000000; 
        
        //Habilita adc y setea el preescalar en 16
        adc->adcsra = 0b10000100;
}

int adc_get(char input)//Valores 0-8
{
        if(input >= 0 & input < 9){
        //En funcion al input se selecciona el adc
        adc->admux = adc->admux  | input; 

        //Comienza la conversion se pisan los bits
        adc->adcsra =  (adc->adcsra & 0b10111111) | (1 << 6); 

        //adcsra se mantiene en 1 mientras hace conversion, cuando finaliza vuelve a 0
        while((adc->adcsra & (1 << 6))); 
        int low = adc->adcl;
        int high = adc->adch;
        return ((high << 8) | low); 
        }
}
