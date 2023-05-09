

void delay_ms(unsigned int ms) 
{
    volatile long i;
    for(i = 0; i < ms * 180; i++){
    }
}

void delay_10_us() 
{
    volatile int i = 0;
    i++;
}




