
int delay_ms(long tiempo){
  //aca hay que ver cuantos i necesito ciclar para llegar a 1ms 
  //con 150 iteraciones hacemos 1ms, va a pasar como parametro cuantos ms necesitamos 
  //esto lo verificamos con el osciloscopio 
  long cant=150*tiempo;
  volatile long i;
  for (i = 0; i < cant; i++){}
}

int main(void)
{
  volatile unsigned char * DDR_B = (unsigned char *) 0x24;
  volatile unsigned char * PUERTO_B = (unsigned char *) 0X25;
  *(DDR_B)=0b00100000;
  while(1){
    *(PUERTO_B) = 0b00100000;
    delay_ms(1000);
    *(PUERTO_B) = 0b00000000;
    delay_ms(1000);
}
}