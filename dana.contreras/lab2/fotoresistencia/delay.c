
void delay_10us()
{
    volatile int i = 10, n = 10, max;
    max = i * n + 2;
}

void delay_ms(volatile int ms)
{
    volatile int i, max;
    max = ms * 301;
    for (i = 0; i < max; i++){}
}
