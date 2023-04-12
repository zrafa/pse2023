#include "serial.h"
#include "myutils.h"

int main() {
    volatile unsigned char *DDR_B = 0x24;
    volatile unsigned char *PORT_B = 0x25;
    volatile unsigned char *PIN_B = 0x23;
    unsigned int time;
    unsigned int cm;

    // Sets the DDR_B port 0 to output 1
    *(DDR_B) |= 1 << 0;

    serial_init();

    while (1) {
        // Activates the ultrasound
        *(PORT_B) |= 0b1;
        delay_10_us();
        *(PORT_B) ^= 0b1;

        // Waits until echo is up
        while (!(*(PIN_B) & (1 << 1))){}

        time = 0;
        // Starts counting time until echo is down or time is over 38000us
        while (*(PIN_B) & (1 << 1) && time < 3800) {
            time++;
            delay_10_us();
        }

        cm = time * 10 / 100;
        serial_put_str("Distancia: ");
        serial_put_int(cm, 3);
        serial_put_str("cm \n");
        delay_ms(50);
    }

    return 0;
}
