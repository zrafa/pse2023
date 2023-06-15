#include <xinu.h>

int hours;
int min;
int sec;

int real_time_clock(void) {
    hours = 0;
    min = 0;
    sec = 0;

    while (1) {
        sleep(1);
        sec = (sec + 1) % 60;
        if (sec == 0) {
            min = (min + 1) % 60;
            if (min == 0)
                hours = (hours +1) % 60;
        }
    }
}