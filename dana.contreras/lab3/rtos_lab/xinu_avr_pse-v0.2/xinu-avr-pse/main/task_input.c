#include <xinu.h>
#include "serial.h"

unsigned char option;

int input(void)
{
    option = ' ';

    while (1){
        option = serial_get_char();
    }
    
}