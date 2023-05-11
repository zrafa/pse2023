#include "serial.h"
#include "delay.h"

void control_knight_rider();
int control_ultrasonido();
void turn_on_leds(unsigned char led_1, unsigned char led_2, unsigned char led_3);
void turn_off_leds();
void convert_to_string(char* str, int length, int num);

volatile unsigned char* PIN_B = (unsigned char*) 0x23;
volatile unsigned char* DDR_B = (unsigned char*) 0x24;
volatile unsigned char* PORT_B = (unsigned char*) 0x25;

#define LED_1 0x4 // 0000 0100
#define LED_2 0x8 // 0000 1000
#define LED_3 0x10 // 0001 0000
#define ECHO 0x1
#define TRIGGER 0x2

int main(void)
{
    char rcvChar = 0;
    int distance = 0;
    int n = 5;
    char* str = "0000-";

    *DDR_B = TRIGGER;
    *PORT_B = ECHO;

    serial_init();

    while (1) {

        rcvChar = serial_get_char();

        if (rcvChar == 'k'){
            control_knight_rider();
        } else if (rcvChar == 'q'){
            distance = control_ultrasonido();
            convert_to_string(str,n,distance);
            serial_put_str(str);
        }
    }

    return 0;
}

void control_knight_rider()
{
    unsigned char state = 0;

    while (!state) {
        turn_on_leds(LED_1,LED_2,LED_3);
        state = serial_get_char_ready();
        if (!state)
            turn_on_leds(LED_3,LED_2,LED_1);
        state = serial_get_char_ready();
    }

    turn_off_leds();
}

void turn_on_leds(unsigned char led_1, unsigned char led_2, unsigned char led_3)
{
    int delay = 92;
    
    delay_ms(delay);
    *PORT_B |= led_1;
    delay_ms(delay);
    *PORT_B |= led_2; 
    *PORT_B &= ~led_1;
    delay_ms(delay);
    *PORT_B |= led_3;
    *PORT_B &= ~led_2; 
    delay_ms(delay);
    *PORT_B &= (~led_3);
}

void turn_off_leds()
{
    *PORT_B &= (~LED_1) & (~LED_2) & (~LED_3);
}

int control_ultrasonido()
{
    int distance_cm = 0;
    unsigned int time_us = 0;
    volatile unsigned int t = 0;
    volatile unsigned char state_high;

    // Transmision de pulso.
    *PORT_B |= TRIGGER; // high
    delay_10us();
    *PORT_B &= (~TRIGGER); // low.

    // Espera de echo.
    state_high = (*PIN_B & ECHO);
    while (state_high != ECHO){
        state_high = (*PIN_B & ECHO);
    }

    // Medicion.
    while (state_high == ECHO){
        t++;
        delay_10us();
        state_high = (*PIN_B & ECHO);
    }

    time_us = t * 10;
    distance_cm = time_us / 41;
    delay_ms(45);

    return distance_cm;
}

void convert_to_string (char* str, int length, int num)
{
    int i;

    str[length-1] = 45;
    for (i = length-2; i >= 0; i--) {
        str[i] = (char)(num % 10 + 48);
        num /= 10;
    }
}