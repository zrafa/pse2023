#include "serial.h"
#include "globals.h"
#include "sleep.h"

void ultrasound_run(void)
{
  int distancia_cm =0;
  unsigned int tiempo_us;
  volatile int echo = 0;
  volatile unsigned int t=0;
  rcv_char=0;
  encendido=0;
  (*DDR_B)= 0b00110000;//pb3= ENTRADA, pb4=SALIDA
  (*PUERTO_B)= 0b00100000;
	serial_init();
  serial_put_string("\n\rULTRASOUND ENCENDIDO\n\r ");
  encendido=1;

  while(encendido){//
    verif_apagar();
    (*PUERTO_B)= (*PUERTO_B) | 0b00010000;//Activa salida
    sleep10_us();//Espera 10us
    (*PUERTO_B)= (*PUERTO_B) & 0b11101111;//Desactiva salida
    t=0;
    while(!echo){
      echo = (*PIN_B) & 0b00001000;
    }//Se queda esperando que se habilite la entrada
 
    while(echo){
      t++;
      sleep10_us();//Espera 10us*/
      echo = (*PIN_B) & 0b00001000;//Actualiza entrada
    }
    tiempo_us = t * 10;  
    distancia_cm = tiempo_us / 58;
    serial_put_string("\n\rDIST: ");
    serial_put_int(distancia_cm,4);//Mostrar distancia
    sleep_ms(50);

  }
}

void verif_apagar()
{
  
  if(serial_getchar_ready()){
    rcv_char = serial_get_char();
    if(rcv_char == 'q'){//Recibe q entonces apaga
      encendido=0;
      (*PUERTO_B)= 0b00000000; //Apaga led arduino
      serial_put_string("\rULTRASOUND APAGADO\n\n\r ");
    }
  }
}
