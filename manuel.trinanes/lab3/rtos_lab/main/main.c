#include <xinu.h>
#include "serial.h"
#include "adc.h"
#include "timer1.h"

// Process with external code
extern int led_placa(void);
extern int serial_input(void);
extern int serial_output(void);
extern int knob_motor(void);
extern int rtc(void);
extern int servo(void);

// Global Variables
unsigned int rtc_seconds;
int servo_angle = 90;
int knob_porcentage = 0;
unsigned char motor = 0;

// Main process
int main(void)
{
	serial_init();
	adc_init();
	init_timer1();

	// Create and run process
	resume(create(rtc, 64, 20, "rtc", 0));
	resume(create(knob_motor, 128, 19, "k_m", 0));
	resume(create(servo, 128, 19, "ser", 0));
	resume(create(serial_input, 64, 19, "s_i", 0));
	resume(create(serial_output, 256, 19, "s_o", 0));

	led_placa();

	return 0;
}

