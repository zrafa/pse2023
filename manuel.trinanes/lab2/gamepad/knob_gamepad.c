#include "adc.h"
#include "serial.h"
#include "myutils.h"

/*
Bash:
key_down=false   # initial key state
sudo cat /dev/ttyUSB0 | while read -n 1 key; do
    if [ "$key" == "a" ] || [ "$key" == "d" ]; then
        if [ "$key_down" == true ]; then
            xdotool keyup "$key"
            key_down=false
        else
            xdotool keydown "$key"
            key_down=true
        fi
    else
        xdotool key "$key"
    fi
done
*/

int main(void) {
    int val;
    int shot_button_port = 2;
    char key = ' ';
    char last_key;

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

        if(key != last_key) {
            if(key == ' ') {
                serial_put_char(last_key);
            } else {
                serial_put_char(key);
            }
            last_key = key;
        }

        if((*(PIN_D) & (1 << shot_button_port)) == 0) {
            delay_ms(1);
            if((*(PIN_D) & (1 << shot_button_port)) == 0) {
                serial_put_char('s');
                delay_ms(50);
            }
        }

        delay_ms(300);
    }
}