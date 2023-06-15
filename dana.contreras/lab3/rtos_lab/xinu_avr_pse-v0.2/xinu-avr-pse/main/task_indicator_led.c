#include <xinu.h>

extern int motor_percent;

int indicator_led(void)
{
    volatile unsigned char* DDR_B = (unsigned char*) 0x24;
    volatile unsigned char* PUERTO_B = (unsigned char*) 0x25;

    int freq;
    int delay_value;

    (*DDR_B) |= 0x20; // control: salida.

    while(1) {

        if (motor_percent == 0)
            freq = 0;
        else
            freq = (int)(motor_percent * 9 / 100) + 1;
        
        if (freq == 0) {
            (*PUERTO_B) |= (*PUERTO_B & (~0x20)); // low
        } else {

            delay_value = 1000 / (2 * freq);
            sleepms(delay_value);
            (*PUERTO_B) |= 0x20; // high
            sleepms(delay_value);
            (*PUERTO_B) |= (*PUERTO_B & (~0x20)); // low
            
        }
    }
}