/**
 *
 * task_knob_motor:  	Toma como entrada la posicion del knob y modifica la velocidad del motor.
 * task_led_observer: 	Lee la velocidad actual del motor y enciende el led a una frecuencia proporcional.
 * task_reporter:		Obtiene la entrada de la consola del operador del sistema. (main)
 * task_reporter:		Reporta constantemente el estado del sistema al operador.
 * task_servo_handler:	Manipula la posicion del servo
 *
 */

#include <xinu.h>
#include "serial.h"

unsigned char motor_speed = 0;
unsigned char servo_angle = 0;
unsigned char clock = 0;
unsigned char input_op = 0;
unsigned char seg = 0;
unsigned char min = 0;
unsigned char hor = 0;

volatile unsigned char *PIN_B = (unsigned char *)0x23;	  // direccion de PIN_B
volatile unsigned char *DDR_B = (unsigned char *)0x24;	  // direccion de DDR_B
volatile unsigned char *PUERTO_B = (unsigned char *)0x25; // direccion de PORT_B

/* definicion de tareas (cuyo codigo fuente es externo) */
// extern int led_observer(void);
extern int reporter(void);
extern int comunicacion(void);
extern int knob_motor(void);
extern int servo_handler(void);
extern int led_observer(void);
extern int real_time_clock(void);

/* main es la tarea que toma las entradas del sistema (reporter) */
int main(void)
{
	serial_init();
	adc_init();
	timer1_init();
	/* configurar entrada/salida de datos */
	(*DDR_B) |= 0b00001110;

	/* creamos y ponemos a ejecutar las tareas */
	resume(create(servo_handler, 128, 30, "serv", 0));
	resume(create(knob_motor, 128, 30, "knob", 0));
	resume(create(reporter, 256, 30, "repo", 0));
	resume(create(led_observer, 64, 30, "led", 0));
	resume(create(real_time_clock, 64, 30, "rtc", 0));
	while (1)
	{
		if (serial_get_char_ready())
			input_op = serial_get_char();
		else
			input_op = 0;

		sleepms(250);
	}

	return 0;
}
