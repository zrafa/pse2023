#include <avr/interrupt.h>
#include "timer1.h"
#include "serial.h"
#include "delay.h"

int main()
{
    volatile unsigned char ch;
    volatile int num;

    serial_init();
    timer1_init();

    sei();

    while(1){
        ch = serial_get_char();
        num = (int)(ch * 130 / 255);
        setOCRnA(num);
        //delay_ms(100);
    }

    return 0;
}