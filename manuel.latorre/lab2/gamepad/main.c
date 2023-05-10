#include "adc.h"
#include "serial.h"
#include "sleep.h"
#include "globals.h"

main(void)
{
  int analog_in;
  char input=' ';
  int apretado = 0;
  int bit_in;
  *(DDR_B)= 0b00100000;//bit 5= led arduino, pb0 lo uso de entrada de boton
  *(PUERTO_B)= 0b00000001;//Habilita pullup en pin pb0
  apretado = 0;
  adc_init();
  serial_init();
  while(1){
    bit_in = *(PIN_B) & 0b00000001;
    analog_in = (adc_get(0)/455); //Aca para tener 10 valores del 0 al 9 y poder distribuir: izq:0,1,2 med=3,4,5,6 der=7,8,9
    //MOVIMIENTO IZQ/DER
    if(analog_in<=2){
        input='a';
    }else if(analog_in>=7){
        input='d';
    }else{
        input='s'; //Si esta en el centro
      }
    

    //DISPARO
    //Apreta
    if(bit_in==0 && apretado==0){//Si apretó y no venia pulsando
      sleep_ms(10);
      input='b';
      apretado=1;
    }

    //Suelta
    if(bit_in!=0 && apretado==1){ //Si solto y venia apretado
      sleep_ms(10);
      input='q';
      apretado=0;
    }

    serial_put_char(input);
    sleep_ms(300);//Este es el delay que mejor me andaba
  }
}