#include "serial.h"
#include "myutils.h"

int main(void)
{
    volatile unsigned char *DDR_B = 0x24;
    volatile unsigned char *PORT_B = 0x25;
    volatile unsigned char *PIN_B = 0x23;
    volatile unsigned char *DDR_D = 0x2A;
    volatile unsigned char *PORT_D = 0x2B;

    // Serial
    serial_init();
    char input_char = 0;
    serial_put_char('s');
    serial_put_char('t');
    serial_put_char('a');
    serial_put_char('r');
    serial_put_char('t');
    serial_put_char('\n');
    serial_put_char('\r');

    // Ultrasound
    *(DDR_B) |= 1 << 0;
    unsigned int time;
    unsigned int cm;

    // Lights
    char knight_rider = 0;
    int lights = 0b110000;
    char ida = 0;
    *(DDR_D) |= 0b111111 << 2;

    while (1) {
        input_char = serial_try_get_char();

        if (input_char == 'k') {
            knight_rider ^= 1;
        }

        if (input_char == 'u') {
            // Activates the ultrasound
            *(PORT_B) |= 0b1;
            delay_10_us();
            *(PORT_B) ^= 0b1;

            // Waits until echo is up
            while (!(*(PIN_B) & (1 << 1)));

            time = 0;
            // Starts counting time until echo is down or time is over 38000us
            while (*(PIN_B) & (1 << 1) && time < 3800) {
                time++;
                delay_10_us();
            }

            cm = time * 10 / 100;
            serial_put_char(cm+48);
            delay_ms(50);
        }

        if (knight_rider) {
            *(PORT_D) = lights << 2 | (*(PORT_D)&0b11);
            if (ida) {
                lights <<= 1;
            } else {
                lights >>= 1;
            }
            if ((lights & 1) || (lights & (1 << 5))){
                ida = !ida;
            }
            delay_ms(200);
        }
    }

    return 0;
}