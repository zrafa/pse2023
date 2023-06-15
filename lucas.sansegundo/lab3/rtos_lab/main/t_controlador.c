#include <xinu.h>
#include "serial.h"
#include "globales.h"

int controlador(void){
	unsigned char rsvchar;
	while (1)
	{
		rsvchar = serial_get_char();
		
		if (rsvchar == 'b')
		{
			motor_encendido = 0;
		}
		if (rsvchar == 'n')
		{
			motor_encendido = 1;
		}
		if (rsvchar == 'a')
		{
			angulo_servo -= 5;
			if (angulo_servo < 0){
				angulo_servo = 0;
			}
		}
		if (rsvchar == 'd')
		{
			angulo_servo += 5;
			if (angulo_servo > 180){
				angulo_servo = 180;
			}
		}
		
		sleepms(50);
	}
}
