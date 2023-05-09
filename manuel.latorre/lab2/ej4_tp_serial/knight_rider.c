#include "serial.h"
#include "globals.h"

void knight_rider_run(void)
{
  serial_init();
  serial_put_string("\n\rKNIGHTRIDER ENCENDIDO\n\r ");
  encendido=0;
  rcv_char='a';
  (*DDR_B)= 0b00110111;//bit 5= led arduino(para debugear), pb0,pb1,pb2=SALIDAS
  (*PUERTO_B)= 0b00100001;//Enciende pin pb0,
  encendido=1;
  while(encendido){
    verif_pagar();
      if(encendido==1){
        esperar(); //delay prendido
        (*PUERTO_B)= (*PUERTO_B) & 0b11111110;//Apaga pb0=d8
        esperar();//delay apagado
      }

      if(encendido==1){
        (*PUERTO_B)= (*PUERTO_B) | 0b00000010;//Prende pb1=d9
        esperar();//delay prendido
      }

      if(encendido==1){
        (*PUERTO_B)= (*PUERTO_B) & 0b11111101;//Apaga pb1=d9
        esperar();//delay apagado
      }

      if(encendido==1){
        (*PUERTO_B)= (*PUERTO_B) | 0b00000100;//Prende pb2=d10
        
        esperar();//delay prendido
      }

      if(encendido==1){
        (*PUERTO_B)= (*PUERTO_B) & 0b11111011;//Apaga pb2=d10
        
        esperar();//delay apagado
      }
      if(encendido==1){
        (*PUERTO_B)= (*PUERTO_B) | 0b00000001;//Prende pb0=d8
      }
  }
}

void verif_pagar()
{
  if(serial_getchar_ready()){
    rcv_char = serial_get_char();
    if(rcv_char == 'q'){//Recibe q entonces apaga
      encendido=0;
      (*PUERTO_B)= 0b00000000; //Apaga led arduino
      serial_put_string("\rKNIGHTRIDER APAGADO\n\n\r ");
    }
  }
}

void esperar()
{
  volatile long i=0;
  for(i=0; i<12000; i++){
    verif_pagar();//De esta manera verifica constantemente excepto en los instantes de encendido y apagado que son muy pequeños
  }
}