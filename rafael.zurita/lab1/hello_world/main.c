/* Enciende y apaga cada un segundo led incorporado a la placa arduino
 controlado por el PIN13 (portb bit 5) del MCU atmega328P */

#include "utils.h"

int main(void)
{
        led_init();

        while (1) {
                led_toggle();
                delay_ms(1000);
        }
}
