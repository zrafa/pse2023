#include "adc.h"
#include "serial.h"
#include "myutils.h"

/*
Bash:
sudo cat /dev/ttyUSB0 | while read -n 3 num; do brightnessctl s $num; done
*/

int main(void) {
    int val;

    adc_init();
    serial_init();

    while(1) {
        // +100 to has a more useful brightness
        val = adc_get(2) + 100;

        // My monitor has a limit of 950
        if(val > 950) {
            val = 950;
        }

        serial_put_int(val, 3);
        delay_ms(1000);
    }
}