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
        adc->admux = (0 << 7) | (1 << 6); //Habilita capacitor externo
        adc->adcsra = (1 << 7) | (1 << 2) | (0 << 1 ) | (0 << 0);//Habilita adc y setea el preescalar en 16
     
}

int adc_get(char input)//Valores 0-8
{
        adc->admux =(adc->admux & 0b11110000) | input; //En funcion al input se selecciona el adc
        //adc->admux =(adc->admux & 0b11011111) | (1 << 5); //Setea el adlar en 1 para tener alineacion izquierda y leer 8 bits


        adc->adcsra =  (adc->adcsra & 0b10111111) | (1 << 6); //Comienza la conversion se pisan los bits

        while((adc->adcsra & (1 << 6))); //adcsra se mantiene en 1 mientras hace conversion, cuando finaliza vuelve a 0
        int low = adc->adcl;
        int high = adc->adch;
        return ((high << 8) | low); //Resolucion 12 bits
        //return high; //Resolucion 8 bits
}
