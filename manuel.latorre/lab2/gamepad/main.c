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
    analog_in = (adc_get(0)/455); //Aca para tener 10 valores del 0 al 9 y poder distribuir: izq:0,1,2,3, med=4,5, der=6,7,8,9
    //MOVIMIENTO IZQ/DER
    if(analog_in<=3){
      if(apretado){ //Si venia apretado y moviendo, ataca y me mueve a la izq
        input='l';
      }else if(input!='l'){ //Si venia solo moviendo o quieto, mueve a la izq
        input='a';
      }
    }else if(analog_in>=6){
      if(apretado){ //Si venia apretado y moviendo, ataca y me mueve a la der
        input='r';
      }else if(input!='r'){ //Si venia solo moviendo o quieto, mueve a la der
        input='d';
      }
    }else{
      if(!apretado){ //Si estoy quieto y no apreto, solo va quieto
        input='s';
      }else{
        input='b'; //Si estaba apretando, apreta y dispara
      }
    }

    //DISPARO
    //Apreta
    if(bit_in==0 && apretado==0){//Si apretó y no venia pulsando
      sleep_ms(10);
      if(input=='a'){ //Ataque con desp a izq
        input='l';
      }else if(input=='d'){//Ataque con desp a der
        input='r';
      }else{//Ataque quieto
        input='b';
      }
      
      *(PUERTO_B)= *(PUERTO_B) | 0b00100000;//Prende PB5=d13
      apretado=1;
    }
    //Suelta
    if(bit_in!=0 && apretado==1){ //Si solto y venia apretado
      sleep_ms(10);
      input='q';
      *(PUERTO_B)= *(PUERTO_B) & 0b11011111;
      apretado=0;
    }

    serial_put_char(input);
    sleep_ms(300);//Este es el delay que mejor me andaba
  }
}