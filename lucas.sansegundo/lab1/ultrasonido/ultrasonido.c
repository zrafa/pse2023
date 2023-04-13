
volatile unsigned char * DDR_B = (unsigned char *) 0x24;
volatile unsigned char * PUERTO_B = (unsigned char *) 0X25;
volatile unsigned char * PIN_B= (unsigned char *) 0X23;

int main(void)
{
    serial_init();

   // un pin-x gpio del atmega328p lo configuran como SALIDA
    // el pb0 (d8) sera de salida
   //un pin-y gpio del atmega328p lo configuran como ENTRADA
    //pb4 (d12) sera de entrada
  *(DDR_B) = 0b00000001;
  
  int distancia_cm =0;
  unsigned int tiempo_us;
  volatile int echo = 0;
  volatile unsigned int t;

  while(1){
    //medicion, poner en alto la señal del trigger y luego de 10us bajarla 
    (*PUERTO_B)= (*PUERTO_B) | 0b00000001;
    delay_10us();
    (*PUERTO_B)= (*PUERTO_B) & 0b11111110;
    

    //Esperar hasta que pb4 esté en high (el ultrasound levanta esa señal).
    while(!echo){
      echo = (*PIN_B) & 0b00010000;
    }
    
    //Cuando esté en high, empiezar a contar de a 10 microsegundos (us):
    t=0;
    while(echo>0){
      t++;
      delay_10us();
      //leer pin de entrada pb4
      echo = (*PIN_B) & 0b00010000;
    }

    //calculo de distancia
    tiempo_us = t * 10;  
    distancia_cm = tiempo_us / 58;
    serial_put_str("\n Distancia: ");
    serial_put_int(distancia_cm,4);
    serial_put_str(" cm");
    delay_ms(50);

  }
}

int delay_10us(){
  // segun el osciloscopio esta accion dura 10us
  for (volatile int i = 0; i < 1; i++){}
  volatile int a=1;
  
}

int delay_ms(long tiempo){
  //aca hay que ver cuantos i necesito ciclar para llegar a 1ms 
  //con 150 iteraciones hacemos 1ms, va a pasar como parametro cuantos ms necesitamos 
  //esto lo verificamos con el osciloscopio 
  long cant=150*tiempo;
  volatile long i;
  for (i = 0; i < cant; i++){}
}

