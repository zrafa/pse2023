#include <xinu.h>
#include "globales.h"
#include "adc.h"
#include "timer.h"

int controlar_motor(void)
{
	while(1) {
		volatile int vel;
		if(motor_encendido) {
			//valores de 0 a 100
			vel_motor = (adc_get(2) / 35);
			if(vel_motor > 100){
				vel_motor=100;
				vel = 0;
			}
			vel = 100 - vel_motor;
			timer1_motor(vel);
		} else {
			timer1_motor(100);
		}

		sleepms(50);
	}
}
