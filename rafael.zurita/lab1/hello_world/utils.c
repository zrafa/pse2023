#include "utils.h"

#define LED (0x20)  /* 0010 0000 */

#define CYCLES_PER_MS (450)

/* puertos de E/S */
volatile unsigned char * PORTB = (unsigned char *) 0x25;  /* direccion de PORTB */
volatile unsigned char * DDRB  = (unsigned char *) 0x24;  /* direccion de DDR B (registro de control) */
volatile unsigned char * PINB  = (unsigned char *) 0x23;  /* direccion PIN B (registro de datos) */

void delay_ms(unsigned long ms)
{
        volatile unsigned long i;  /* no quitar volatile o NO funciona */

        for (i = 0; i < CYCLES_PER_MS * ms; i++);
}

void led_toggle(void)
{
        *PORTB ^= LED;
}

void led_init(void)
{
        *PORTB &= ~LED;  /* set voltage off */
        *DDRB  |= LED;   /* set pin as OUTPUT */
}
