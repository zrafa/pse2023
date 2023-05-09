#include "adc.h"
#include "serial.h"
#include "sleeps.h"

volatile unsigned char *DDR_B = 0x24;
volatile unsigned char *PUERTO_B = 0x25;
volatile unsigned char *PIN_B = 0x23;

void boton (){
 //el boton de disparo es la k   
 char se_apreta = *(PIN_B) & 0b00000001;
 if(se_apreta == 0) {
    sleep_ms(20); //rebote
    if(se_apreta == 0){
        serial_put_char('k');
        sleep_ms(100);
    }  
}
}

main(void)
{
    //Habilita pullup en pin pb0(d8) 
    *(PUERTO_B)= 0b00000001;
    
    adc_init();
    serial_init();
    
    int val;
    char letra_apretada = ' ';

    /*toma valores del 0 al 9
    -del 0 al 3 es moverse a la izquierda
    -del 4 al 5 quedarse quieto
    -del 6 al 9 moverse a la derecha  
    -si se apreta una letra nueva y es para que la nave no se mueva
    ---tocamos la letra anterior para indicar que el xdotool no haga mas el keydown */
    while(1) {
        sleep_ms(200);
        boton();

        val = adc_get(2) / 380;
        if (val >= 0 && val < 4 ) {
            if (letra_apretada != 'a'){
                serial_put_char('a');
                letra_apretada = 'a';
            }
        } else if(val >= 4 && val < 6) {
            if (letra_apretada != 's'){
                serial_put_char(letra_apretada);
                letra_apretada = 's';
            }
        } else if (val >= 7 && val < 10) {
            if (letra_apretada != 'd'){
                serial_put_char('d');
                letra_apretada = 'd';
            }
        }        
    }
  
}

