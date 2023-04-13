int main(void)
{
  volatile unsigned char * DDR_B = (unsigned char *) 0x24;
  volatile unsigned char * PUERTO_B = (unsigned char *) 0X25;
  (*DDR_B)=0b00010000;
  volatile long i=0;
  while(1){
    (*PUERTO_B) = 0b00100000;
    sleep_ms(3000);
    (*PUERTO_B) = 0;
    sleep_ms(3000);
  }
}

void sleep_ms(int tiempo){
  volatile unsigned int cant=146*tiempo;
  for (volatile long i = 0; i < cant; i++){}
}

void sleep10_us(){
  for (volatile int i = 0; i < 1; i++){
  }
  volatile int a=1;
}