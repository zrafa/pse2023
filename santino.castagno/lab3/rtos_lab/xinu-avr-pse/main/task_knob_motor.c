

#include <xinu.h>
#include "serial.h"
#include "timer1.h"
#include "adc.h"

extern volatile unsigned char *PIN_B;    // direccion de PIN_B
extern volatile unsigned char *DDR_B;    // direccion de DDR_B
extern volatile unsigned char *PUERTO_B; // direccion de PORT_B

#define SEM_COM 0
#define SEM_PROD 1
#define MAX_VALUE_ADC 1024

extern unsigned char motor_speed;
extern unsigned char input_op;

/**
 * tarea encargada de manipular la velocidad del motor utilizando el snob-potenciometro
 */
int knob_motor(void)
{
    char state = 1;
    unsigned int input = 0;
    unsigned char input_aux = 0;
    unsigned char temp = 0;

    while (1)
    {
        input_aux = input_op;
        if (input_op == 'b')
        {
            state = 0;
            motor_speed = 0;
            timer1b_pwm_move_to(0);
        }
        else if (input_op == 'n')
        {
            state = 1;
        }

        if (state)
        {
            input = adc_get(0);
            temp = input / 10; // para simplificar la operacion de motor_speed = input * 100 / 1024
            motor_speed = temp;
            if (temp > 100 && temp < 110)
                temp = 100;
            timer1b_pwm_move_to(temp);
            sleepms(50);
        }
    }
}
