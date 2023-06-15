#include "globales.h"

volatile unsigned char * DDR_B = (unsigned char *) 0x24;
volatile unsigned char * PUERTO_B = (unsigned char *) 0X25;
volatile unsigned char * PIN_B = (unsigned char *) 0X23;
int angulo_servo = 90;
int vel_motor = 0;
unsigned char motor_encendido = 0;
unsigned int segundos = 0;
