#include <avr/io.h>
#include <avr/interrupt.h>
#include "globals.h"
#include "timer.h"
#include "laser.h"
#include "serial.h"

void main()
{
  char rcv_char=' ';
  *(DDR_B)= 0b00000001;//bit 0 = salida
  serial_init();
  serial_put_string("EJECUTANDO.\r\n");
  for(;;){
    (*PUERTO_B)= (*PUERTO_B) | 0b00000001; //El laser siempre esta prendido cuando no se esta enviando
    serial_put_string("\rIngrese una letra: \r\n");
    rcv_char = serial_get_char();
    serial_put_char(rcv_char);
    serial_put_string("\r\n");
    print(rcv_char);//Imprime bit a bit 
    serial_put_char('\r');
    serial_put_char('\n');
    
    prende_apaga(rcv_char);
    serial_put_string("FIN.\r\n");
  }
  
}

void print(char rcv_char){
  volatile int i;
  volatile int bit;
    for(i = 0; i < 8; i ++){
        bit = ((int)(rcv_char >> i) & 0x01);
        serial_put_int(bit , 4);
        serial_put_char('\r');
        serial_put_char('\n');
    }
}