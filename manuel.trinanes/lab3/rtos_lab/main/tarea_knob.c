#include <xinu.h>
#include "adc.h"
#include "timer1.h"

extern int knob_porcentage;
extern unsigned char motor;

int knob_motor(void)
{
	while(1) {
		if(motor) {
			knob_porcentage = (adc_get(2) / 40) - 2;
			set_timer1_ocr1b_dutycycle(knob_porcentage);
		} else {
			set_timer1_ocr1b_dutycycle(0);
		}

		sleepms(100);
	}
}
