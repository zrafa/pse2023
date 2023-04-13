#include "serial.h"

void delay_10us();
void delay_ms(volatile int ms);
void control_leds(int distance_cm);

volatile unsigned char* PIN_B = (unsigned char*) 0x23;
volatile unsigned char* DDR_B = (unsigned char*) 0x24;
volatile unsigned char* PORT_B = (unsigned char*) 0x25;
volatile unsigned char* PORT_D = (unsigned char*) 0x2B;

unsigned char trigger = 0x2; //0000 0010
unsigned char echo = 0x1; //0000 0001
unsigned char led_1 = 0x4; // 0000 0100 
unsigned char led_2 = 0x8; // 0000 1000
unsigned char led_3 = 0x10; // 0001 0000
unsigned char led_4 = 0x20; // 0010 0000

int main()
{
    int distance_cm;
    unsigned int time_us;
    volatile unsigned int t;
    volatile unsigned char state_high;

    *DDR_B = trigger;
    *PORT_B = echo;

    serial_init();

    while(1){
        distance_cm = 0;
        time_us = 0;
        t = 0;

        // Transmision de pulso.
        *PORT_B = (*PORT_B | trigger); // high
        delay_10us();
        *PORT_B = (*PORT_B) & (~trigger); // low.

        // Espera de echo.
        state_high = (*PIN_B & echo);
        while (state_high != echo){
            state_high = (*PIN_B & echo);
        }

        // Medicion.
        while (state_high == echo){
            t++;
            delay_10us();
            state_high = (*PIN_B & echo);
        }

        time_us = t * 10;
        distance_cm = time_us / 41;
        control_leds(distance_cm);

        serial_put_str("\n\r\n ");
        serial_put_int (distance_cm, 4);

        delay_ms(45);
    }

    return 0;
}

void delay_10us()
{
    volatile int i = 10, n = 10, max;
    max = i * n + 2;
}

void delay_ms(volatile int ms)
{
    volatile int i, max;
    max = ms * 301;
    for (i = 0; i < max; i++){}
}

void control_leds(int distance)
{

    if (distance <= 50){
        *PORT_D = led_1;

        if (distance > 10){
            *PORT_D = (*PORT_D | led_2);

            if (distance > 20){
                *PORT_D = (*PORT_D | led_3);

                if (distance > 30)
                    *PORT_D = (*PORT_D | led_4); 
            } 
        }
    } else { // leds apagados.
        *PORT_D = 0;
    }

}
