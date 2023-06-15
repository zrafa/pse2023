#include <xinu.h>
#include <avr/interrupt.h>
#include "timer1.h"

extern unsigned char option;

int degrees;

int servo_control(void)
{
    int num, value = 90;
    int min = 330;
    long int max = 1000;

    while(1){

        switch (option) {
            case 'a':
                value = (value + 10) % 180;
                option = ' ';
                break;

            case 'd':
                value = (value - 10) % 180;
                if (value < 0)
                    value = 180;
                option = ' ';
                break;
        }

        // rango de [0,180] a rango de [min, max]
        num = (int)(((long int)value * (max - min)) / 180) + min;

        cli();
        set_OCR1A(num);
        sei();

        degrees = value;
    }
}