
extern volatile unsigned char *PIN_B;    // direccion de PIN_B
extern volatile unsigned char *DDR_B;    // direccion de DDR_B
extern volatile unsigned char *PUERTO_B; // direccion de PORT_B

#include <xinu.h>
#include "serial.h"
#include "timer1.h"

extern unsigned char servo_angle;
extern unsigned char input_op;

/**
 * tarea encargada de posicionar el servo
 */
int servo_handler(void)
{
    while (1)
    {

        if (servo_angle > 0 && input_op == 'a')
        {
            servo_angle -= 10;
            timer1a_pwm_move_to(servo_angle * 100 / 180);
        }
        else if (servo_angle < 180 && input_op == 'd')
        {
            servo_angle += 10;
            timer1a_pwm_move_to(servo_angle * 100 / 180);
        }

        sleepms(250);
    }
}
