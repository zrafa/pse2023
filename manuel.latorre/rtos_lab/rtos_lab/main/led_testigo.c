#include <xinu.h>
#include "serial.h"
#include "globals.h"
int bit_in = 0;
int main_led_testigo(void)
{
  while(1){
    bit_in = *(PIN_B) & 0b00100000;//Revisa estado actual del led
    if(motor_init){
      parpadeo();
    }else{
      if(bit_in){
        (*PUERTO_B) &= ~(1 << 5);//Apaga
      }
    }
    sleepms(1);//Para que libere CPU y pueda correr main
  }
}

void parpadeo()
{
  if(!bit_in){
    *(PUERTO_B) |= (1 << 5);//Prende
  }else{
    (*PUERTO_B) &= ~(1 << 5);//Apaga
  }

  if(motor_speed==0){//Velocidad minima
    sleepms(500);
  }else if(motor_speed==10){//Velocidad maxima
    sleepms(30);
  }else{
    sleepms(500/motor_speed);
  }
}


