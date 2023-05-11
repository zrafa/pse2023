#include "adc.h"
#include "serial.h"
#include "delay.h"

void knob_control();
void button_control();

volatile unsigned char* PIN_B = (unsigned char*) 0x23;
volatile unsigned char* DDR_B = (unsigned char*) 0x24;
volatile unsigned char* PORT_B = (unsigned char*) 0x25;

#define BUTTON 0x01
#define LEFT 1900
#define MIDDLE 2195
#define RIGHT 4095

int current_key = -1;

int main()
{
    serial_init();
    adc_init();
    
    *DDR_B = 0; // entrada.
    *PORT_B |= BUTTON; // pull up.

    while (1){
        button_control();
        knob_control();
        delay_ms(100);
    }
    
    for(;;);
}

void knob_control()
{
    /* Limita el envio de una letra dependiendo del rango al que pertenece el valor knob y el valor de letra
    actual */
    int knob;

    knob = adc_get(0);
    if (knob <= LEFT && current_key != LEFT){
        current_key = LEFT;
        serial_put_char('a');
    }
    else if (knob > LEFT && knob <= MIDDLE && current_key != MIDDLE){
        current_key = MIDDLE;
        serial_put_char('s'); 
    }
    else if (knob > MIDDLE && current_key != RIGHT) {
        current_key = RIGHT;
        serial_put_char('d');
    }
}

void button_control()
{
    if ((*PIN_B & BUTTON) != BUTTON){ // Se pulsa boton.
        delay_ms(100); // Rebote.
        if ((*PIN_B & BUTTON) != BUTTON){
            current_key = -1;
            serial_put_char('b');
        }    
    }
}