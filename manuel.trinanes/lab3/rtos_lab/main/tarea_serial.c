#include <xinu.h>
#include "serial.h"

// Global Variables
extern unsigned int rtc_seconds;
extern int servo_angle;
extern int knob_porcentage;
extern unsigned char motor;

// Process
int serial_input(void)
{
	unsigned char serial_input_char;
	while (1)
	{
		serial_input_char = serial_get_char();
		if (serial_input_char == 'a')
		{
			servo_angle = servo_angle - 5;
			if (servo_angle >= 180)
			{
				servo_angle = 180;
			}
			else if (servo_angle < 1)
			{
				servo_angle = 0;
			}
		}
		else if (serial_input_char == 'd')
		{
			servo_angle = servo_angle + 5;
			if (servo_angle >= 180)
			{
				servo_angle = 180;
			}
			else if (servo_angle < 1)
			{
				servo_angle = 0;
			}
		}
		else if (serial_input_char == 'b')
		{
			motor = 0;
		}
		else if (serial_input_char == 'n')
		{
			motor = 1;
		}
		sleepms(50);
	}
}

// Another Process
int serial_output(void)
{
	while (1)
	{
		serial_put_int(rtc_seconds / 3600, 2);
		serial_put_char(':');
		serial_put_int((rtc_seconds % 3600) / 60, 2);
		serial_put_char(':');
		serial_put_int((rtc_seconds % 3600) % 60, 2);
		serial_put_str(" | velocidad: ");
		serial_put_int(motor ? knob_porcentage : 0, 3);
		serial_put_str("% | angulo: ");
		serial_put_int(servo_angle, 3);
		serial_put_str("° |\n\r");
		sleepms(500);
	}
}
