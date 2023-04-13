
void delay_ms(volatile int delay);

int main()
{
    volatile unsigned char* DDR_B = (unsigned char*) 0x24;
    volatile unsigned char* PUERTO_B = (unsigned char*) 0x25;

    *DDR_B = 0x20; // control: salida.

    while (1){
        delay_ms(90);
        *PUERTO_B = 0x20; // high
        delay_ms(90);
        *PUERTO_B = 0; // low
    }

}

void delay_ms(volatile int ms)
{
    volatile int i, max;
    max = ms * 302;
    for (i = 0; i < max; i++){}
}