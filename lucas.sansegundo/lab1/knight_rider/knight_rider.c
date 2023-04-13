//variables globales
unsigned char estado, apretado,nro_led;
volatile unsigned char *DDR_B = (unsigned char *)0x24;
volatile unsigned char *PUERTO_B = (unsigned char *)0X25;
volatile unsigned char *PIN_B = (unsigned char *)0X23;


//ACLARACION: este knight_rider usa 3 leds mas el led integrado en pb5. 

int main(void)
{

  //el arreglo que nos indican el byte de comparacion para prender un led
  char prende_luces[4] = {0b00000001, 0b00000010, 0b00000100, 0b00100000};
  //el arreglo que nos indican el byte de comparacion para apagar el led
  char apaga_luces[4] = {0b11111110, 0b11111101, 0b11111011, 0b11011111};
  //estos arreglos almacenan bytes que nos sirve para comparar valores para el PUERTO_B
  //Nos ayuda a prender y apagar leds
  
  //el estado representa si el sistema esta apagado = 0 o prendido = 1
  estado = 0; 
  //esta variable nos indica si el boton se esta manteniendo apretado = 1 o no apretado = 0
  apretado = 0; 

  // dejamos el pb5, pb0, pb1 y pb2 como salida (leds)
  *(DDR_B) = 0b00100111;
  // Habilita pullup en pin pb3, dejamos apagados los leds    
  *(PUERTO_B) = 0b00001000; 

  while (1){ 
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

      if(estado == 0){
        break;
      }
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
}

int prende_o_apaga(){
//modulo que checkea el estado del boton   
  // verificamos si el registro de entrada tenga un 1 en el pb3 (pullup)
  volatile int bitIn = *(PIN_B)&0b00001000;

  if (bitIn == 0 && apretado == 0){ 
    // Si el boton esta en pulldown y no se venia apretando 
    delay_rebote();
    //se prende o se apaga dependiendo el estado
    if (estado == 0){ 
      estado = 1;
    }
    else{
      estado = 0;
    }
    //indicamos que el boton esta apretado
    apretado = 1;
  }

  if (bitIn != 0 && apretado == 1){ 
    // Si esta en pullup y se estaba manteniendo apretado, indicamos que no esta apretado
    delay_rebote();
    apretado = 0;
  }
}

int delay_luz(void){
//tiempo que la luz se mantiene prendida o apagada 
  volatile int i = 0;
  for (i = 0; i < 15000; i++){
    prende_o_apaga();
  }
}

int delay_rebote(void){
//delay para el rebote de señal
  volatile int i = 0;
  for (i = 0; i < 5000; i++){
  }
}
