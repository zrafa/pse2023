#include "adc.h"
#include "serial.h"
#include "myutils.h"

/*
Bash:
sudo cat /dev/ttyUSB0 | while read -n 1 key; do xdotool key $key; done
*/

int main(void) {
    int val;
    int shot_button_port = 2;
    char key = ' ';

    volatile unsigned char * PORT_D = 0x2B;
    volatile unsigned char * PIN_D = 0x29;
    // Port D2
    *(PORT_D) |= 1 << shot_button_port;

    adc_init();
    serial_init();

    while(1) {
        val = adc_get(2) / 455 / 3;
        if (val == 1) {
            key = ' ';
        } else if(val == 2) {
            key = 'd';
        } else if (val == 0) {
            key = 'a';
        }

        if((*(PIN_D) & (1 << shot_button_port)) == 0) {
            delay_ms(1);
            if((*(PIN_D) & (1 << shot_button_port)) == 0) {
                key = 's';
                delay_ms(50);
            }
        }

        serial_put_char(key);
        delay_ms(1000);
    }
}