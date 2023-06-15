#include <xinu.h>
#include <avr/interrupt.h>
#include "timer1.h"
#include "adc.h"

extern unsigned char option;

int motor_percent;

int motor_control(void)
{
    int state;
    volatile int knob;
    int motor_speed;
    long int max = 10000;

    while (1) {

        knob = adc_get(0);
        motor_speed = ((knob * max) / 255);

        switch (option) {
            case 'b':
                state = 1;
                break;

            case 'n':
                state = 0;
                break;
        }

        if (state)
            knob = 255;

        motor_speed = ((knob * max) / 255);

        cli();
        set_OCR1B(motor_speed);
        sei();

        motor_percent = 100 - (knob * 100) / 255;
    }
}