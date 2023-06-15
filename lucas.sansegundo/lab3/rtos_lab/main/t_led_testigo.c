/*
 * tarea_led: este programa parpadea el led de la placa.
 * 
 * Se desarrolla como un programa aislado del resto.
 */

#include <xinu.h>
#include "globales.h"

int led_testigo(void)
{
    *DDR_B |= 0x20; 
    int vel_parpadeo;
    while (1){
        if(motor_encendido){
            vel_parpadeo = 1100 - (vel_motor * 10) ;
            sleepms(vel_parpadeo);
            *PUERTO_B |= 0x20; 
            sleepms(vel_parpadeo);
        }
        *PUERTO_B = (*PUERTO_B & (~0x20)); 

    }

}

