#include <xinu.h>
#include "serial.h"
#include "timer1.h"
#include "adc.h"

// procesos
extern int real_time_clock(void);
extern int input(void);
extern int servo_control(void);
extern int motor_control(void);
extern int indicator_led(void);

// variables globales
extern unsigned char hours;
extern unsigned char min;
extern unsigned char sec;
extern unsigned int degrees;
extern unsigned int motor_percent;

int main(void)
{
    serial_init();
    timer1_init();
    adc_init();

    // creacion de procesos
    resume(create(real_time_clock,64,20,"rtc",0));
    resume(create(input,64,20,"inp",0));
    resume(create(servo_control,128,20,"ser",0));
    resume(create(motor_control,256,20,"mot",0));
    resume(create(indicator_led,64,20,"led",0));

    while(1) {

        sleep(1);
        serial_put_int(hours,2);
        serial_put_char(':');
        serial_put_int(min,2);
        serial_put_char(':');
        serial_put_int(sec,2);
        serial_put_str(". velocidad: ");
        serial_put_int(motor_percent,3);
        serial_put_str("%. servo: ");
        serial_put_int(degrees,3);
        serial_put_str(" grados.\n");
        serial_put_char('\r');
    }

    return 0;
}