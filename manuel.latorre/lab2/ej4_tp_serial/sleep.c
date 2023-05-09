void sleep10_us()
{
  for (volatile int i = 0; i < 1; i++){
  }
  volatile int a=1;
  
}

void sleep_ms(int tiempo)
{
  volatile unsigned int cant=146*tiempo;
  for (volatile long i = 0; i < cant; i++){}
}