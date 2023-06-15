/*
 * tarea_led: este programa parpadea el led de la placa.
 *
 * Se desarrolla como un programa aislado del resto.
 */

#include <xinu.h>

extern volatile unsigned char *PUERTO_B;
extern unsigned char motor_speed;

#define FREQ 1000

int led_observer(void)
{

    unsigned char speed = 0;
    while (1)
    {
        speed = motor_speed;
        if (speed > 0)
        {
            sleepms(FREQ - speed * 10);
            *PUERTO_B |= 0b00001000; // high
            sleepms(FREQ - speed * 10);
            *PUERTO_B = (*PUERTO_B & (~0b00001000)); // low
        }
        else
        {
            *PUERTO_B |= 0b00001000; // high
        }
    }
    return 0;
}
