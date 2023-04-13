#include "sleep.h"

volatile unsigned char *DDR_B = (unsigned char *)0x24;	  // puntero a direccion de DDR_B
volatile unsigned char *PUERTO_B = (unsigned char *)0x25; // puntero a direccion de PORT_B

int main()
{
	*(DDR_B) = 0b00100000; // setear direccion de datos

	while (1)
	{
		*(PUERTO_B) = 0b00000000;
		sleep_ms(90);
		*(PUERTO_B) = 0b00100000;
		sleep_ms(90);
	}
	return 0;
}
