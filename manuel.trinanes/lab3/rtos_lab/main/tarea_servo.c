#include <xinu.h>
#include "timer1.h"

extern int servo_angle;

int servo()
{
    long val;
    while(1) {
        // 0deg = 200 ticks
        // 90deg = 700 ticks
        // 180deg = 1200 ticks
        val = servo_angle * 100 / 18 + 200;

        set_timer1_ocr1a(val);
        sleepms(200);
    }
}