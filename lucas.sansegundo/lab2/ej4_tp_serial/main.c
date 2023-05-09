#include "serial.h"
#include "sleeps.h"

volatile unsigned char * DDR_B = (unsigned char *) 0x24;
volatile unsigned char * PUERTO_B = (unsigned char *) 0X25;
volatile unsigned char * PIN_B= (unsigned char *) 0X23;
char rcvChar = 0;
char estado = 0;
unsigned char nro_led;


void menu(void)
{
    serial_put_string("\r\n----------------------------------\r\n");
    serial_put_string("Estas en el menu principal\r\n");
    serial_put_string("Apretar 'k' para prender el knight rider ('q' para apagar)\r\n");
    serial_put_string("Apretar 'u' para prender el ultrasonido ('q' para apagar)\r\n");
    serial_put_string("Apretar 'q' para salir del programa\r\n");
    serial_put_string("\r\n----------------------------------\r\n");
}

int main(void)
{
    char rcvChar = 0;

    /* Configure the UART for the serial driver */
    serial_init();
    menu();

    *(DDR_B) = 0b00101111;

    while (rcvChar != 'q')
    {
        rcvChar = serial_get_char();
        serial_put_char(rcvChar);
        serial_put_string("\r\n");
        if (rcvChar == 'k')
        {
          //el estado representa si el sistema esta apagado = 0 o prendido = 1
          serial_put_string(" Se enciende el knight rider\n\r ");
          estado = 1;
          knight_rider();
          menu();
        } else if(rcvChar == 'u'){
          serial_put_string(" Se enciende el ultrasonido\n\r ");
          estado = 1;
          ultrasonido();
          menu();
        }
    }
    serial_put_string("Saliste del programa!");
    for (;;);
    return 0;
}

void knight_rider(void){
  //el arreglo que nos indican el byte de comparacion para prender un led
  char prende_luces[4] = {0b00000001, 0b00000010, 0b00000100, 0b00100000};
  //el arreglo que nos indican el byte de comparacion para apagar el led
  char apaga_luces[4] = {0b11111110, 0b11111101, 0b11111011, 0b11011111};
 
    //indica el numero de led que se esta trabajando 
    nro_led = 0; 
    //ida indica el sentido hacia donde van las luces
    unsigned char ida = 0;
    prende_o_apaga();

    //este while indica la variacion de juego de luces 
    //mientras este prendido la secuencia de luces sera la siguiente:
    // pb0 - pb1 - pb2 - pb5 - pb2 - pb1 - pb0
    while (estado == 1)
    {
      delay_luz();

      *(PUERTO_B) = *(PUERTO_B) | prende_luces[nro_led];

      delay_luz();

      *(PUERTO_B) = *(PUERTO_B) & apaga_luces[nro_led];

      if (nro_led == 3 && ida == 1){
        ida = 0;
      }

      if (nro_led == 0 && ida == 0){
        ida = 1;
      }

      if (ida == 1){
        nro_led++;
      }
      else{
        nro_led--;
      }
    }
}

void ultrasonido (void){

  int distancia_cm =0;
  unsigned int tiempo_us;
  volatile int echo = 0;
  volatile unsigned int t=0;

  while(estado){//
    prende_o_apaga();
    (*PUERTO_B)= (*PUERTO_B) | 0b00001000;
    sleep10_us();
    (*PUERTO_B)= (*PUERTO_B) & 0b11110111;
    t=0;
    while(!echo){
      echo = (*PIN_B) & 0b00010000;
    }
 
    while(echo){
      t++;
      sleep10_us();
      echo = (*PIN_B) & 0b00010000;
    }
    tiempo_us = t * 10;  
    distancia_cm = tiempo_us / 58;
    serial_put_string("\n\rdistancia: ");
    serial_put_int(distancia_cm,4);
    serial_put_string(" cm");
    sleep_ms(50);
  }
}

void prende_o_apaga()
{
//verifica si hay elementos que entraron
  if(serial_getchar_ready()){ 
    rcvChar = serial_get_char();
    if(rcvChar == 'q'){
      (*PUERTO_B)= 0b00000000;
      estado=0;
      serial_put_string(" Se apaga el dispositivo \n\r ");
    }
  }
  
}

int delay_luz(void){
//tiempo que la luz se mantiene prendida o apagada 
  volatile int i = 0;
  for (i = 0; i < 15000; i++){
    prende_o_apaga(); //verificacion
  }
}