#include <avr/io.h>
#include <avr/interrupt.h>
#include "globals.h"
#include "timer.h"

void prende_apaga(char letra)
{
  volatile int i;
  volatile int bit;
  volatile int aux;
  timer0_init();
  sei();

  (*PUERTO_B)= (*PUERTO_B) | 0b00000001; //on

  while(!send){}//Espera el tiempo de la interrupcion
  (*PUERTO_B)= (*PUERTO_B) & 0b11111110; //señal de bajada
  
  cli();//disable interrupt
    send=0;
  sei(); //enable interrupt
  
  //ENVIO DE BITS
  for(i = 0; i < 8; i ++){   
    while(!send){}
    if(send){
      cli();//disable interrupt
      send=0;
      sei(); //enable interrupt
      bit = ((int)(letra >> i) & 0x01);//obtiene bit a bit
      if(bit){
        (*PUERTO_B)= (*PUERTO_B) | 0b00000001; //on
      }else{
        (*PUERTO_B)= (*PUERTO_B) & 0b11111110; //off
      }
    }
  }
  while(!send){}//Espera a que termine el envio del ultimo bit para que no se prenda instantaneamente a la vuelta
}