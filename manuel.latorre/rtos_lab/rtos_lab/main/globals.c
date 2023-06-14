#include "globals.h"

volatile unsigned char * DDR_B = (unsigned char *) 0x24;
volatile unsigned char * PUERTO_B = (unsigned char *) 0X25;
volatile unsigned char * PIN_B= (unsigned char *) 0X23;
volatile int motor_init=0;
volatile int motor_speed=0;
volatile int serv_angle= 0;
volatile unsigned int seconds=0;