#include <xinu.h>
#include "timer.h"
#include "globales.h"


int controlar_servo()
{
    long ticks;
    while(1) {
        //como el servo frena en 720
        ticks = angulo_servo * 100 / 18 + 210;
        timer1_rotacion_servo(ticks);
        sleepms(50);
    }
}