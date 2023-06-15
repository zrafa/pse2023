
#include <xinu.h>
#include "serial.h"
#include "timer1.h"

extern unsigned char seg;
extern unsigned char min;
extern unsigned char hor;

/**
 * tarea encargada de llevar el conteo del tiempo real
 */
int real_time_clock(void)
{
    while (1)
    {
        seg++;
        if (seg == 60)
        {
            seg = 0;
            min++;
        }
        if (min == 60)
        {
            seg = 0;
            min = 0;
            hor++;
        }
        sleepms(1000);
    }
}