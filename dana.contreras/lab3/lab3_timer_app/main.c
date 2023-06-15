#include <avr/interrupt.h>
#include "timer1.h"
#include "serial.h"
#include "delay.h"

#define N 100

int main()
{
    volatile unsigned char ch;
    volatile int num;

    serial_init();
    timer1_init();

    while(1){
        ch = serial_get_char();
        num = (int)(ch * N / 255);
        cli();
        setOCRnA(num);
        sei();
    }

    return 0;
}